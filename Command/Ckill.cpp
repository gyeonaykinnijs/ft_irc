#include "Ckill.hpp"

/**
 * @brief 
 * 
 * @param channelManager 
 * @param userManager 
 * @param network 
 * @param commandChunk 
 * 
 * 
 * 		### KILL
		`KILL <client> <comment>`
		- 네트워크에서 <클라이언트>를 강제로 제거합니다.
		- 이 명령은 IRC 운영자만 실행할 수 있습니다.
		- RFC 1459에 정의되어 있습니다.
 */

void Kill::execute(ChannelManager &channelManager,
					UserManager &userManager,
					Network &network,
					struct CommandChunk commandChunk)
{

}