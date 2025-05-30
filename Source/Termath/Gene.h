// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Gene.generated.h"

/**
 * 
 */

class UMeshComponent;
class UPoseableMeshComponent;
class UBasePair;
class ARyanTermath;
UCLASS(BlueprintType)
class TERMATH_API UGene : public UObject
{
	GENERATED_BODY()

public:
	// Sets the default values
	UGene();

	// Type of Gene
	UPROPERTY(EditAnywhere)
	TArray<FName> List;
	
	// Controlling Mesh
	UPROPERTY(EditAnywhere)
	TArray<UStaticMeshComponent*> ControllingMeshes;
	
	// Value
	UPROPERTY(EditAnywhere)
	float IndiValue;

	UPROPERTY(EditAnywhere)
	float DepValue;

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAcess = true), BlueprintReadOnly)
	float FinalValue;

	// Type
	FName Type;
	
	// Controlling Meshes
	TArray<FName> ControlledBones;

	// The Mesh They Control
	UPoseableMeshComponent* PoseableMeshComponent;
	
	// The Function to Mutate
	UFUNCTION(BlueprintCallable)
	void Mutate(UGene* MutatedGene);

	// List of the BasePairs a gene has
	TArray<UBasePair*> BasePairsMR;
	TArray<UBasePair*> DPBasePair;

	// Mark this Gene as broken
	bool bIsBroken;

	// Owning Termath
	ARyanTermath* Termath;

	bool WasMutated;

	UFUNCTION(BlueprintCallable)
	void CascadeMutations();
};
