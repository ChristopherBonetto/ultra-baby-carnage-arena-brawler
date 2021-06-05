// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/DataTable.h"
#include "../UBCCharacter.h"
#include "UBCWaveInfo.h"
#include "Evaluator.h"
#include "UBCWaveAsset.generated.h"

/**
 * Asset that contains information about a wave.
 */

UCLASS()
class ULTRABABYCARNAGE_API UUBCWaveAsset : 
	public UPrimaryDataAsset
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadWrite)
	UEvaluator* maxActiveEnemyCountEquation;

	UPROPERTY(BlueprintReadWrite)
	UEvaluator* enemySpawnEquation;
	
	UPROPERTY(BlueprintReadWrite)
	UEvaluator* enemySpawnDelayEquation;
	
	UPROPERTY(BlueprintReadWrite)
	UEvaluator* enemySpawnBatchEquation;
	
	UPROPERTY(BlueprintReadWrite)
	UEvaluator* enemyHealthEquation;
	
	UPROPERTY(BlueprintReadWrite)
	UEvaluator* enemyPowerEquation;	

	UPROPERTY(BlueprintReadWrite)
	UEvaluator* enemySpeedEquation;
	
	UPROPERTY(BlueprintReadWrite)
	UEvaluator* weaponBudgetMultiplierEquation;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FUBCWaveInfo info;

protected:

	static float GetCurveValue(UCurveFloat* curve, int round);

	UEvaluator* GetEquation(UEvaluator*& eqInstance, const TSubclassOf<UEvaluator>& evalClass);

public:

	/**
	* Returns the delay between rounds.
	*/

	UFUNCTION(BlueprintCallable)
	float GetRoundDelay() const;

	UFUNCTION(BlueprintCallable)
	int GetEnemyMultiplier() const;

	/**
	* Returns the maximum number of active enemies at the same time.
	*/

	UFUNCTION(BlueprintCallable)
	int GetMaxActiveEnemiesCount() const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UEvaluator* GetSpawnEquation();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetRoundSpawnCount(int round);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UEvaluator* GetMaxActiveEnemiesCountEquation();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetRoundMaxActiveEnemiesCount(int round);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UEvaluator* GetSpawnDelayEquation();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetRoundSpawnDelay(int round);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UEvaluator* GetSpawnBatchEquation();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetRoundBatchSize(int round);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UEvaluator* GetHealthEquation();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetRoundHealthValue(int round);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UEvaluator* GetPowerEquation();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetRoundPowerValue(int round);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UEvaluator* GetSpeedEquation();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetRoundSpeedValue(int round);

	UFUNCTION(BlueprintCallable)
	int GetBaseBudget() const;

	UFUNCTION(BlueprintCallable)
	int GetMinBudgetMultiplier() const;

	UFUNCTION(BlueprintCallable)
	int GetMaxBudgetMultiplier() const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UEvaluator* GetBudgetMultiplierEquation();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetRoundBudgetMultiplier(int round);

	UFUNCTION(BlueprintCallable)
	UCurveFloat* GetTierCurve() const;

	UFUNCTION(BlueprintCallable)
	int GetRoundTier(int round) const;

	UFUNCTION(BlueprintCallable)
	UDataTable* GetItemCostTableOfTier(int tier) const;

	UFUNCTION(BlueprintCallable)
	UCurveFloat* GetItemIndexOffsetCurve() const;

	UFUNCTION(BlueprintCallable)
	int GetRoundItemIndexOffset(int round) const;

	UFUNCTION(BlueprintCallable)
	UCurveFloat* GetMaxItemIndexCurve() const;

	UFUNCTION(BlueprintCallable)
	int GetRoundMaxItemIndex(int round) const;

	UFUNCTION(BlueprintCallable)
	UCurveFloat* GetDefaultItemIndexCurve() const;

	UFUNCTION(BlueprintCallable)
	int GetRoundDefaultItemIndex(int round) const;

	UFUNCTION(BlueprintCallable)
	TSubclassOf<AUBCCharacter> GetEnemyClass() const;

};
