
#include "UBCConsumableBase.h"

void UUBCConsumableBase::OnUse_Implementation(AUBCCharacter* user)
{
}

bool UUBCConsumableBase::CanUse(AUBCCharacter* user)
{
	return true;
}

bool UUBCConsumableBase::Use(AUBCCharacter* user)
{
	if (CanUse(user))
	{
		OnUse(user);
		return true;
	}

	return false;
}
