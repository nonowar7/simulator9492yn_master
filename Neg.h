#ifndef SIMULATOR9492YN_MASTER_NEG_H
#define SIMULATOR9492YN_MASTER_NEG_H

#include "UnaryExpression.h"

/**
 * Neg expression
 */
class Neg : public UnaryExpression {
public:
    // Constructor
   explicit Neg(Expression* ex):UnaryExpression(ex){}

    // calculation as negation by -1 multiplication
    double calculate() override{
        return -1 * this->getExp()->calculate();
    }
};

#endif
