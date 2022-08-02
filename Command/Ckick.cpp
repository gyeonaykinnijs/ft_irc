#include "Ckick.hpp"

/**
 * @brief 
 * 				
 * 				format: KICK <channel> <user> *( "," <user> ) [<comment>]
 */

void Ckick::execute(ChannelManager &channelManager,
					UserManager &userManager,
					Network &network,
					struct CommandChunk commandChunk)
{
	
	User *user = userManager.getUserByFd(commandChunk.fd);
	vector<string> param = commandChunk.parameters;
	(void)channelManager;
	
	if (user->getIsRegistered() == false)
	{
		// 에러 메시지 보내야 됨
		cout << "it should be registered" << endl;
		return ;
	}	

	string name = param[0];
	string targetUser = param[1];
	string reason = "Something....";

	Channel *channel = user->getChannel();
	if (param.size() < 2) {
		/**
		 * @brief 
		 * 
		 * 
		 * 			less Param ERROR
		 * 
		 * 
		 */

		string msg = UserManager::makeMessage(ERR_NEEDMOREPARAMS, user->getNickname(), "less Param ERROR");
		network.sendToUser(*user, msg);
		return;

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
		string msg = UserManager::makeMessage(ERR_NOSUCHCHANNEL, user->getNickname(), "No Such Channel");
		network.sendToUser(*user, msg);
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

		// What error Name
		string msg = UserManager::makeMessage(ERR_NOSUCHCHANNEL, user->getNickname(), "No Such Channel");
		network.sendToUser(*user, msg);
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

		string msg = UserManager::makeMessage(ERR_USERNOTINCHANNEL, user->getNickname(), "Not User in Channel");
		network.sendToUser(*user, msg);

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

		string msg = UserManager::makeMessage(ERR_NOTONCHANNEL, user->getNickname(), "Not User in Channel");
		network.sendToUser(*user, msg);
		return;
	}

	none->setChannel(NULL);
	channel->deleteJoinUser(none);
}
