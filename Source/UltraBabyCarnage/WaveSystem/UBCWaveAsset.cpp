
#include "UBCWaveAsset.h"

float UUBCWaveAsset::GetCurveValue(UCurveFloat* curve, int round)
{
	return curve->IsValidLowLevelFast() ?
		curve->GetFloatValue(round) :
		0.f;
}

float UUBCWaveAsset::GetRoundDelay() const
{
	return info.roundDelay;
}

int UUBCWaveAsset::GetEnemyMultiplier() const
{
	return info.enemyMultiplier;
}

int UUBCWaveAsset::GetMaxActiveEnemiesCount() const
{
	return info.maxActiveEnemiesCount;
}

UCurveFloat* UUBCWaveAsset::GetSpawnCurve() const
{
	return info.enemySpawnCurve;
}

UEvaluator * UUBCWaveAsset::GetSpawnEquation()
{
	if (!enemySpawnEquation && info.enemySpawnEquation.Get()->IsValidLowLevelFast())
	{
		enemySpawnEquation = NewObject<UEvaluator>((UObject*)this, info.enemySpawnEquation.Get());
	}

	return enemySpawnEquation;
}

int UUBCWaveAsset::GetRoundSpawnCount(int round)
{
	//return (int)GetCurveValue(GetSpawnCurve(), round);
	return (int)(*GetSpawnEquation())(round);
}

UCurveFloat* UUBCWaveAsset::GetSpawnDelayCurve() const
{
	return info.enemySpawnDelayCurve;
}

UEvaluator * UUBCWaveAsset::GetSpawnDelayEquation()
{
	if (!enemySpawnDelayEquation && info.enemySpawnDelayEquation.Get()->IsValidLowLevelFast())
	{
		enemySpawnDelayEquation = NewObject<UEvaluator>((UObject*)this, info.enemySpawnDelayEquation.Get());
	}

	return enemySpawnDelayEquation;
}

float UUBCWaveAsset::GetRoundSpawnDelay(int round)
{
	//return GetCurveValue(GetSpawnDelayCurve(), round);
	return (int)(*GetSpawnDelayEquation())(round);
}

UCurveFloat* UUBCWaveAsset::GetSpawnBatchCurve() const
{
	return info.enemySpawnBatchCurve;
}

UEvaluator * UUBCWaveAsset::GetSpawnBatchEquation()
{
	if (!enemySpawnBatchEquation && info.enemySpawnBatchEquation.Get()->IsValidLowLevelFast())
	{
		enemySpawnBatchEquation = NewObject<UEvaluator>((UObject*)this, info.enemySpawnBatchEquation.Get());
	}

	return enemySpawnBatchEquation;
}

int UUBCWaveAsset::GetRoundBatchSize(int round)
{
	//return GetCurveValue(GetSpawnBatchCurve(), round);
	return (int)(*GetSpawnBatchEquation())(round);
}

UCurveFloat* UUBCWaveAsset::GetHealthCurve() const
{
	return info.enemyHealthCurve;
}

UEvaluator * UUBCWaveAsset::GetHealthEquation()
{
	if (!enemyHealthEquation && info.enemyHealthEquation.Get()->IsValidLowLevelFast())
	{
		enemyHealthEquation = NewObject<UEvaluator>((UObject*)this, info.enemyHealthEquation.Get());
	}

	return enemyHealthEquation;
}

int UUBCWaveAsset::GetRoundHealthValue(int round)
{
	//return (int)GetCurveValue(GetHealthCurve(), round);
	return (int)(*GetHealthEquation())(round);
}

UCurveFloat* UUBCWaveAsset::GetPowerCurve() const
{
	return info.enemyPowerCurve;
}

UEvaluator * UUBCWaveAsset::GetPowerEquation()
{
	if (!enemyPowerEquation && info.enemyPowerEquation.Get()->IsValidLowLevelFast())
	{
		enemyPowerEquation = NewObject<UEvaluator>((UObject*)this, info.enemyPowerEquation.Get());
	}

	return enemyPowerEquation;
}

int UUBCWaveAsset::GetRoundPowerValue(int round)
{
	//return (int)GetCurveValue(GetPowerCurve(), round);
	return (int)(*GetPowerEquation())(round);
}

int UUBCWaveAsset::GetBaseBudget() const
{
	return info.baseBudget;
}

int UUBCWaveAsset::GetMinBudgetMultiplier() const
{
	return info.minBudgetMultiplier;
}

int UUBCWaveAsset::GetMaxBudgetMultiplier() const
{
	return info.maxBudgetMultiplier;
}

UEvaluator * UUBCWaveAsset::GetBudgetMultiplierEquation()
{
	if (!weaponBudgetMultiplierEquation && info.weaponBudgetMultiplierEquation.Get()->IsValidLowLevelFast())
	{
		weaponBudgetMultiplierEquation = NewObject<UEvaluator>((UObject*)this, info.weaponBudgetMultiplierEquation.Get());
	}

	return weaponBudgetMultiplierEquation;
}

int UUBCWaveAsset::GetRoundBudgetMultiplier(int round)
{
	return (int)(*GetBudgetMultiplierEquation())(round);
}

UCurveFloat * UUBCWaveAsset::GetTierCurve() const
{
	return info.itemTierCurve;
}

int UUBCWaveAsset::GetRoundTier(int round) const
{
	return (int)GetCurveValue(GetTierCurve(), round);
}

UDataTable * UUBCWaveAsset::GetItemCostTableOfTier(int tier) const
{
	int tierCount = info.itemTierTables.Num();
	return FMath::IsWithin(tier, 0, tierCount) ? 
		info.itemTierTables[tier] : 
		nullptr;
}

UCurveFloat * UUBCWaveAsset::GetItemIndexOffsetCurve() const
{
	return info.itemIndexOffsetCurve;
}

int UUBCWaveAsset::GetRoundItemIndexOffset(int round) const
{
	return (int)GetCurveValue(GetItemIndexOffsetCurve(), round);
}

UCurveFloat * UUBCWaveAsset::GetMaxItemIndexCurve() const
{
	return info.maxItemIndexCurve;
}

int UUBCWaveAsset::GetRoundMaxItemIndex(int round) const
{
	return (int)GetCurveValue(GetMaxItemIndexCurve(), round);
}

UCurveFloat * UUBCWaveAsset::GetDefaultItemIndexCurve() const
{
	return info.defaultItemIndexCurve;
}

int UUBCWaveAsset::GetRoundDefaultItemIndex(int round) const
{
	return GetCurveValue(GetDefaultItemIndexCurve(), round);
}

TSubclassOf<AUBCCharacter> UUBCWaveAsset::GetEnemyClass() const
{
	return info.enemyToSpawn;
}