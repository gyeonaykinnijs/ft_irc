#include "./Cnick.hpp"

void execute(const struct CommandChunk commandChunk)
{	
	if (!commandChunk.parameter[1])
	{
		sendError(ERR_NONICKNAMEGIVEN);
	}
	// user->server
	if (UserManager::getUserByFd(commandChunk.fd)->getNickname() == "default")
	{

	}
	// server-user
	// 채널 내 전체에게 user의 nickname이 command.nickname으로 바뀌었다는 메시지 보내주기
}
 