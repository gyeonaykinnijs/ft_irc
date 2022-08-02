#ifndef __DEFINES_HPP__
#define __DEFINES_HPP__

#include <vector>
#include <map>
#include <queue>
#include <string>
#include <iostream>
#include <utility>

using namespace std;

#define ERROR 1


// Reply Code
#define RPL_WELCOME "001"
#define RPL_YOURHOST "002"
#define RPL_CREATED "003"
#define RPL_MYINFO "004"
#define ERR_NEEDMOREPARAMS "461"
#define ERR_ALREADYREGISTERED "462"
#define ERR_NONICKNAMEGIVEN "431"
#define ERR_ERRONEOUSNICKNAME "432"
#define ERR_NICKNAMEINUSE "433"
#define ERR_BADCHANNELKEY "475"
#define ERR_CHANNELISFULL "471"
#define ERR_NOSUCHCHANNEL "403"
#define ERR_TOOMANYCHANNELS "405"
#define ERR_USERNOTINCHANNEL "441"
#define RPL_TOPIC "332"
#define RPF_NOTOPIC "331"
#define ERR_NORECIPIENT "411"
#define ERR_NOTEXTTOSEND "412"
#define ERR_CANNOTSENDTOCHAN "404"
#define ERR_NOSUCHNICK "401"
#define ERR_NOTONCHANNEL "442"
#define RPL_LIST "322"
#define RPL_LISTEND "323"


#endif