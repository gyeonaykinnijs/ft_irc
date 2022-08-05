#include "./Cnick.hpp"

void Cnick::execute(ChannelManager& channelManager, UserManager& userManager, Network& network, struct CommandChunk commandChunk)
{  // 최대길이 9
	User *user = userManager.getUserByFd(commandChunk.fd);
	vector<string> param = commandChunk.parameters;
	(void)channelManager;
	
	if (param.empty()) // 인자 부족할 때
	{
		string msg = UserManager::makeMessage(ERR_NEEDMOREPARAMS, user->getNickname(), "Need more Parameter");
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
	user->setNickname(nickname);
	if (user->getIsRegistered()) // 이미 등록했고 nick 변경할 때
	{
		// 응답코드 필요
		string msg = UserManager::makeMessage(prevNickname, "is now known as" ,user->getNickname());
		network.sendToUser2(user->getFd(), msg);
		userManager.addUser(user);
		return;
	}
	else
	{
		// 처음 nick 설정했을 때 리플라이 보내기
	}
}
