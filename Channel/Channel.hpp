#ifndef __CHANNEL_HPP__
#define __CHANNEL_HPP__

#include "../defines.hpp"
#include "../User/User.hpp"
class Channel
{

public:
	Channel();
	~Channel();
	

	/**
	 * @brief Set the Channel Name object
	 * 
	 * 			Setter
	 */
	void setChannelName(const string channelName);
	void setMakeUser(const User *user);
	void setChannelKey(const string channelKey);
	void setCurSizeUser(const int size);


	/**
	 * @brief Get the Channel Name object
	 * 
	 * 			Getter
	 */
	string getChannelName() const;
	User* getMakeUser() const;
	string getChannelKey() const;
	int getCurSizeUser() const;
	int getMaxSizeUser() const;



	/**
	 * @brief 
	 * 
	 * @param user 
	 * 
	 * 			Insert User
	 */
	void addJoinUser(User *user);

	/**
	 * @brief 
	 * 
	 * @param user 
	 * 
	 * 			Delete User
	 */
	void deleteJoinUser(User user);

	/**
	 * @brief Get the Join User object
	 * 
	 * @return std::map<string, User *> 
	 * 
	 * 	return Insert All User
	 */
	std::map<string, User *> getJoinUser();


	/**
	 * @brief 
	 * 
	 * 				ENUM
	 * 
	 */

	enum Mode
	{
		WAIT, TALKING, ELSE
	};

private:
	string channelName;
	string channelKey;


	/**
	 * @brief 
	 * 
	 * 		채널 생성한 사람
	 */
	User *makeUser;
	
	/**
	 * @brief 
	 * 
	 * 		채널에 참가하고 있는 사람 list
	 * 
	 */
	map<string, User *> joinUser;

	/**
	 * @brief Channel user Size
	 * 
	 */
	int maxSizeUser;
	int curSizeUser;
};

#endif