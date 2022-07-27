#include "Nick.hpp"

Nick::Nick() {

}

Nick::Nick(const Nick& copy) {

}

Nick& Nick::operator=(const Nick& origin) {

}

~Nick::Nick() {

}


void Nick::execute(const struct &commandChunk) {
	// user->server
	if (canChangeNickname(commandChunk.nickname)) {
		User.nickname = commandChunk.nickname;
	} else {
		// send error code
	}
	
	// server-user
	// 채널 내 전체에게 user의 nickname이 commandChunk.nickname으로 바뀌었다는 메시지 보내주기
}
