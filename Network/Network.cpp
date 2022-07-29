//
// Created by 연규준 on 2022/07/24.
//

#include "Network.hpp"
#include <arpa/inet.h>
#include <sys/socket.h>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include "../User/User.hpp"
#include "../User/UserManager.hpp"

#include <cerrno>

using namespace std;
#define BUFFERSIZE 512

Network::Network(const char* ip, const short port, const char* passWord, UserManager& userManager)
: IP(ip), PORT(port), PASSWORD(passWord), userManager(userManager)
{
	memset(&this->addressServer, 0, sizeof(this->addressServer));
};

bool isZero(void* data, size_t size)
{
	char c = 0;
	for (size_t i = 0; i < size; i++)
	{
		if (*((char *)data + i) != c)
		{
			return false;
		}
	}
	return true;
}

Network::~Network()
{
	if (!isZero(&this->addressServer, sizeof(this->addressServer)))
	{
		close(this->fdServer);
	}
};

void Network::init()
{
	int fd;

	this->addressServer.sin_family = PF_INET;
	this->addressServer.sin_port = htons(this->PORT);
	inet_pton(AF_INET, this->IP.c_str(), &this->addressServer.sin_addr);
	this->fdServer = socket(AF_INET, SOCK_STREAM, 0);
	fd = this->fdServer;
	fcntl(fd, F_SETFL, O_NONBLOCK);
};

bool Network::AcceptUser()
{
	sockaddr_in addressClient;
	socklen_t lenClient = sizeof(addressClient);
	int fdClient = ::accept(this->fdServer, reinterpret_cast<sockaddr*>(&addressClient), &lenClient);
	if (fdClient < 0)
	{
		std::cerr << "[select]" << strerror(errno) <<endl;
	}
	this->userManager.makeUser(fdClient);
	std::cout << fdClient << " user set" << std::endl;
	return true;
}

void pushCmdToQueue(string cmd)
{
	cout << "🌟" << cmd << "🌟" << endl;
}

bool Network::IOMultiflexing()
{
	string tempBuffer;
	// bind와 구분하기 위해, 아래의 bind는 namespace가 없다는걸 명시하기 위해 앞에 ::를 붙인다.
	if (::bind(this->fdServer, reinterpret_cast<sockaddr*>(&this->addressServer), sizeof(this->addressServer)) < 0)
	{
		// FIXME: 수정 필요.
		cerr << "[bind]" << strerror(errno) <<endl;
	}
	if(::listen(this->fdServer, 5) < 0)
	{
		// FIXME: 수정 필요.
		cerr << "[listen]" << strerror(errno) <<endl;
	}
	while (1)
	{
		initFdSets();
		sleep(3);
		// FIXME: 클라 끊겼을떄 정리하는 코드 작성
		if (::select(10, &this->rSet, &this->wSet, NULL, NULL) < 0)
		{
			// FIXME: 수정 필요.
			cerr << "[select]" << strerror(errno) <<endl;
		}
		if (FD_ISSET(this->fdServer, &this->rSet))
		{
			this->AcceptUser();
		}
		else
		{
			map<int, User*>& users = this->userManager.getAllUser();
			// 이미 연결된 유저들과 관련된 동작
			for(map<int, User*>::iterator iter = users.begin(); iter != users.end(); iter++)
			{
				if (FD_ISSET(iter->first, &this->rSet))
				{
					int lenRecv;
					char buffer[BUFFERSIZE];
					User* user = this->userManager.getUserByFd(iter->first);
					// BUFFERSIZE 다 받지 말고, 유저 버퍼에 남아있는 버퍼 사이즈의 길이 반영해서, 도합 512까지.
					lenRecv = ::recv(iter->first, buffer, BUFFERSIZE, 0);
					if (lenRecv < 0)
					{
						cerr << "[recv " << iter->first << "]" << strerror(errno) <<endl;
					}
					else if (lenRecv == 0)
					{
						this->userManager.deleteUser(iter->first);
						cout << iter->first << " disconnect" << endl;
						//TODO:this->userManager.
					}
					else
					{
						tempBuffer.assign(buffer, lenRecv);
						user->appendBuffer(tempBuffer);
						// 유저 버퍼 처리하는 로직
						// 유저에 ignore 플래그 필요
						// FIXME: 버퍼에 내용이 남아있는 상태에서 select가 안들어 오면, 남아있는 내용이 동작하지 않는다. -> 
						while(1)
						{
							if (user->getBuffer().empty())
							{
								break;
							}
							size_t crlfIndex = user->getBuffer().find("\r\n");
							if (crlfIndex == string::npos)
							{
								std::cout << "🔥" << user->getBuffer() << std::endl;
								break;
							}
							else if (crlfIndex >= BUFFERSIZE)
							{
								tempBuffer.assign(user->getBuffer(), BUFFERSIZE - 2);
								tempBuffer.append("\r\n");
								pushCmdToQueue(tempBuffer);
								// User.setIgnore();
								user->setBuffer("");
							}
							else
							{
								tempBuffer.assign(user->getBuffer(), 0, crlfIndex);
								pushCmdToQueue(tempBuffer);
								tempBuffer.assign(user->getBuffer().substr(crlfIndex + 2, user->getBuffer().size() - crlfIndex - 2));
								user->setBuffer(tempBuffer);
							}
						}
					}
				}
			}
			// TODO: send작업은 좀 나중에 하기.
			// for (int i = 0; i < this->sendVector_.size(); i++)
			// {
			// }
		}
	}
}

// TODO:
void Network::initFdSets()
{
	// rSet모든 유저 돌면서 set에 추가.
	FD_ZERO(&this->rSet);
	FD_ZERO(&this->wSet);
	map<int, User*>::iterator iter =  this->userManager.getAllUser().begin();
	map<int, User*>::iterator iterEnd =  this->userManager.getAllUser().end();
	FD_SET(this->fdServer, &this->rSet);
	for (;iter != iterEnd; iter++)
	{
		
		FD_SET(iter->first, &this->rSet);
	}
	// wSet의 경우, queue에 입력된 유저들을 확인하고...? 근데 채널에 보내는 경우는?
	
}

// 서버어서 소켓 관련 에러가 났을때 exception을 쓰는게 좋나?
// 아니면 에러를 반환시켜서 서버를 종료시키는게 맞나?
// 아니면 로그만 남기고 그냥 예외처리 하고 쭉유지???????