

#ifndef SIMULATOR9492YN_MASTER_UPDATEVARCOMMAND_H
#define SIMULATOR9492YN_MASTER_UPDATEVARCOMMAND_H

#include "Command.h"
#include <string>
#include <vector>

using namespace std;

/*
 * responsibility - invocation of variable update
 * adding data to tables and informing simulator)
 */
class UpdateVarCommand : public Command{

private:
    // members
    string var;
    string value;

public:

    // ctor
    UpdateVarCommand(vector<string> line) {
        this->var = line.at(0);
        this->value = line.at(2);
    }

    void doCommand() override;

};


#endif //SIMULATOR9492YN_MASTER_UPDATEVARCOMMAND_H
