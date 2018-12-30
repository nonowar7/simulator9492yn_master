#ifndef SIMULATOR9492YN_MULTIPLY_H
#define SIMULATOR9492YN_MULTIPLY_H

#include "BinaryExpression.h"

/**
 * Multiply expression
 */
class Multiply : public BinaryExpression {
public:
    // Constructor
    Multiply(Expression* leftExp, Expression* rightExp):BinaryExpression(leftExp,rightExp){}
    double calculate() override{
        return this->getLeftExp()->calculate() * this->getRightExp()->calculate();
    }
};

#endif
