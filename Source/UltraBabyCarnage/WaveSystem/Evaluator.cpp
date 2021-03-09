
#include "Evaluator.h"

float UEvaluator::operator () (float in) const 
{
	float out;
	Evaluate(in, out);
	return out;
}