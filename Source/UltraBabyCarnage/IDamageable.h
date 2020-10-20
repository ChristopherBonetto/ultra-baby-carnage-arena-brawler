
#pragma once

#include "CoreMinimal.h"

class ULTRABABYCARNAGE_API IDamageable
{

public:

	virtual bool TakeDamage(const int& damage) = 0;

};
