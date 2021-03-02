// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/DataTable.h"
#include "../UBCCharacter.h"
#include "UBCWaveInfo.h"
#include "UBCWaveAsset.generated.h"

/**
 * Asset that contains information about a wave.
 */

UCLASS()
class ULTRABABYCARNAGE_API UUBCWaveAsset : 
	public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FUBCWaveInfo info;

protected:

	static float GetCurveValue(UCurveFloat* curve, int round);

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

	UFUNCTION(BlueprintCallable)
	UCurveFloat* GetSpawnCurve() const;

	UFUNCTION(BlueprintCallable)
	int GetRoundSpawnCount(int round) const;

	UFUNCTION(BlueprintCallable)
	UCurveFloat* GetSpawnDelayCurve() const;

	UFUNCTION(BlueprintCallable)
	float GetRoundSpawnDelay(int round) const;

	UFUNCTION(BlueprintCallable)
	UCurveFloat* GetSpawnBatchCurve() const;

	UFUNCTION(BlueprintCallable)
	int GetRoundBatchSize(int round) const;

	UFUNCTION(BlueprintCallable)
	UCurveFloat* GetHealthCurve() const;

	UFUNCTION(BlueprintCallable)
	int GetRoundHealthValue(int round) const;

	UFUNCTION(BlueprintCallable)
	UCurveFloat* GetPowerCurve() const;

	UFUNCTION(BlueprintCallable)
	int GetRoundPowerValue(int round) const;

	UFUNCTION(BlueprintCallable)
	int GetBaseBudget() const;

	UFUNCTION(BlueprintCallable)
	int GetMinBudgetMultiplier() const;

	UFUNCTION(BlueprintCallable)
	int GetMaxBudgetMultiplier() const;

	UFUNCTION(BlueprintCallable)
	UDataTable* GetItemCostTable() const;

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
