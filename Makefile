TARGET = ircserv
CPP = c++
FLAGS = -g -std=c++98 -Wall -Wextra -Werror
DIR = ./
SRCS = main.cpp\
		User/User.cpp User/UserManager.cpp\
		Channel/Channel.cpp Channel/ChannelManager.cpp\
		Network/Network.cpp\
		Server/Server.cpp\
		Logger/Logger.cpp\
		Command/Cjoin.cpp Command/Ckick.cpp Command/Cnick.cpp Command/Coper.cpp Command/Cpart.cpp Command/Cpass.cpp\
		Command/Cping.cpp Command/Cpong.cpp Command/Cquit.cpp Command/Cuser.cpp Command/Cnotice.cpp Command/Cprivmsg.cpp

OBJS = $(SRCS:.cpp=.o)

all : $(TARGET)
$(TARGET) : $(OBJS)
	$(CPP) $(FLAGS) -o $(TARGET) $^
%.o : %.cpp
	$(CPP) $(FLAGS) -o $@ -c $<
clean :
	rm -rf $(OBJS)
fclean : clean
	rm -rf $(TARGET)
re : 
	make fclean
	make all
.PHONY : all clean fclean re