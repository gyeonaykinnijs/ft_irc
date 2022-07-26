//
// Created by 연규준 on 2022/07/24.
//

#include "Network.h"
#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>

#include <cerrno>

Network::Network(const std::string ip, const short port, const std::string passWord)
: IP_(ip), PORT_(port), PASSWORD_(passWord)
{
	memset(&this->addressServer_, 0, sizeof(this->addressServer_));
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
	if (!isZero(&this->addressServer_, sizeof(this->addressServer_)))
	{
		close(this->fdServer_);
	}
};

void Network::init()
{
	int fd;

	this->addressServer_.sin_family = PF_INET;
	this->addressServer_.sin_port = htons(this->PORT_);
	inet_pton(AF_INET, this->IP_.c_str(), &this->addressServer_.sin_addr);
	this->fdServer_ = socket(AF_INET, SOCK_STREAM, 0);
	fd = this->fdServer_;
	fcntl(fd, F_SETFL, O_NONBLOCK);
};

bool Network::IOMultiflexing()
{


	if (bind(this->fdServer_, reinterpret_cast<sockaddr*>(&this->addressServer_), sizeof(this->addressServer_)) < 0)
	{
		// FIXME: 수정 필요.
		std::cerr << "[bind]" << strerror(errno) <<std::endl;
	}
	if(listen(this->fdServer_, 5) < 0)
	{
		// FIXME: 수정 필요.
		std::cerr << "[listen]" << strerror(errno) <<std::endl;
	}
	while (1)
	{
		initFdSets();
		if (select(this->fdServer_, &this->rSet_, &this->wSet_, NULL, NULL) < 0)
		{
			// FIXME: 수정 필요.
			std::cerr << "[select]" << strerror(errno) <<std::endl;
		}
		if (FD_ISSET(this->fdServer_, &this->rSet_))
		{
			// 커넥션 작업 수행
		}
		else
		{
			// 이미 연결된 유저들과 관련된 동작
			for()
			{
				// FIXME: 추후 user이터레이터 얻고 나서 수정.
				if (FD_ISSET(iter->fd, &this->rSet_))
				{
					;
				}
			}
			for (int i = 0; i < this->sendVector_.size(); i++)
			{
				this->sendVector_[i].getFd
			}
		}
	}
}

// TODO:
void Network::initFdSets()
{
	// rSet모든 유저 돌면서 set에 추가.
	// wSet의 경우, queue에 입력된 유저들을 확인하고...? 근데 채널에 보내는 경우는?
}

// 서버어서 소켓 관련 에러가 났을때 exception을 쓰는게 좋나?
// 아니면 에러를 반환시켜서 서버를 종료시키는게 맞나?
// 아니면 로그만 남기고 그냥 예외처리 하고 쭉유지???????