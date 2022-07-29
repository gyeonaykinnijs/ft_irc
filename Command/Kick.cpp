#include "Kick.hpp"

/**
 * @brief 
 * 				
 * 				format: KICK <channel> <user> *( "," <user> ) [<comment>]
 */

void Kick::execute(ChannelManager &channelManager,
					UserManager &userManager,
					Network &network,
					struct CommandChunk commandChunk)
{
	
	User *user = userManager.getUserByFd(commandChunk.fd);
	vector<string> param = commandChunk.parameters;
	

	string name = param.at(0);
	string targetUser = param.at(1);
	string reason = "Something....";

	Channel *channel = user->getChannel();
	if (param.size() < 2) {
		/**
		 * @brief 
		 * 
		 * 
		 * 			less Param ERROR
		 * 
		 */
		return;
	}

	if (param.size() >= 3 && (param[2][0] != ':' || param[2].size() > 1)) {
		reason = "";
		for (vector<string>::iterator it = param.begin() + 2; it != param.end(); it++)
			reason.append(*it + " ");
	}



	if (!channel || channel->getChannelName() != name) {
		/**
		 * @brief 
		 * 
		 * 			채널이 존재하지 않거나 채널이름이 맞지 않는 ERROR
		 * 
		 */
		return;
	}

	if (channel->getMakeUser() != user) {
		
		/**
		 * @brief 
		 * 
		 * 		강퇴하는 사람이 방장인지 확인
		 * 
		 * 		없을시 ERROR
		 * 
		 */

		return;
	}

	User *none = channel->selectJoinUser(targetUser);
	if (!none) {
		
		/**
		 * @brief 
		 * 
		 * 		user가 channel에 있는지 확인
		 * 
		 * 		없을시 ERROR
		 * 
		 */
		return;
	}

	if (!none->getChannel() || none->getChannel() != channel) {
		
		/**
		 * @brief 
		 * 
		 * 		강퇴 당하는 사람이 채널에 있는지 확인
		 * 		없을 시 ERROR
		 * 
		 */
		return;
	}

	none->setChannel(NULL);
	channel->deleteJoinUser(none);
}
