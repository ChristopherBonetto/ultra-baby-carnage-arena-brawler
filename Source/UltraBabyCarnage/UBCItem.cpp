// Fill out your copyright notice in the Description page of Project Settings.

#include "UBCItem.h"

UBCItem::UBCItem()
{
}

UBCItem::~UBCItem()
{
}

int UBCItem::GetAttackValue() const
{
	return attackValue;
}

void UBCItem::SetAttackValue(const int& value)
{
	this->attackValue = value;
}

bool UBCItem::Attack(IDamageable* target)
{
	return target->TakeDamage(attackValue);
}
