#ifndef __NETWORK_H__
#define __NETWORK_H__

#include <iostream>
#include <string>
#include <queue>
#include <sys/socket.h>
#include <netinet/in.h>

class User;
class Channel;

struct commandReq
{
	std::string prefix;
	std::string command;
	vector<std::string> parameters;
	std::string parameterLast;
};

class Network
{
public:
	Network(const std::string ip, const short port, const std::string passWord);
	~Network(); //RAII
	Init();
	bool SendToUser(const std::string& message, User& user);
	bool SendToChannel(const std::string& message, Channel& channel);
	bool Kick(const std::string& message, User& user);
	commandReq getCommand();
private:
	Network(const Network& other);
	Network& operator=(const Network& other);
	const std::string PASSWORD_;
	sockaddr_in addressServer_;
	const std::string IP;
	const short PORT_;
	int fdServer_;
	std::queue<commandReq> commandQueue_;
};

#endif
