#ifndef __NETWORK_H__
#define __NETWORK_H__

#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <utility>
#include <sys/socket.h>
#include <netinet/in.h>
// #include "../defines.hpp"
#include "../User/UserManager.hpp"
#include "../Channel/ChannelManager.hpp"
// class User;
// class UserManager;
// class Channel;

struct CommandChunk
{
	int fd;
	std::string prefix;
	std::string command;
	std::vector<std::string> parameters;
	std::string parameterLast;
};

class Network
{
public:
	Network();
	Network(const char* ip, const short port, const char* passWord, UserManager& userManager);
	~Network(); //RAII
	void init();
	bool IOMultiflexing();
	bool sendToUser(User& user, const std::string& message);
	bool sendToChannel(Channel& channel, const std::string& message);
	bool kick(const std::string& message, User& user);
	CommandChunk getCommand();
private:
	Network(const Network& other);
	Network& operator=(const Network& other);

	void initFdSets();
	fd_set wSet;
	fd_set rSet;
	sockaddr_in addressServer;
	const std::string IP;
	const short PORT;
	const std::string PASSWORD;
	UserManager& userManager;
	int fdServer;
	std::queue<CommandChunk> commandQueue;
	std::vector<std::pair<User, std::string> > sendVector;
};

#endif
