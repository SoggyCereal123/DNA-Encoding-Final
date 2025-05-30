// Fill out your copyright notice in the Description page of Project Settings.

#include "Blueprint/UserWidget.h"
#include "Student.h"

// Sets default values
AStudent::AStudent()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStudent::BeginPlay()
{
	Super::BeginPlay();

	// Adds the UI to the viewport
	if (UUserWidget* InterfaceWidget = CreateWidget(GetWorld(), InterfaceWidgetClass))
	{
		InterfaceWidget->AddToViewport();
	}
	
}

// Called every frame
void AStudent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AStudent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


