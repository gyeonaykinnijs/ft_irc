#include "Cprivmsg.hpp"

/**
 * @brief 
 * 
 * 
 * 		### PRIVMSG
 * 		`PRIVMSG <msgtarget> :<message>`
 *		- 일반적으로 사용자 또는 채널인 <msgtarget>에 <message>를 보냅니다.
		- RFC 1459에 정의되어 있습니다.
 * 
 */

void Cprivmsg::execute(ChannelManager &channelManager,
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
		if (param.size() < 2 || param[0].empty() || param[1].empty()) {
		/**
		 * @brief 
		 * 
		 * 			Need More Param ERROR
		 */

		string msg = UserManager::makeMessage(ERR_NEEDMOREPARAMS, user->getNickname(), "No Param");
		network.sendToUser(*user, msg);
		return;
	}

	
	string targetUser = param[0];
	string message;

	for (vector<string>::iterator it = param.begin() + 1; it != param.end(); it++) {
		message.append(*it + " ");
	}

	message = message[0] == ':' ? message.substr(1) : message;

	Channel *channel = user->getChannel();


	User *none = channel->selectJoinUser(targetUser);
	if (!none) {
		/**
		 * @brief 
		 * 
		 * 			Error
		 * 
		 */
		return;
	}

	/**
	 * @brief 
	 * 
	 * 		msg 전송 완료 확인
	 * 
	 */



}