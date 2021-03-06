#include "IfCommand.h"

/**
 * doCommand in ifCommand checks if the boolean expression is true,
 * If it does, it preform all the commands in the vector toExecute.
 */
void IfCommand::doCommand() {
    BooleanExpression* boolExp = getBoolExpression();
    vector<Command*> toExecute = getCommands();
    // If the boolean expression is true, we do all the commands in the scope
    if(boolExp->calculate()){
        for(auto command: toExecute){
            command->doCommand();
        }
    }
}