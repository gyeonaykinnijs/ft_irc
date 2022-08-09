#ifndef __NETWORK_HPP__
#define __NETWORK_HPP__

#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <utility>
#include <sys/socket.h>
#include <netinet/in.h>
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
	bool init();
	bool IOMultiflexing();
	bool sendToUser(User& user, const std::string& message);
	bool sendToUser2(int fd, const std::string& message);
	bool sendToChannel(Channel& channel, const std::string& message);
	void disconnectUser(User* user);
	CommandChunk getCommand();
private:
	Network(const Network& other);
	Network& operator=(const Network& other);
	bool AcceptUser();
	void pushCmdToQueue(int fd, string cmd);
	void prtCmd(int fd);
	void logging(const string& log);
	void errorLogging(const string& log, bool serverEndFlag);
	void recvActionPerUser(map<int, User*>& users);
	void recvParsingAndLoadCommands(User* user, char* bufferRecv, size_t lenRecv);
	void sendActionPerSendQueue();
	void initFdSets();
	
	fd_set wSet;
	fd_set rSet;
	sockaddr_in addressServer;
	const std::string IP;
	const short PORT;
	const std::string PASSWORD;
	UserManager& userManager;
	int fdServer;
	queue<CommandChunk> commandQueue;
	queue<string> errorLogQueue;
	queue<string> logQueue;
	map<int, vector<string> > sendMap;
	bool exitFlag;
};

#endif
