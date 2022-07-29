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
}

void pushCmdToQueue(string cmd)
{

}

bool Network::IOMultiflexing()
{
	string tempBuffer;
	char *ptrBufferStart;
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
			this->AcceptUser();
		}
		else
		{
			map<int, User*>& users = this->userManager.getAllUser();
			// 이미 연결된 유저들과 관련된 동작
			for(map<int, User*>::iterator iter = users.begin(); iter != users.end(); iter++)
			{
				// 파싱 조건문 다시.
				// 우선 recv를 통해서 읽어들인다.
				// 읽어들인 문자에서 crlf가 없다면
				// 		1. 총 합이 512보다 길게 된다면, 510까지 입력을 커맨드로 처리하고, crlf가 올때까지 입력을 전부 날린다.
				//		2. 총 합이 512보다 짧다면 유저별 버퍼에 넣고 512자까지 읽어본다. 이후 1번.
				// 읽어들인 문자에서 crlf가 있다면 유저별 버퍼에 있는 내용과 합쳐서 파싱을 시작한다.
				// 		한 명령어 단위를 읽고, recvLen을 남은 길이로 갱신 후, 그 뒤부터 crlf을 찾는다.
				//			1. 버퍼 남은거에 crlf가 또 있다면 recvLen가 0이 될때까지 반복.
				//			2. crlf가 없고, recvLen이 0이 아니라면 유저별 버퍼에 넣고 다시 recv(위의 2번과 같음)
				//				이때, recv반환값이 would block일때까지 다 읽어와서...? 아니 이러면 그쪽에서 데이터를 계속 보내면 다른 클라한테 작업권이 안감.
				if (FD_ISSET(iter->first, &this->rSet))
				{
					int lenRecv;
					char buffer[BUFFERSIZE];
					lenRecv = ::recv(iter->first, buffer, BUFFERSIZE, 0);
					if (lenRecv < 0)
					{
						cerr << "[recv " << iter->first << "]" << strerror(errno) <<endl;
						continue;
					}
					else if (lenRecv == 0)
					{
						cout << iter->first << " disconnect" << endl;
						//TODO:this->userManager.
						continue;
					}
					ptrBufferStart = buffer;
					while (1)
					{
						char* where = strnstr(ptrBufferStart, "\r\n", lenRecv);
						// 유저 버퍼
						// where이 NULL이고, lenRecv + userBuffer >= 512인 경우
						//	userBuffer 510까지 buffer에서 받아와 저장하고 뒤에 crlf
						//	ptrBufferStart옮기고, lenRecv길이도 적합하게 수정
						// where이 NULL이고, lenRecv + userBuffer < 512인 경우 유저별 버퍼에 저장.
						if (where == NULL)
						{
							if (lenRecv == BUFFERSIZE)
							{
								tempBuffer.assign(ptrBufferStart, BUFFERSIZE - 2);
								tempBuffer.append("\r\n");
								pushCmdToQueue(tempBuffer);
								continue;
							}
							else
							{
								this->userManager.getUserByFd(iter->first)->setBuffer
							}
						}
						size_t len = where - buffer;
						if (where == NULL && lenRecv != 0)
						{
							string left(buffer, 0, lenRecv);
							cout << "2 :" << left << endl;
							this->userManager.getUserByFd(iter->first)->setBuffer(left);
							break;
						}
						else if (where != NULL)
						{
							string temp(buffer, 0, len);
							cout << "🌟" << temp << "🌟" << endl;
							if (lenRecv > (int)len + 2)
							{
								lenRecv -= len + 2;
								if (lenRecv == 0)
								{
									cout << "33333333333333" << endl;
									break;
								}
								memcpy(buffer, buffer + len + 2, lenRecv);
							}
							else
							{
								break;
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