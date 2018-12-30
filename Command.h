#ifndef SIMULATOR9492YN_MASTER_COMMAND_H
#define SIMULATOR9492YN_MASTER_COMMAND_H

#include <string>
#include <vector>

using namespace std;

/**
 * Command is an abstract class,
 * That has pure virtual method do command that execute the command.
 */
class Command {
public:
    // Preform the command
    virtual void doCommand()=0;
};

#endif
