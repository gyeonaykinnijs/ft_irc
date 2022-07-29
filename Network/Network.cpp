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

bool Network::IOMultiflexing()
{
	
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
		//std::cout << "ssdddd" << std::endl;
		if (FD_ISSET(this->fdServer, &this->rSet))
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
					lenRecv = ::recv(iter->first, buffer, BUFFERSIZE, 0);
					//std::cout << "[" << iter->first << "] " << lenRecv << std::endl;
					//write(1, buffer, lenRecv);
					if (strnstr(buffer, "\r\n", lenRecv) == NULL)
					{
						
						//TODO:512내에 CRLF가 안오면, 다음 CRLF까지 들어온 입력을 싹 날려주는 명령. 근데 User에서 가지고 있어야되서 일단 패스.
						//int errorFlag = false; // 
						// 유저단에서 버퍼도 가지고 있어야 할거 같은데? ㅋㅋㅋ -> 유저가 보낸 명령르 다 못받을 수도 있어서, 받을때까지 기다려야 하면, 이걸 일단 가지고 있어야한다.
					}
					while (1)
					{
						char* where = strnstr(buffer, "\r\n", lenRecv);
						size_t len = where - buffer;
						if (where == NULL)
						{
							//cout << lenRecv << endl;
							//cout << where << endl;
							printf("🌟%p\n", where);
							break;
							//TODO:no \r\n, 나올때까지 입력 날려버리기. -> buffer 꽉 차게 받받았았는데 CRLF가 없는 경우 CRLF나올때까지 모든 입력 무시.
							// 2. 버퍼에 recv한 데이터가 짤려서 CRLF가 안들어간 경우 ->
						}
						else
						{
							string temp(buffer, 0, len);
							cout << "🌟" << temp << "🌟" << endl;
							if
							{
								lenRecv -= len + 2;
								if (lenRecv == 0)
								{
									cout << "33333333333333" << endl;
									break;
								}
								memcpy(buffer, buffer + len + 2, lenRecv);
							}
						}
					}
				}
			}
			// TODO: send작업은 좀 나중에 하기.
			// for (int i = 0; i < this->sendVector_.size(); i++)
			// {
			// 	if (FD_ISSET(this->sendVector_[i].first.getFd(), &this->wSet))
			// 	{
					
			// 	}
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