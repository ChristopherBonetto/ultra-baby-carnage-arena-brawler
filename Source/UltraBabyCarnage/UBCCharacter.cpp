
#include "UBCCharacter.h"

AUBCCharacter::AUBCCharacter()
{
	death.AddDynamic(this, &AUBCCharacter::OnDeath);
}

void AUBCCharacter::OnDeath_Implementation(AUBCCharacter* character) {}