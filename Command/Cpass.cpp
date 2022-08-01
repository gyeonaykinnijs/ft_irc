#include "./Cpass.hpp"

/**
 * @brief 
 * 			pass는 user가 서버에 접속할 때 비밀번호를 걸게 해준다. 
 * 
 * 			접속 비밀번호가 필요한데 제공되지 않거나 틀렸다면 user는 서버에 성공적으로 연결될 수 없다. 
 * 
 * 			connection registration이 완료된 후에는 이 명령어를 사용할 수 없다. 

			<password>는 접속 비밀번호다. user 계정이나 다른 user에 사용자별 인증 매커니즘과는 관련이 없다.

			서버에서 요구된다면, 접속하려는 시도가 일어나기 전에 보내져야 한다. 
			즉, client는 NICK/USER 조합을 보내기 전에 이 명령어를 보내야 한다. 
			PASS 명령을 register 전에 여러 개 보내도 되지만, 결국 마지막에 보낸 것만이 verification에 쓰인다.

			표준 IRC 서버에서는, 비밀번호는 서버의 설정에 있는 것과 일치해야 한다. 
			다른 서비스들은 런타임에 평가되는 암호에 대해 다른 형식을 요구할 수 있다.

			만약 클라이언트가 접속 등록이 완료된 후에 PASS 명령어를 보내면 
			ERR_ALREADYREGISTRED 응답이 보내지고 명령은 무시된다.
 * 

 * @param channelManager 
 * @param userManager 
 * @param network 
 * @param commandChunk 
 */
void Cpass::execute(ChannelManager &channelManager, UserManager &userManager, Network &network, struct CommandChunk commandChunk)
{
	User *user = userManager.getUserByFd(commandChunk.fd);

	if (user->getIsRegistered())
	{
		string msg = UserManager::makeMessage(ERR_ALREADYREGISTERED, user->getNickname(), "User is already registered");
		network.sendToUser(*user, msg);
		return;
	}
	else if (commandChunk.parameters.empty())
	{
		string msg = UserManager::makeMessage(ERR_NEEDMOREPARAMS, user->getNickname(), "Need more Parameter");
		network.sendToUser(*user, msg);
		return;
	} 
	else
	{
		string password = commandChunk.parameters[0];
		user->setPasswd(password);
	}
}