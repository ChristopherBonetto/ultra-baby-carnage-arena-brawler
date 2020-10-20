// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IWeapon.h"
#include "IDamageable.h"

/**
 * 
 */

class ULTRABABYCARNAGE_API UBCItem :
	public IWeapon
{

protected:

	UPROPERTY(EditAnywhere)
	int attackValue;

public:

	UBCItem();

	~UBCItem();

	UFUNCTION()
	int GetAttackValue() const;
	
	UFUNCTION()
	void SetAttackValue(const int& value);

	UFUNCTION()
	virtual bool Attack(IDamageable* target) override;

};
