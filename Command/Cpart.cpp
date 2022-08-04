#include "Cpart.hpp"


/*
### PART
	`PART <channels> [<message>]`
	- 사용자가 쉼표로 구분된 목록 <channels>의 채널을 떠나도록 합니다.
	- RFC 1459에 정의되어 있습니다.
*/

void Cpart::execute(ChannelManager &channelManager,
					UserManager &userManager,
					Network &network,
					struct CommandChunk commandChunk)
{
	User *user = userManager.getUserByFd(commandChunk.fd);
	vector<string> param = commandChunk.parameters;

	if (user->getIsRegistered() == false)
	{
		// 에러 메시지 보내야 됨
		cout << "it should be registered" << endl;
		return ;
	}	
	if (param.empty()) {
		/*
				param more need Error
		*/
		string msg = UserManager::makeMessage(ERR_NEEDMOREPARAMS, user->getNickname(), "No Param");
		network.sendToUser2(user->getFd(), msg);
		return;
	}
	std::string channelName = param[0];
	Channel *channel = channelManager.getChannel(channelName);
	if (!channel) {
		/**
		 * @brief 
		 * 
		 * 		No Such Channel Error
		 */

		string msg = UserManager::makeMessage(ERR_NOSUCHCHANNEL, user->getNickname(), "No Such Channel");
		network.sendToUser2(user->getFd(), msg);
		return;
	}

	if (!user->getChannel(channelName) || user->getChannel(channelName)->getChannelName() != channelName) {
		/**
		 * @brief 
		 * 
		 * 		NO Name Match Channel Error
		 * 
		 */

		string msg = UserManager::makeMessage(ERR_NOSUCHCHANNEL, user->getNickname(), "No Such Channel");
		network.sendToUser2(user->getFd(), msg);
		return;
	}

	/*
			유저 채널에서 퇴장
	*/
	channel->deleteJoinUser(user);
	user->deleteChannel(channelName);
}