#ifndef SIMULATOR9492YN_EXPRESSION_H
#define SIMULATOR9492YN_EXPRESSION_H

#include "Command.h"
using namespace std;

/**
 * Expression is an abstract class, with pure virtual method calculate.
 */
class Expression {
public:
    /**
     * Calculate the expression and return the result in double
     */
    virtual double calculate()=0;
};

#endif