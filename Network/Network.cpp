//
// Created by 연규준 on 2022/07/24.
//

#include "Network.h"
#include <arpa/inet.h>
#include <sys/socket.h>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include "User/User.hpp"
#include "User/UserManager.hpp"

#include <cerrno>

using namespace std;

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
		if (::select(this->fdServer, &this->rSet, &this->wSet, NULL, NULL) < 0)
		{
			// FIXME: 수정 필요.
			cerr << "[select]" << strerror(errno) <<endl;
		}
		if (FD_ISSET(this->fdServer, &this->rSet))
		{
			int fdClient = ::accept(this->fdServer, )
		}
		else
		{
			// FIXME: ref로 변경 필요
			map<int, User*> users = this->userManager.getAllUser();
			// 이미 연결된 유저들과 관련된 동작
			for(map<int, User*>::iterator iter = users.begin(); iter != users.end(); iter++)
			{
				// FIXME: 추후 user이터레이터 얻고 나서 수정.
				if (FD_ISSET(iter->first, &this->rSet))
				{
					// FIXME: 유저 생성시 fd값을 받게.

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