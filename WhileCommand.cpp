#include "WhileCommand.h"
#include <iostream>

/**
 * doCommand preform all the commands in the vector if the boolean
 * Expression is true
 */
void WhileCommand::doCommand() {
    // Get the boolean expression
    BooleanExpression* boolExp = this->getBoolExpression();
    // Get all the commands to execute
    vector<Command*> toExecute = this->getCommands();
    // while the condition is true preform all the commands
    while(boolExp->calculate()){
        for(auto command: toExecute){
            command->doCommand();
        }
    }
}