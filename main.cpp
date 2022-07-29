#include "./defines.hpp"
#include "./Server/Server.hpp"
int main(int ac, char **av)
{
    if (ac != 3)
    {
        cout << "YOU NEED 2 PARAMETERS" << endl;
        return ERROR;
    }
    else
    {
        Server server;
        server.init();
        server.run();
    }
    (void)av;
    return 0;
}