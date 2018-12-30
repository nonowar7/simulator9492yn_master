
#ifndef SIMULATOR9492YN_MASTER_OPENSERVERCOMMAND_H
#define SIMULATOR9492YN_MASTER_OPENSERVERCOMMAND_H

#include "Command.h"
#include "Threader.h"
#include <string>
#include <vector>

using namespace std;

/*
 * responsibility - connecting the simulator
 * as a client to a server (the program).
 */
class OpenServerCommand : public Command {

    // members
    int port;
    int hz;

public :

    // ctor
    explicit OpenServerCommand(vector<string>line);

    // creating a connection
    void doCommand() override;
    int openServer(int port, int Hz);

    // opening threads
    void createThread(int socket) ;

};

#endif //SIMULATOR9492YN_MASTER_OPENSERVERCOMMAND_H
