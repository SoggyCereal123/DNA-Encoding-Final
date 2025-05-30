// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BasePair.generated.h"

/**
 * 
 */
UCLASS()
class TERMATH_API UBasePair : public UObject
{
	GENERATED_BODY()

public:
	// Sets the default values
	UBasePair();

	// List of the different base pair types
	TArray<FName> BasePairTypes;

	// How they effect the value of the gene
	bool bMultiply;
	bool bDivide;

	// The Default Value for Base Pairs
	float Value;

	// Exempt from 'A-T G-C' rule
	bool bIsExempt;

	// The Stored Type
	FName Type;
};
