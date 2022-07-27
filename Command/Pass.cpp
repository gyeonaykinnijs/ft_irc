#include "./Pass.hpp"

Pass::Pass() {

}

Pass::Pass(const Pass& copy) {

}

Pass& Pass::operator=(const Pass& origin) {

}

~Pass::Pass() {

}


void Pass::execute(const struct &commandChunk) {
	// User.password = 입력받은 password;
	// 비밀번호 맞는지 여부는 여기서 판단하지 않는다. 
	// PASS 는 여러 번 칠 수 있기 때문에 갱신만 해준다.
}
