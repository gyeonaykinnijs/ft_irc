//
// Created by 연규준 on 2022/07/24.
//

#include "Network.hpp"
#include <arpa/inet.h>
#include <sys/socket.h>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>
#include "../defines.hpp"
#include "../User/User.hpp"
#include "../User/UserManager.hpp"

#include <cerrno>

using namespace std;
#define BUFFERSIZE 512

Network::Network(const char* ip, const short port, const char* passWord, UserManager& userManager)
: IP(ip), PORT(port), PASSWORD(passWord), userManager(userManager), exitFlag(false)
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

void Network::logging(const string& log)
{
	this->logQueue.push(log);
}

void Network::errorLogging(const string& log, bool serverEndFlag)
{
	this->errorLogQueue.push(log);
	this->exitFlag = serverEndFlag;
}

void Network::init()
{
	int result = 1;
	string tempLog;

	this->addressServer.sin_family = PF_INET;
	this->addressServer.sin_port = htons(this->PORT);
	inet_pton(AF_INET, this->IP.c_str(), &this->addressServer.sin_addr);
	this->fdServer = socket(AF_INET, SOCK_STREAM, 0);
	fcntl(this->fdServer, F_SETFL, O_NONBLOCK);
	fcntl(STDOUT_FILENO, F_SETFL, O_NONBLOCK);
	fcntl(STDERR_FILENO, F_SETFL, O_NONBLOCK);
	if (setsockopt(this->fdServer, SOL_SOCKET, SO_REUSEADDR, &result, sizeof(result)))
	{
		this->errorLogging(string("[setsockopt]") + strerror(errno), true);
	}
	this->logging(string("Socket init Success!"));
	if (::bind(this->fdServer, reinterpret_cast<sockaddr*>(&this->addressServer), sizeof(this->addressServer)) < 0)
	{
		this->errorLogging(string("[bind]") + strerror(errno), true);
	}
	if(::listen(this->fdServer, 5) < 0)
	{
		this->errorLogging(string("[listen]") + strerror(errno), true);
	}

};

void Network::initFdSets()
{
	FD_ZERO(&this->rSet);
	FD_ZERO(&this->wSet);
	if (!this->logQueue.empty())
	{
		FD_SET(STDOUT_FILENO, &this->wSet);
	}
	if (!this->errorLogQueue.empty())
	{
		FD_SET(STDERR_FILENO, &this->wSet);
	}
	map<int, User*>::iterator iter =  this->userManager.getAllUser().begin();
	map<int, User*>::iterator iterEnd =  this->userManager.getAllUser().end();
	FD_SET(this->fdServer, &this->rSet);
	for (;iter != iterEnd; iter++)
	{
		FD_SET(iter->first, &this->rSet);
	}
	map<int, vector<string> >::iterator iterMap = this->sendMap.begin();
	map<int, vector<string> >::iterator iterMapEnd = this->sendMap.end();
	for (; iterMap != iterMapEnd; iterMap++)
	{
		FD_SET(iterMap->first, &this->wSet);
	}
}

bool Network::AcceptUser()
{
	string tempLog;
	sockaddr_in addressClient;
	socklen_t lenClient = sizeof(addressClient);

	int fdClient = ::accept(this->fdServer, reinterpret_cast<sockaddr*>(&addressClient), &lenClient);
	if (fdClient < 0) 
	{
		this->errorLogging(string("[setsockopt]") + strerror(errno), false);
	}
	this->userManager.makeUser(fdClient);
	return true;
}

bool Network::sendToUser2(int fd, const std::string& message)
{
	map<int, vector<string> >::iterator iter;

	iter = this->sendMap.find(fd);
	if (iter == this->sendMap.end())
	{
		vector<string> temp;
		temp.push_back(message);
		//FIXME:this->sendMap.insert(make_pair(user.getFd(), temp));
		this->sendMap[fd] = temp;
	}
	else
	{
		iter->second.push_back(message);
	}
	return true;
}

bool Network::sendToUser(User& user, const std::string& message)
{
	map<int, vector<string> >::iterator iter;

	iter = this->sendMap.find(user.getFd());
	if (iter == this->sendMap.end())
	{
		vector<string> temp;
		temp.push_back(message);
		//FIXME:this->sendMap.insert(make_pair(user.getFd(), temp));
		this->sendMap[user.getFd()] = temp;
	}
	else
	{
		iter->second.push_back(message);
	}
	return true;
}

