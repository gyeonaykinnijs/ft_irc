#include "./Cnick.hpp"

void Cnick::execute(ChannelManager& channelManager, UserManager& userManager, Network& network, struct CommandChunk commandChunk)
{  // 최대길이 9
	User *user = userManager.getUserByFd(commandChunk.fd);
	vector<string> param = commandChunk.parameters;
	// Channel *channel = user->getChannel();
	(void)channelManager;
	
	if (param.empty()) // 인자 부족할 때
	{
		string msg = UserManager::makeMessage(ERR_NEEDMOREPARAMS, user->getNickname(), "Need more Parameter");
		network.sendToUser(*user, msg);
		return;
	}
	string nickname = param[0];
	if (userManager.hasNickname(nickname)) // 불가능한 닉네임일 때
	{
		string msg = UserManager::makeMessage(ERR_NICKNAMEINUSE, user->getNickname(), "Nickname is already in use");
		network.sendToUser(*user, msg);
		return;
	}
	if (nickname.size() > 9)
	{
		nickname = nickname.substr(9);
	}
	string prevNickname = user->getNickname();
	user->setNickname(nickname);
	if (user->getIsRegistered()) // 이미 등록했고 nick 변경할 때
	{
		// 응답코드 필요
		string msg = UserManager::makeMessage(prevNickname, "are now known as" ,user->getNickname());
		//network.sendToChannel(*channel, msg);
		network.sendToUser(*user, msg);
		return;
	}

}
