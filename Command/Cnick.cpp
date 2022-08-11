#include "./Cnick.hpp"

void Cnick::execute(ChannelManager& channelManager, UserManager& userManager, Network& network, struct CommandChunk commandChunk)
{  // 최대길이 9
	User *user = userManager.getUserByFd(commandChunk.fd);
	vector<string> param = commandChunk.parameters;
	(void)channelManager;
	
	if (user->getPassOK() == false)
	{	// 비밀번호 맞기 전 입력 못 하게
		string msg = UserManager::makeMessage(ERR_NOTCONNECTED, "*", "User should be connected first");
		network.sendToUser2(user->getFd(), msg);
		return;
	}
	else if (param.empty())
	{	// 인자 부족
		string msg = UserManager::makeMessage(ERR_NEEDMOREPARAMS, user->getNickname(), "Not enough parameters");
		network.sendToUser2(user->getFd(), msg);
		return;
	}
	string nickname = param[0];
	if (userManager.hasNickname(nickname)) // 불가능한 닉네임일 때
	{
		string msg = UserManager::makeMessage(ERR_NICKNAMEINUSE, user->getNickname(), "Nickname is already in use");
		network.sendToUser2(user->getFd(), msg);
		return;
	}
	if (nickname.size() > 9)
	{
		nickname = nickname.substr(0, 9);
	}
	if (!(nickname[0] > 'a' && nickname[0] < 'z') || (nickname[0] > 'A' && nickname[0] < 'Z'))
	{
		string msg = UserManager::makeMessage(ERR_ERRONEOUSNICKNAME, nickname, "Erroneous Nickname");
		network.sendToUser2(user->getFd(), msg);
		return;
	}
	string prevNickname = user->getNickname();
	user->setNickOK(true);
	user->setNickname(nickname);
	if (user->getIsRegistered())
	{	// 이미 등록했고 nick 변경할 때
		// 응답코드 필요
		string msg = UserManager::makeMessage(":" + user->getNickname() + "!" + user->getUserName() + "@127.0.0.1 " + "NICK", user->getNickname(), "");
		network.sendToUser2(user->getFd(), msg);
	}
}
