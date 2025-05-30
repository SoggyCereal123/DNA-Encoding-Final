// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/SkeletalMeshComponent.h"
#include "RyanTermath.h"
#include "Components/PoseableMeshComponent.h"
#include "Gene.h"

UGene::UGene(): IndiValue(0), DepValue(0), FinalValue(0)
{
	PoseableMeshComponent = nullptr;
	List = {TEXT("E"), TEXT("P"), TEXT("R")};
	bIsBroken = false;
}

void UGene::Mutate(UGene* MutatedGene)
{
	UE_LOG(LogTemp, Log, TEXT("Mutate has been called!"))

	for (FName Bone : MutatedGene->ControlledBones)
	{
		// Gets All The Bone's Transform Properties
		FVector BoneScale = PoseableMeshComponent->GetBoneScaleByName(Bone, EBoneSpaces::ComponentSpace);
		// Gives a Chance the Bone will be mutated
		int32 TypeOfChange = FMath::RandRange(0, 150);
		if (TypeOfChange <= 25)
		{
			PoseableMeshComponent->SetBoneScaleByName(Bone, BoneScale + FinalValue / 2, EBoneSpaces::ComponentSpace);
		}
	}
}

void UGene::CascadeMutations()
{
	int32 AmountOfGenes = Termath->Genome.Num() * Termath->MutationRate;

	TArray<UGene*> UnmutatedGenes;
	for (UGene* Gene : Termath->Genome)
	{
		if (Gene && !Gene->WasMutated)
		{
			UnmutatedGenes.Add(Gene);
		}

		if (UnmutatedGenes.Num() >= AmountOfGenes)
			break;
	}

	for (int32 i = 0; i < UnmutatedGenes.Num(); i++)
	{
		if (UnmutatedGenes.Num() == 0) break;

		int32 RandomGeneIndex = FMath::RandRange(0, UnmutatedGenes.Num() - 1);
		UGene* ChosenGene = UnmutatedGenes[RandomGeneIndex];

		if (IsValid(ChosenGene))
		{
			ChosenGene->Mutate(ChosenGene);
			UnmutatedGenes.RemoveAt(RandomGeneIndex);
		}
	}
}
