#ifndef SIMULATOR9492YN_DIVIDE_H
#define SIMULATOR9492YN_DIVIDE_H

#include "BinaryExpression.h"

/**
 * Dividing expression
 */
class Divide : public BinaryExpression {
public:
    // Constructor
    Divide(Expression* leftExp, Expression* rightExp):BinaryExpression(leftExp,rightExp){}
    double calculate() override{
        if(this->getRightExp()->calculate() == 0){
            // cannot divide by 0
            throw exception();
        }
        // Return the calculation of the dividing operator
        return this->getLeftExp()->calculate() / this->getRightExp()->calculate();
    }
};

#endif