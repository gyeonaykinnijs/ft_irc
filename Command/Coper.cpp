#include "Coper.hpp"


/*

### OPER
`OPER <username> <password>`
	- 사용자를 해당 서버/네트워크의 IRC 운영자로 인증합니다.
	- RFC 1459에 정의되어 있습니다.

	옵(Op) - 오퍼레이터(Operator)의 앞에서 따온 것이라 보시면 됩니다.

    채널에서 타인에게 보이스, 옵을 주거나, 채널의 모드를 조작하는 등

    옵을 가지고 있는 채널 내에서의 권한 대부분을 행사할 수 있습니다

	/msg ^^ 옵 <#채널> [닉네임] [닉네임] ..

	채널에서 해당 사람들에게 옵을 줍니다. 여러명을 지정할 수 있습니다. 

	채널만 적고 닉네임을 적지 않은 경우엔 명령을 내린 사용자에게 옵을 줍니다.

	ex) /msg ^^ 옵 #^^# Arcy arcturus
	

*/

void Coper::execute(ChannelManager &channelManager,
					UserManager &userManager,
					Network &network,
					struct CommandChunk commandChunk)
{
	User *user = userManager.getUserByFd(commandChunk.fd);
	if (user->getIsRegistered() == false)
	{
		// 에러 메시지 보내야 됨
		cout << "it should be registered" << endl;
		return ;
	}

	vector<string> param = commandChunk.parameters;
	string channelName = param[0];
	Channel *channel = channelManager.getChannel(channelName);
	map<string, User *> userList = channel->getJoinUser();
	if (!channel)
	{	// channel 없을 때
		string msg = UserManager::makeMessage(ERR_NOSUCHCHANNEL, user->getNickname(), "No Such Channel");
		network.sendToUser(*user, msg);
		return;
	}
	for (unsigned long i = 1; i < param.size(); i++)
	{
		if (!userList[param[i]])
		{
			/**
			 * @brief 
			 * 			No Such User in Channel Error
			 */

			string msg = UserManager::makeMessage(ERR_USERNOTINCHANNEL, user->getNickname(), "No Such User in Channel");
			network.sendToUser(*user, msg);
			return ;
		}
	}

	/**
	 * @brief 
	 * 
	 * 				Setting User Auth -> Admin
	 * 
	 */


	for (unsigned long i = 1; i < param.size(); i++)
	{
		User * user = userList[param[i]];
		user->setAuth(User::ADMIN);
	}
}