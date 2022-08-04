#include "./Cuser.hpp"


/**
 * @brief 
 * 
 * @param channelManager 
 * @param userManager 
 * @param network 
 * @param commandChunk 
 * 
 * 				`USER <username> <hostname> <servername> <realname>` (RFC 1459)  
				`USER <user> <mode> <unused> <realname>` (RFC 2812)
				- 이 명령은 연결 시작 시 연결 클라이언트의 사용자 이름, 호스트 이름, 실제 이름 및 초기 사용자 모드를 지정하는 데 사용됩니다.
				- <realname>은 공백을 포함할 수 있으므로 콜론 접두사를 사용해야 합니다.
				- RFC 1459에서 정의되고 RFC 2812에서 수정되었습니다.

				USER는 user가 서버에 연결되는 동안 username과 realname을 설정하게 해준다. 접속 등록이 완료된 후에는 사용할 수 없다.

				- username: nick!user@host 에서 user 부분
				- realname: 공백이 있을 수 있다.

				작성된 username은 클라이언트가 선호하는 것이지만, 서버들은 user에 등록할 때 약간 수정하거나 자를 수 있다. username의 최고 길이는 USERLEN 005 인자에 의해 정해진다.

				몇 서버들은 연결중인 클라이언트의 username을 자동으로 Ident Protocol에 의해 정해버린다. 
				이런 서버들에서는, Ident를 통해 회수된 username은 클라이언트가 제출한 것보다 선호된다.

				이 서버들에 접속할 때, 만약 체줄된 username이 사용되면, 일반적으로 user-set임을 나타내기 위해 타일(~)이 접두사로 붙는다.

				두 번째, 세 번째 인자는 참조한 소스와 서버가 실행중인 소프트웨어에 따라 다른 정의를 가진다. 예상 못한 결과를 막기 위해 항상 0과 *를 보내기를 추천한다.

				클라이언트가 접속 등록이 완료된 후에 USER 명령을 보내려고 하면 ERR_ALREADYREGISTERED 응답이 보내지고 명령은 무시된다.
 */
void Cuser::execute(ChannelManager &channelManager,
					UserManager &userManager,
					Network &network,
					struct CommandChunk commandChunk)
{
	User *user = userManager.getUserByFd(commandChunk.fd);
	vector<string> param = commandChunk.parameters;
	(void)channelManager;

	if (param.size() < 3)
	{
		string msg = UserManager::makeMessage(ERR_NEEDMOREPARAMS, user->getNickname(), "Need more Parameter");
		network.sendToUser2(user->getFd(), msg);
		return;
	}
	else if (user->getIsRegistered())
	{
		string msg = UserManager::makeMessage(ERR_ALREADYREGISTERED, user->getNickname(), "User is already registered");
		network.sendToUser2(user->getFd(), msg);
		return;
	}

	user->setUserName(param[0]);
	user->setRealName(commandChunk.parameterLast);
}