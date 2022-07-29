#ifndef __DEFINES_HPP__
#define __DEFINES_HPP__

using namespace std;

#include <vector>
#include <map>
#include <queue>
#include <string>
#include <iostream>
#include <utility>

#include "Channel/Channel.hpp"
#include "Channel/ChannelManager.hpp"
#include "User/User.hpp"
#include "User/UserManager.hpp"

// 명령어 다 넣기
#include "Command/ICommand.hpp"
#include "Command/Cpass.hpp"
#include "Command/Cnick.hpp"
#include "Command/Cuser.hpp"


// 견님 헤더 넣기
#include "Network/Network.hpp"

// Error Code
#define ERROR 1
#define ERR_NEEDMOREPARAMS 461
#define ERR_ALREADYREGISTERED 462


#endif