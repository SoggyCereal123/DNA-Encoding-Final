// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PoseableMeshComponent.h"
#include "BasePair.h"
#include "RyanTermath.h"


// Sets default values
ARyanTermath::ARyanTermath()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void ARyanTermath::BeginPlay()
{
	Super::BeginPlay();
	
	// Sets all the bone names in a group
	TArray<TArray<FName>> BoneGroups = GetBones();
	
	// Creates the Genome
	for (int32 i = 0; i <= GenomeLength; i++)
	{
		// Creates the gene, hello world!
		UGene* Gene = NewObject<UGene>();

		Gene->Termath = this;
		
		// Gives the Gene a type
		int32 SelectedType = FMath::RandRange(0, Gene->List.Num() - 1);
		Gene->Type = Gene->List[SelectedType];

		// Sets the Gene's base pairs and calculates its potential value from those base pairs
		CreateBasePairs(Gene);
		Gene->FinalValue = Gene->DepValue * Gene->IndiValue;
		UE_LOG(LogTemp, Log, TEXT("The Depndent Value is %f and the Indipendent Value is %f"), Gene->DepValue, Gene->IndiValue);
		// Sets the gene's final value to the Results divided
		Gene->FinalValue = 1.0f / (1.0f  + Gene->IndiValue / Gene->DepValue * DampingEffect);

		// Assigns the gene a bone group to control with a 15% chance to control less than the bone group.
		Gene->PoseableMeshComponent = GetPoseableMesh();
		int32 BoneGroup = FMath::RandRange(0, BoneGroups.Num() - 1);
		TArray<FName> SelectedGroup = BoneGroups[BoneGroup];

		int32 Chance = FMath::RandRange(0, 100);
		if (Chance <= SpecialGeneChance)
		{
			int32 ControlledBones = FMath::RandRange(1, SelectedGroup.Num());

			// Shuffle the selected group to avoid duplicates and pick the first N
			SelectedGroup.Sort([](const FName&, const FName&) {
				return FMath::RandBool();
			});

			for (int32 j = 0; j < ControlledBones && j < SelectedGroup.Num(); j++)
			{
				Gene->ControlledBones.Add(SelectedGroup[j]);
			}
		}
		else
		{
			for (int32 j = 0; j < SelectedGroup.Num(); j++)
			{
				Gene->ControlledBones.Add(SelectedGroup[j]);
			}
		}
		
		Genome.Add(Gene);
	}
}

// Called every frame
void ARyanTermath::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARyanTermath::EditGroup(TArray<FName>& TargetArray, TArray<FName>& OriginalArray, FName& Elem)
{
	// Adds the Element to a new array
	TargetArray.AddUnique(Elem);
	// Removes the Element from the Original Array
	OriginalArray.Remove(Elem);
}

TArray<TArray<FName>> ARyanTermath::GetBones() const
{
	// Gets the skeletal mesh
	UPoseableMeshComponent* PoseableMesh = GetPoseableMesh();
	
	// Loops over all the bones in the skeletal mesh, from there, we separate all the bones into 3 categories, Body, Arms, Legs.
	// Array for every bone name
	TArray<FName> AllNames;
	PoseableMesh->GetBoneNames(AllNames);

	TArray<FName> LegBones;
	TArray<FName> BodyBones;
	TArray<FName> ArmBones;
	
	for (FName Name : AllNames)
	{
		FString BoneName = Name.ToString();
		// Filter for the Body
		if (BoneName.Contains(TEXT("spine")) || BoneName.Contains(TEXT("clavicle")))
		{
			EditGroup(BodyBones, AllNames, Name);
		}
		
		// Filter for the Arms
		if (BoneName.Contains(TEXT("arm")) || BoneName.Contains(TEXT("hand"))
			|| BoneName.Contains(TEXT("metacarpal")) || BoneName.Contains(TEXT("index"))
			|| BoneName.Contains(TEXT("pinky")) || BoneName.Contains(TEXT("ring"))
			|| BoneName.Contains(TEXT("thumb")) || BoneName.Contains(TEXT("wrist")) && !BoneName.Contains("toe"))
		{
			EditGroup(ArmBones, AllNames, Name);
		}

		// Filter for the Legs
		if (BoneName.Contains(TEXT("thigh")) || BoneName.Contains(TEXT("calf"))
			|| BoneName.Contains(TEXT("foot")) || BoneName.Contains(TEXT("ankle"))
			|| BoneName.Contains(TEXT("ball")) || BoneName.Contains(TEXT("toe")))
		{
			EditGroup(LegBones, AllNames, Name);
		}
	}

	TArray<TArray<FName>> SortedBones;
	SortedBones.Add(LegBones);
	SortedBones.Add(ArmBones);
	SortedBones.Add(BodyBones);
	
	return SortedBones;
	
}

