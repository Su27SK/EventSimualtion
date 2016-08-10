// NumericalComp.h: interface for the NumericalComp class.
//
//////////////////////////////////////////////////////////////////////

/** The class intends to overcome the numerical error
	Call this class if you want to do the addition of two numbers with the opposite sign
	or the substraction with the same sign
*/

#define Small_Value 1e-10 
#define epsilon_2 1e-10

class NumericalComp
{
public:
	static double add(double op1, double op2);
	static double sub(double op1, double op2);
};
