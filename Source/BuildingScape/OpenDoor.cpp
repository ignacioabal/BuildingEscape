

#include "OpenDoor.h"
#include "Engine/TriggerVolume.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"

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
		OpenDoorAngle += InitialYaw;

		if (IsValid(GetWorld()->GetFirstPlayerController())) {
			UOpenDoor::ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
		}
		if (!IsValid(PressurePlate)) {
			UE_LOG(LogTemp, Error, TEXT("%s has the OpenDoor component, but no Pressure Plate set."), *GetOwner()->GetName());
		}
	}

}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (IsValid(PressurePlate)) {
		if (TotalMassOfActors()> 50.f) {
			OpenDoor(DeltaTime, true);
			DoorLastOpened = GetWorld()->GetTimeSeconds();	
		}
		else {
			if (GetWorld()->GetTimeSeconds() >= DoorLastOpened + DoorCloseDelay) {
				OpenDoor(DeltaTime, false);
			}
		}
	}



}

void UOpenDoor::OpenDoor(float DeltaTime, bool Open) {

	if (IsValid(GetOwner())) {

		//UE_LOG(LogTemp, Warning, TEXT("%s"), *GetOwner()->GetActorRotation().ToString());
		//UE_LOG(LogTemp, Warning, TEXT("Yaw is: %f"), GetOwner()->GetActorRotation().Yaw);

		if (Open == true) {

			CurrentYaw = FMath::Lerp(CurrentYaw, OpenDoorAngle, DeltaTime * DoorOpenSpeed);
		}
		else {
			CurrentYaw = FMath::Lerp(CurrentYaw, InitialYaw, DeltaTime * DoorCloseSpeed);

		}

		FRotator DoorRotation = GetOwner()->GetActorRotation();
		DoorRotation.Yaw = CurrentYaw;
		GetOwner()->SetActorRotation(DoorRotation);

	}

}

float UOpenDoor::TotalMassOfActors() const {
	float TotalMass = 0.f;

	TArray<AActor*> OverlappingActors;

	PressurePlate->GetOverlappingActors(OverlappingActors);



	return TotalMass;
}
