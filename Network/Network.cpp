//
// Created by 연규준 on 2022/07/24.
//

#include "Network.h"
#include <arpa/inet.h>

Network::Network(const std::string ip, const short port, const std::string passWord)
: IP_(ip), PORT_(port), PASSWORD_(passWord)
{
	memset(this->addressServer, 0, sizeof(this->addressServer_));
};

Network::~Network()
{

};

void Network::Init()
{
	this->addressServer_.sin_family = PF_INET;
	this->addressServer_.sin_port = htons(this->PORT_);
	inet_pton(AF_INET, this->IP_, &this->addressServer_.sin_addr);
};