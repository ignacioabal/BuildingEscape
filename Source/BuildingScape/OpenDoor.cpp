// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(GetOwner())) {
		InitialYaw = GetOwner()->GetActorRotation().Yaw;
		CurrentYaw = InitialYaw;
		TargetYaw = InitialYaw + 90.f;
	}

}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (IsValid(GetOwner())) {
		UE_LOG(LogTemp, Warning, TEXT("%s"), *GetOwner()->GetActorRotation().ToString());
		UE_LOG(LogTemp, Warning, TEXT("Yaw is: %f"), GetOwner()->GetActorRotation().Yaw);

		CurrentYaw = FMath::Lerp(CurrentYaw, TargetYaw, 0.02f);
		FRotator DoorRotation = GetOwner()->GetActorRotation();
		DoorRotation.Yaw = CurrentYaw;
		GetOwner()->SetActorRotation(DoorRotation);
	}


	//float CurrentYaw = GetOwner()->GetActorRotation().Yaw;
	//FRotator OpenDoor(0.f, TargetYaw, 0.f);
	//OpenDoor.Yaw = FMath::FInterpTo(CurrentYaw, 90.f, DeltaTime, 45);

}

