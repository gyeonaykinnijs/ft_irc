#include "Csquit.hpp"

/*

### SQUIT
`SQUIT <server> <comment>`
	- <서버>가 네트워크를 종료합니다.
	- RFC 1459에 정의되어 있습니다.

*/
void Squit::execute(ChannelManager &channelManager,
					UserManager &userManager,
					Network &network,
					struct CommandChunk commandChunk)
{

	User *user = userManager.getUserByFd(commandChunk.fd);
	vector<string> param = commandChunk.parameters;

	if (user->getAuth() == User::ADMIN)
	{
		/**
		 * @brief 
		 * 		프로그램 종료
		 */

		exit(1);
	} 
	else 
	{
		/**
		 * @brief 
		 * 
		 * 		권한 없는 유저 ERROR
		 * 
		 */
	}
}