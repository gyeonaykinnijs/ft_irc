TARGET = ircserv
CPP = c++
FLAGS = -g -std=c++98 -Wall -Wextra -Werror
DIR = ./
SRCS = main.cpp\
		User/User.cpp User/UserManager.cpp\
		Channel/Channel.cpp Channel/ChannelManager.cpp\
		Network/Network.cpp\
		Server/Server.cpp
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