// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Evaluator.generated.h"

/**
 * Abstract object that takes an input value and returns an output value.
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

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void Evaluate(float in, float& out);

	/**
	* Evaluates the input.
	*/

	float operator () (float in);

};
