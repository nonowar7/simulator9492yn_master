#ifndef NEWSIMULATOR_WHILECOMMAND_H
#define NEWSIMULATOR_WHILECOMMAND_H

#include "TableManager.h"
#include "Threader.h"
#include "ConditionCommand.h"

class WhileCommand : public ConditionCommand{
public:
    explicit WhileCommand(BooleanExpression* booleanExpression): ConditionCommand(booleanExpression){}
    void doCommand() override;
};

#endif 