bool Network::sendToChannel(Channel& channel, const std::string& message)
{
	map<std::string, User *>::iterator iter = channel.getJoinUser().begin();
	map<std::string, User *>::iterator iterEnd = channel.getJoinUser().end();

	while (iter != iterEnd)
	{
		this->sendToUser(*iter->second, message);
		++iter;
	}
	return true;
}

CommandChunk Network::getCommand()
{
	CommandChunk temp;
	temp.fd = -1;
	if (!this->commandQueue.empty())
	{
		temp =  this->commandQueue.front();
		this->commandQueue.pop();
	}
	return temp;
}

void Network::pushCmdToQueue(int fd, string cmd)
{
	CommandChunk tempChunk;
	string tempStr;

	if (cmd.find("  ") != string::npos)
	{
		User *tempUser = this->userManager.getUserByFd(fd);
		string tempStr = UserManager::makeMessage(ERR_UNKNOWNCOMMAND, tempUser->getNickname(), "");
		this->sendToUser(*tempUser, tempStr);
	} 
	// 공백 날리기(trim)기능 추가
	tempChunk.fd = fd;
	if (cmd[0] == ':')
	{
		if (cmd.find(' ') == string::npos)
		{
			tempChunk.prefix.assign(cmd, 0, cmd.size());
			this->commandQueue.push(tempChunk);
			return ;
		}
		else
		{
			tempChunk.prefix.assign(cmd, 0, cmd.find(' '));
			cmd.assign(cmd, cmd.find(' ') + 1, cmd.size() - cmd.find(' ') - 1);
		}
	}

	if (cmd.find(' ') == string::npos)
	{
		tempChunk.command.assign(cmd, 0, cmd.size());
		this->commandQueue.push(tempChunk);
		return ;
	}
	else
	{
		tempChunk.command.assign(cmd, 0, cmd.find(' '));
		cmd.assign(cmd, cmd.find(' ') + 1, cmd.size() - cmd.find(' ') - 1);
	}
	
	while (1)
	{
		if (cmd.find(' ') == string::npos)
		{
			tempStr.assign(cmd, 0, cmd.size());
			tempChunk.parameters.push_back(tempStr);
			this->commandQueue.push(tempChunk);
			return ;
		}
		else
		{
			tempStr.assign(cmd, 0, cmd.find(' '));
			tempChunk.parameters.push_back(tempStr);
			cmd.assign(cmd, cmd.find(' ') + 1, cmd.size() - cmd.find(' ') - 1);
		}
		if (cmd[0] == ':')
		{
			tempChunk.parameterLast.assign(cmd, 0, cmd.size());
			this->commandQueue.push(tempChunk);
			return ;
		}
		else if (cmd.size() == 0)
		{
			break;
		}
	}
	this->commandQueue.push(tempChunk);
}

void Network::disconnectUser(User* user)
{
	int userFd = user->getFd();

	close(userFd);
	this->userManager.deleteUser(userFd);
}

void Network::recvParsingAndLoadCommands(User* user, char* bufferRecv, size_t lenRecv)
{
	user->appendBuffer(string(bufferRecv, lenRecv));
	while(1)
	{
		if (user->getBuffer().empty())
		{
			break;
		}
		size_t crlfIndex = user->getBuffer().find("\r\n");
		if (user->getIgnored())
		{
			if (crlfIndex == string::npos)
			{
				user->setBuffer("");
			}
			else
			{
				user->setBuffer(string(user->getBuffer().substr(crlfIndex + 2, user->getBuffer().size() - crlfIndex - 2)));
				user->setIgnored(false);
			}
		}
		else
		{
			// 512자를 넘지 않고 crlf가 없는 경우.
			if (user->getBuffer().size() <= BUFFERSIZE - 2 && crlfIndex == string::npos)
			{
				break;
			}
			// 버퍼 누적이 512자를 넘는데도 crlf가 없는 경우. -> 그냥 버퍼 누적이 512가 넘는 경우 앞에 거ㄹ를 다 때 버려야 한다.
			// 즉, crlfIndex >= BUFFERSIZE이 맞다(crlfIndex == string::npos조건 포함).
			else if (user->getBuffer().size() > BUFFERSIZE - 2 && crlfIndex > BUFFERSIZE - 2)
			{
				cout << "🔥 cmd 🔥 " << string(user->getBuffer(), 0, BUFFERSIZE - 2).append("\r\n") << endl;
				pushCmdToQueue(user->getFd(), string(user->getBuffer(), 0, BUFFERSIZE - 2).append("\r\n"));
				user->setBuffer("");
				user->setIgnored(true);
				break;
			}
			// 1조건 : 버퍼가 510자가 안되거나 같지만, crlf가 있는 경우
			// 2조건 : 버퍼가 510자를 초과하지만, crlf가 510자 내부에 있는 경우.
			else
			{
				cout << "🌟 cmd 🌟 " << string(user->getBuffer(), 0, crlfIndex) << endl;
				pushCmdToQueue(user->getFd(), string(user->getBuffer(), 0, crlfIndex));
				user->setBuffer(string(user->getBuffer().substr(crlfIndex + 2, user->getBuffer().size() - crlfIndex - 2)));
			}
		}
	}
}

