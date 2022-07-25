#ifndef __NETWORK_H__
#define __NETWORK_H__

#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <utility>
#include <sys/socket.h>
#include <netinet/in.h>

class User;
class Channel;

struct commandReq
{
	std::string prefix;
	std::string command;
	std::vector<std::string> parameters;
	std::string parameterLast;
};

class Network
{
public:
	Network(const std::string ip, const short port, const std::string password);
	~Network(); //RAII
	void init();
	bool IOMultiflexing();
	bool sendToUser(User& user, const std::string& message);
	bool sendToChannel(Channel& channel, const std::string& message);
	bool kick(const std::string& message, User& user);
	commandReq getCommand();
private:
	Network(const Network& other);
	Network& operator=(const Network& other);
	const std::string PASSWORD_;
	sockaddr_in addressServer_;
	const std::string IP_;
	const short PORT_;
	int fdServer_;
	std::queue<commandReq> commandQueue_;
	std::queue< std::pair<std::string, std::string> > sendQueue_;
};

#endif
