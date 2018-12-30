#ifndef SIMULATOR9492YN_MINUS_H
#define SIMULATOR9492YN_MINUS_H

#include "BinaryExpression.h"

/**
 * Minus expression
 */
class Minus : public BinaryExpression {
public:
    // constructor - uses super class constructor
    Minus(Expression* leftExp, Expression* rightExp):BinaryExpression(leftExp,rightExp){}
    double calculate() override{
        return this->getLeftExp()->calculate() - this->getRightExp()->calculate();
    }
};

#endif

