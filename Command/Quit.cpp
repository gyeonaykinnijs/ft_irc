#include "Quit.hpp"

/*

### QUIT
`QUIT [<message>]`
	- 서버에서 사용자의 연결을 끊습니다.
	- "종료 메시지"가 지정된 경우, 기본 메시지인 닉네임 대신 메시지가 발송됩니다.
	- RFC 1459에 정의되어 있습니다.

*/

void Quit::execute(ChannelManager &channelManager,
					UserManager &userManager,
					Network &network,
					struct CommandChunk commandChunk)
{
	User *user = userManager.getUserByFd(commandChunk.fd);
	vector<string> param = commandChunk.parameters;


	std::string reason = param.empty() ? "Leaving..." : param.at(0);
	reason = reason.at(0) == ':' ? reason.substr(1) : reason;

	std::string buffer = ":" + commandChunk.prefix  + " QUIT :Quit" + reason + "\r\n";
	
	if (send(user->getFd(), buffer.c_str(), buffer.length(), 0) < 0)
		throw std::runtime_error("Error while sending message to client.");
}