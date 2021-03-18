
#include "Evaluator.h"

float UEvaluator::operator()(float in) 
{
	float out;
	Evaluate(in, out);
	return out;
}