#include <cmath>
#include "NumericalComp.h"

double NumericalComp::add(double op1, double op2)
{
	if(op1 * op2 >= 0)
		return (op1 + op2);

	double sum = op1 + op2;

	if(op2 != 0.0 && fabs(op1 / op2 + 1.0) < Small_Value)
		sum = 0;

	return sum;
}

double NumericalComp::sub(double op1, double op2)
{
	if(op1 * op2 <= 0)
		return (op1 - op2);

	double diff = op1 - op2;

	if(op2 != 0.0 && fabs(op1 /op2 - 1.0) < Small_Value)
		diff = 0;
	
	return diff;
}
