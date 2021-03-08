
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

int UUBCWaveAsset::GetRoundSpawnCount(int round) const
{
	return (int)GetCurveValue(GetSpawnCurve(), round);
}

UCurveFloat* UUBCWaveAsset::GetSpawnDelayCurve() const
{
	return info.enemySpawnDelayCurve;
}

float UUBCWaveAsset::GetRoundSpawnDelay(int round) const
{
	return GetCurveValue(GetSpawnDelayCurve(), round);
}

UCurveFloat* UUBCWaveAsset::GetSpawnBatchCurve() const
{
	return info.enemySpawnBatchCurve;
}

int UUBCWaveAsset::GetRoundBatchSize(int round) const
{
	return GetCurveValue(GetSpawnBatchCurve(), round);
}

UCurveFloat* UUBCWaveAsset::GetHealthCurve() const
{
	return info.enemyHealthCurve;
}

int UUBCWaveAsset::GetRoundHealthValue(int round) const
{
	return (int)GetCurveValue(GetHealthCurve(), round);
}

UCurveFloat* UUBCWaveAsset::GetPowerCurve() const
{
	return info.enemyPowerCurve;
}

int UUBCWaveAsset::GetRoundPowerValue(int round) const
{
	return (int)GetCurveValue(GetPowerCurve(), round);
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