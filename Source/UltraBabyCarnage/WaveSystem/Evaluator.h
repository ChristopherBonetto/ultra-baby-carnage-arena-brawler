// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Evaluator.generated.h"

/**
 * Object
 */

UCLASS(Abstract, Blueprintable)
class ULTRABABYCARNAGE_API UEvaluator : 
	public UObject
{
	GENERATED_BODY()
	
public:

	/**
	* Evaluates the input and returns an output.
	*/

	UFUNCTION(BlueprintImplementableEvent)
	void Evaluate(float in, float& out) const;

	/**
	* Evaluates the input.
	*/

	float operator () (float in) const;

};
