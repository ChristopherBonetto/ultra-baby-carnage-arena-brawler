// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "UBCWaveInfo.h"
#include "UBCWaveAsset.generated.h"

/**
 * Asset that contains information about a wave.
 */

UCLASS()
class ULTRABABYCARNAGE_API UUBCWaveAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FUBCWaveInfo info;

public:

	/**
	* Returns the delay between rounds.
	*/

	UFUNCTION(BlueprintCallable)
	float GetRoundDelay() const;

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
	TSubclassOf<AActor> GetEnemyClass() const;

	UFUNCTION(BlueprintCallable)
	int GetEnemyMultiplier() const;

};
