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

void Network::prtCmd(int fd)
{
	CommandChunk tempChunk;
	size_t queueSize = this->commandQueue.size();
	string temp;

	for (size_t i = 0; i < queueSize; i++)
	{
		tempChunk = this->commandQueue.front();
		//cout << tempChunk.fd << " | " << tempChunk.prefix << " | " << tempChunk.command;
		temp.append(std::to_string(tempChunk.fd) + " | " + tempChunk.prefix + " | " + tempChunk.command + " | ");
		for (size_t j = 0; j < tempChunk.parameters.size(); j++)
		{
			//cout << tempChunk.parameters[i] << " - ";
			temp.append(tempChunk.parameters[j] + " - ");
		}
		//cout << "| " << tempChunk.parameterLast << std::endl;
		temp.append("| " + tempChunk.parameterLast + "\n");
		//this->commandQueue.push(this->commandQueue.front());
		this->commandQueue.pop();
		User* user = this->userManager.getUserByFd(fd);
		this->sendToUser(*user, temp);
		
	}
}

bool Network::sendToUser(User& user, const std::string& message)
{
	map<int, vector<string> >::iterator iter;

	iter = this->sendMap.find(user.getFd());
	if (iter == this->sendMap.end())
	{
		vector<string> temp;
		temp.push_back(message);
		this->sendMap.insert(make_pair(user.getFd(), temp));
		std::cout << user.getFd() << "]" << message << endl;
	}
	else
	{
		iter->second.push_back(message);
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
		// protocol ERROR
	} 
	// 공백 날리기(trim)기능 추가
	tempChunk.fd = fd;
	if (cmd[0] == ':')
	{
		if (cmd.find(' ') == string::npos)
		{
			//TODO:ERROR
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
	// while (1)
	// {
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
		// FIXME: iter를 받아놓고 for문 내부에서 map을 조작(삭제)해서, iter가 유효하지 않은 위치를 포인팅하는거 같음.
		//for(map<int, User*>::iterator iter = users.begin(); iter != users.end(); iter++)
		for(map<int, User*>::iterator iter = users.begin(); iter != users.end();)
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
					int tempFd;
					tempFd = iter->first;
					cerr << "[recv " << tempFd << "]" << strerror(errno) <<endl;
					++iter;
					this->userManager.deleteUser(tempFd);
					close(tempFd);
					continue;
				}
				else if (lenRecv == 0)
				{
					int tempFd;
					tempFd = iter->first;
					cout << tempFd << " disconnect" << endl;
					++iter;
					this->userManager.deleteUser(tempFd);
					close(tempFd);
					continue ;
					//TODO:this->userManager.
				}
				else
				{
					tempBuffer.assign(buffer, lenRecv);
					user->appendBuffer(tempBuffer);
					while(1)
					{
						if (user->getBuffer().empty())
						{
							break;
						}
						size_t crlfIndex = user->getBuffer().find("\r\n");
						if (crlfIndex == string::npos)
						{
							std::cout << "🔥" << iter->first << " :" << user->getBuffer() << std::endl;
							break;
						}
						else if (crlfIndex >= BUFFERSIZE)
						{
							tempBuffer.assign(user->getBuffer(), BUFFERSIZE - 2);
							tempBuffer.append("\r\n");
							pushCmdToQueue(iter->first, tempBuffer);
							//prtCmd(iter->first);
							// User.setIgnore();
							user->setBuffer("");
							break;
						}
						else
						{
							tempBuffer.assign(user->getBuffer(), 0, crlfIndex);
							pushCmdToQueue(iter->first, tempBuffer);
							//prtCmd(iter->first);
							tempBuffer.assign(user->getBuffer().substr(crlfIndex + 2, user->getBuffer().size() - crlfIndex - 2));
							user->setBuffer(tempBuffer);
						}
					}
				}
			}
			++iter;
		}
		for (map<int, vector<string> >::iterator iter = this->sendMap.begin(); iter != this->sendMap.end();)
		{
			int lenSend;
			map<int, vector<string> >::iterator temp = iter;
			if (FD_ISSET(iter->first, &this->wSet))
			{
				for (vector<string>::iterator iterVec = iter->second.begin(); iterVec != iter->second.end();)
				{
					lenSend = ::send(iter->first, iterVec->c_str(), iterVec->size(), 0);
					if (lenSend < 0)
					{
						cerr << iter->first << " send error" << endl;
					}
					else if (lenSend == 0)
					{
						cerr << iter->first  << " ???" << endl;
					}
					else
					{
						cout << iter->first << " send done" << endl;
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
	//}
	return true;
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
	map<int, vector<string> >::iterator iterMap = this->sendMap.begin();
	map<int, vector<string> >::iterator iterMapEnd = this->sendMap.end();
	for (; iterMap != iterMapEnd; iterMap++)
	{
		std::cout << iterMap->first << ", ";
		FD_SET(iterMap->first, &this->wSet);
	}
	cout << endl;
}

// 서버어서 소켓 관련 에러가 났을때 exception을 쓰는게 좋나?
// 아니면 에러를 반환시켜서 서버를 종료시키는게 맞나?
// 아니면 로그만 남기고 그냥 예외처리 하고 쭉유지???????