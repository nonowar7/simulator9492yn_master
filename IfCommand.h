#ifndef NEWSIMULATOR_IFCOMMAND_H
#define NEWSIMULATOR_IFCOMMAND_H

#include "ConditionCommand.h"

/**
 * If command is a condition command.
 */
class IfCommand : public ConditionCommand{
public:
    explicit IfCommand(BooleanExpression* booleanExpression):ConditionCommand(booleanExpression){}
    void doCommand() override;
};

#endif
