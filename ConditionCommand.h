#ifndef NEWSIMULATOR_CONDITIONCOMMAND_H
#define NEWSIMULATOR_CONDITIONCOMMAND_H

#include "Command.h"
#include "BooleanExpression.h"

/**
 * All the commands that their preform depends in condition.
 */
class ConditionCommand : public Command{
    // The condition represent as boolean expression
    BooleanExpression* booleanExpression;
    // All the commands to perform if the condition is true
    vector<Command*> commands;
public:
    // Constructor to condition command
    explicit ConditionCommand(BooleanExpression* booleanExpression){
        this->booleanExpression = booleanExpression;
    }
    // Add command to perform to the vector
    void addCommand (Command* command){
        this->commands.push_back(command);
    }
    // Return all the commands to perform if the condition is true
    vector<Command*> getCommands(){
        return this->commands;
    }
    // Return the boolean expression
    BooleanExpression* getBoolExpression(){
        return this->booleanExpression;
    }
    // Do the command
    virtual void doCommand()=0;
};

#endif
