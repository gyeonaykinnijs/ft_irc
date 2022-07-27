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
class UserManager;

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
	Network::Network(const std::string ip, const short port, const std::string passWord, UserManager userManager);
	~Network(); //RAII
	void init();
	bool IOMultiflexing();
	bool sendToUser(User& user, const std::string& message);
	bool sendToChannel(Channel& channel, const std::string& message);
	bool kick(const std::string& message, User& user);
	commandChunk getCommand();
private:
	Network(const Network& other);
	Network& operator=(const Network& other);

	void initFdSets();
	UserManager& userManager_;
	fd_set rSet_;
	fd_set wSet_;
	const std::string PASSWORD_;
	sockaddr_in addressServer_;
	const std::string IP_;
	const short PORT_;
	int fdServer_;
	std::queue<commandChunk> commandQueue_;
	std::vector<std::pair<User, std::string> > sendVector_;
};

#endif
