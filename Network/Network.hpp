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
#include "../Logger/Logger.hpp"

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
	Network(const short port, const char* passWord, UserManager& userManager, Logger& argLogger);
	~Network(); //RAII
	bool init();
	bool IOMultiflexing();
	bool sendToUser(User& user, const std::string& message);
	bool sendToUser2(int fd, const std::string& message);
	bool sendToChannel(Channel& channel, const std::string& message);
	bool sendToOtherInChannel(Channel& channel, int fd, const std::string& message);
	void disconnectUser(User* user);
	CommandChunk getCommand();
private:
	Network(const Network& other);
	Network& operator=(const Network& other);
	bool AcceptUser();
	void pushCmdToQueue(int fd, string cmd);
	void prtCmd(int fd);
	//FIXME:
	// void logging(const string& log);
	// void errorLogging(const string& log, bool serverEndFlag);
	void recvActionPerUser(map<int, User*>& users);
	void recvParsingAndLoadCommands(User* user, char* bufferRecv, size_t lenRecv);
	void sendActionPerSendQueue();
	void initFdSets();
	
	// TODO: public으로 호출하면, 해당 클라의 연결을 끊을 수 있는 함수 추가. -> 만들필요 없을거같은데
	fd_set wSet;
	fd_set rSet;
	sockaddr_in addressServer;
	const short PORT;
	const std::string PASSWORD;
	UserManager& userManager;
	int fdServer;
	queue<CommandChunk> commandQueue;
	//FIXME:
	// queue<string> errorLogQueue;
	// queue<string> logQueue;
	map<int, vector<string> > sendMap;
	bool exitFlag;
	Logger& logger;
};

#endif