// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gene.h"
#include "RyanTermath.generated.h"

class USkeletalMeshComponent;
class UBasePair;
class UPoseableMeshComponent;
UCLASS()
class TERMATH_API ARyanTermath : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARyanTermath();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<UGene*> Genome;

	UFUNCTION(BlueprintCallable)
	UPoseableMeshComponent* GetPoseableMesh() const;
	
	UPROPERTY(EditAnywhere)
	float MutationRate;
	
private:
	
	UPROPERTY(EditAnywhere)
	int32 GenomeLength;

	UPROPERTY(EditAnywhere)
	float DefaultValue;
	
	static void EditGroup(TArray<FName>& TargetArray, TArray<FName>& OriginalArray, FName& Elem);

	TArray<TArray<FName>> GetBones() const;

	UPROPERTY(EditAnywhere)
	int32 SpecialGeneChance;

	UPROPERTY(EditAnywhere)
	float AmplificationValue;

	static void CreateBasePairs(UGene*& OwningGene);

	static void ChangeBasePairType(UBasePair*& BasePair, FName ControlledType, bool PairType);

	static void ModifyValue(UBasePair*& BasePair, TArray<UBasePair*> Array, float& Value);
	
	UPROPERTY(EditAnywhere)
	int32 DampingEffect;
	
};
