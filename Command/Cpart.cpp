#include "Cpart.hpp"


/*
### PART
	`PART <channels> [<message>]`
	- 사용자가 쉼표로 구분된 목록 <channels>의 채널을 떠나도록 합니다.
	- RFC 1459에 정의되어 있습니다.
*/

void Part::execute(ChannelManager &channelManager,
					UserManager &userManager,
					Network &network,
					struct CommandChunk commandChunk)
{
	User *user = userManager.getUserByFd(commandChunk.fd);
	vector<string> param = commandChunk.parameters;

	if (param.empty()) {
		/*
				param more need Error
		*/
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
		return;
	}

	if (!user->getChannel() || user->getChannel()->getChannelName() != channelName) {
		/**
		 * @brief 
		 * 
		 * 		NO Name Match Channel Error
		 * 
		 */
		return;
	}

	/*
			유저 채널에서 퇴장
	*/

	channel->deleteJoinUser(user);
	user->setChannel(NULL);
}