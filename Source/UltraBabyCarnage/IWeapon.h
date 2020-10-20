// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IDamageable.h"

/**
 * 
 */

class ULTRABABYCARNAGE_API IWeapon
{

public:

	virtual bool Attack(IDamageable* damageable) = 0;

};