UPoseableMeshComponent* ARyanTermath::GetPoseableMesh() const
{
	// Gets all the skeletal mesh components
	TArray<UPoseableMeshComponent*> PoseableMeshComponents;
	GetComponents<UPoseableMeshComponent>(PoseableMeshComponents);

	for (UPoseableMeshComponent* CurrentMesh : PoseableMeshComponents)
	{
		if (IsValid(CurrentMesh))
		{
			if (CurrentMesh->GetName() == TEXT("Body"))
			{
				return CurrentMesh;
			}
		}
	}
	
	return nullptr;
}

void ARyanTermath::CreateBasePairs(UGene*& OwningGene)
{
	
	// Finds the amount of base pairs the gene will have
	int32 BasePairAmount = FMath::RandRange(7, 100);

	// For Loop for the main rung
	for (int32 i = 0; i <= BasePairAmount; i++)
	{
		// Creates the BasePair and initializes its type, this is for the Main Rung, so they are exempt
		UBasePair* BasePair = NewObject<UBasePair>();
		int32 SelectedType = FMath::RandRange(0, BasePair->BasePairTypes.Num() - 1);
		FName Type = BasePair->BasePairTypes[SelectedType];
		BasePair->Type = Type;

		// Add Exceptions for when the Selected Type is invalid with a 5 percent failure chance.
		int32 BreakChance = FMath::RandRange(0, 500);
		if (BreakChance <= 1)
		{
			BasePair->bIsExempt = true;
		}

		if (BasePair->Type == TEXT("A"))
		{
			BasePair->bDivide = true;
		}
		
		if (BasePair->Type == TEXT("T"))
		{
			BasePair->bDivide = true;
		}
		
		if (BasePair->Type == TEXT("G"))
		{
			BasePair->bMultiply = true;
		}
		
		if (BasePair->Type == TEXT("C"))
		{
			BasePair->bMultiply = true;
		}
		
		OwningGene->BasePairsMR.Add(BasePair);
	}

	// For Loop for the Dependent Rung
	for (int32 i = 0; i <= BasePairAmount; i++)
	{
		// Creates the BasePair
		UBasePair* BasePair = NewObject<UBasePair>();
		OwningGene->DPBasePair.Add(BasePair);

		// Changes the value
		if (OwningGene->BasePairsMR[i]->bIsExempt)
		{
			if (OwningGene->BasePairsMR[i]->Type == TEXT("A"))
			{
				BasePair->Type = TEXT("T");
				BasePair->bDivide = true;
			}
			if (OwningGene->BasePairsMR[i]->Type == TEXT("T"))
			{
				BasePair->Type = TEXT("A");
				BasePair->bDivide = true;
			}
			if (OwningGene->BasePairsMR[i]->Type == TEXT("G"))
			{
				BasePair->Type = TEXT("C");
				BasePair->bMultiply = true;
			}
			if (OwningGene->BasePairsMR[i]->Type == TEXT("C"))
			{
				BasePair->Type = TEXT("G");
				BasePair->bMultiply = true;
			}
		}
	}

	// Modify the Value for the Main Rung
	for (UBasePair* BasePair : OwningGene->BasePairsMR)
	{
		ModifyValue(BasePair, OwningGene->BasePairsMR, OwningGene->IndiValue);
	}

	for (UBasePair* BasePair : OwningGene->DPBasePair)
	{
		ModifyValue(BasePair, OwningGene->DPBasePair, OwningGene->DepValue);
	}
	
}

void ARyanTermath::ChangeBasePairType(UBasePair*& BasePair, FName ControlledType, bool PairType)
{
	if (BasePair->Type == ControlledType)
	{
		PairType = true;
	}
}

void ARyanTermath::ModifyValue(UBasePair*& BasePair, TArray<UBasePair*> Array, float& Value)
{
	// Sets the boolean operators to true.
	if (BasePair->Type == TEXT("A") || BasePair->Type == TEXT("T"))
	{
		BasePair->bDivide = true;
	}
	else if (BasePair->Type == TEXT("G") || BasePair->Type == TEXT("C"))
	{
		BasePair->bMultiply = true;
	}

	// Edits the values of the gene depending on the values
	if (BasePair->bMultiply == true)
	{
		for (UBasePair* Pair : Array)
		{
			if (Array.Find(Pair) >= 1)
			{
				Value = BasePair->Value + Value;
			}
		}
	}

	if (BasePair->bDivide == true)
	{
		for (UBasePair* Pair : Array)
		{
			if (Array.Find(Pair) >= 1)
			{
				Value = BasePair->Value - Value;
			}
		}
	}
}




