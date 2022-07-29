#include "./Cpass.hpp"

void Cpass::execute(const struct CommandChunk commandChunk)
{
	std::string password = commandChunk.parameter[0];
	findUserByFd(commandChunk.fd)->setPasswd(password);
}