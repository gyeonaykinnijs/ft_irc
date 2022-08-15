#include "Cnick.hpp"

bool Cnick::checkValidNickname(const string nickname)
{
	if (!(nickname[0] > 'a' && nickname[0] < 'z') || (nickname[0] > 'A' && nickname[0] < 'Z'))
	{
		return false;
	}
	if (nickname.find_first_not_of("abcdefghijklmnopqrstuvqwxyz0123456789[]-{}\\^`") != string::npos)
	{
		return false;
	}
	return true;
}

void Cnick::execute(ChannelManager& channelManager, UserManager& userManager, Network& network, struct CommandChunk commandChunk)
{  // 최대길이 9
	User *user = userManager.getUserByFd(commandChunk.fd);
	vector<string> param = commandChunk.parameters;
	(void)channelManager;
	
	if (user->getPassOK() == false)
	{	// 비밀번호 맞기 전 입력 못 하게
		string msg = UserManager::makeMessage(NULL, ERR_NOTCONNECTED, "*", "User should be connected first");
		network.sendToUser(user->getFd(), msg);
		return;
	}
	else if (param.empty())
	{	// 인자 부족
		string msg = UserManager::makeMessage(NULL, ERR_NEEDMOREPARAMS, user->getNickname(), "Not enough parameters");
		network.sendToUser(user->getFd(), msg);
		return;
	}
	string nickname = param[0];
	if (userManager.hasNickname(nickname))
	{	// 이미 사용중인 닉네임일 때
		string msg = UserManager::makeMessage(NULL, ERR_NICKNAMEINUSE, user->getNickname(), "Nickname is already in use");
		network.sendToUser(user->getFd(), msg);
		return;
	}
	if (nickname.size() > 9)
	{
		nickname = nickname.substr(0, 9);
	}
	if (!checkValidNickname(nickname))
	{	// nickname invalid 할때
		string msg = UserManager::makeMessage(NULL, ERR_ERRONEOUSNICKNAME, nickname, "Erroneous Nickname");
		network.sendToUser(user->getFd(), msg);
		return;
	}
	if (user->getIsRegistered())
	{	// 이미 등록했고 nick 변경할 때
		string msg = UserManager::makeMessage(user, RPL_NICK, nickname, "");
		network.sendToUser(user->getFd(), msg);
		map<string, Channel*>::iterator iter = user->getChannelList().begin();
		map<string, Channel*>::iterator iterEnd = user->getChannelList().end();
		for (;iter != iterEnd; iter++)
		{
			network.sendToOtherInChannel(*iter->second, user->getFd(), msg);
		}
	}
	user->setNickOK(true);
	user->setNickname(nickname);
}