void Network::recvActionPerUser(map<int, User*>& users)
{
	int lenRecv;
	char bufferRecv[BUFFERSIZE];
	for(map<int, User*>::iterator iter = users.begin(); iter != users.end();)
	{
		if (FD_ISSET(iter->first, &this->rSet))
		{
			User* user = this->userManager.getUserByFd(iter->first);
			lenRecv = ::recv(iter->first, bufferRecv, BUFFERSIZE, 0);
			std::cout << "client send command: " << endl << string(bufferRecv, 0, lenRecv) << endl;
			if (lenRecv < 0)
			{
				++iter;
				this->errorLogging(string("[recv]") + strerror(errno), false);
				disconnectUser(user); 
				continue;
			}
			else if (lenRecv == 0)
			{
				++iter;
				this->logging(string("[disconnect]"));
				disconnectUser(user);
				continue ;
			}
			else
			{
				recvParsingAndLoadCommands(user, bufferRecv, lenRecv);
			}
		}
		++iter;
	}
}

void Network::recvActionPerSendQueue()
{
	for (map<int, vector<string> >::iterator iter = this->sendMap.begin(); iter != this->sendMap.end();)
	{
		map<int, vector<string> >::iterator temp = iter;
		if (FD_ISSET(iter->first, &this->wSet))
		{
			for (vector<string>::iterator iterVec = iter->second.begin(); iterVec != iter->second.end();)
			{
				cout << "server send reply: " << endl << *iterVec << endl;
				if (::send(iter->first, iterVec->c_str(), iterVec->size(), 0) < 0)
				{
					User* user = this->userManager.getUserByFd(iter->first);
					this->errorLogging(string("[recv]") + strerror(errno), false);
					disconnectUser(user);
					break ;
				}
				++iterVec;
			}
			++iter;
			this->sendMap.erase(temp->first);
		}
		else
		{
			++iter;
		}
	}
}

bool Network::IOMultiflexing()
{
	string tempBuffer;

	initFdSets();
	if (::select(64, &this->rSet, &this->wSet, NULL, NULL) < 0)
	{
		this->errorLogging(string("[select]") + strerror(errno), true);
	}
	if (FD_ISSET(this->fdServer, &this->rSet))
	{
		this->AcceptUser();
	}
	if (FD_ISSET(STDOUT_FILENO, &this->wSet))
	{
		while (1)
		{
			if (this->logQueue.empty())
			{
				break ;
			}
			write(STDOUT_FILENO, this->logQueue.front().append("\n").c_str(), this->logQueue.front().size() + 1);
			this->logQueue.pop();
		}
	}
	if (FD_ISSET(STDERR_FILENO, &this->wSet))
	{
		while (1)
		{
			if (this->errorLogQueue.empty())
			{
				break ;
			}
			write(STDERR_FILENO, this->errorLogQueue.front().append("\n").c_str(), this->errorLogQueue.front().size() + 1);
			this->errorLogQueue.pop();
		}
		if (this->exitFlag == true)
		{
			return false;
		}
	}
	map<int, User*>& users = this->userManager.getAllUser();
	recvActionPerUser(users);
	recvActionPerSendQueue();
	return true;
}
