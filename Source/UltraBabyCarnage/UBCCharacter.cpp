
#include "UBCCharacter.h"

AUBCCharacter::AUBCCharacter()
{
}

void AUBCCharacter::BeginPlay()
{
	death.AddDynamic(this, &AUBCCharacter::OnDeath);
	ACharacter::BeginPlay();
}

void AUBCCharacter::OnDeath_Implementation(AUBCCharacter* character, AActor* causer) {}