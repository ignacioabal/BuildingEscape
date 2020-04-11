

#include "OpenDoor.h"
#include "Components/AudioComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/TriggerVolume.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"

#define OUT

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

		FindPressurePlate();
		FindAudioComponent();
	}

}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (IsValid(PressurePlate)) {
		if (TotalMassOfActors() >= MassToOpenDoor) {
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


void UOpenDoor::FindAudioComponent() {
	if (IsValid(GetOwner())) {
		AudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();
	}

	if (IsValid(AudioComponent)) {
		UE_LOG(LogTemp, Error, TEXT("%s Missing audio component"), *GetOwner()->GetName());
	}
}

void UOpenDoor::FindPressurePlate() {
	if (!IsValid(PressurePlate)) {
		UE_LOG(LogTemp, Error, TEXT("Pressure plate not found!"));
	}
}


void UOpenDoor::OpenDoor(float DeltaTime, bool Open) {

	if (IsValid(GetOwner())) {

		if (Open == true) {

			CurrentYaw = FMath::Lerp(CurrentYaw, OpenDoorAngle, DeltaTime * DoorOpenSpeed);


			ClosedDoorSound = false;

			if (!AudioComponent) {
				UE_LOG(LogTemp, Error, TEXT("No Doorsound"));
			}
			else if (!OpenDoorSound) {
				AudioComponent->Play();
				OpenDoorSound = true;
			}

		}
		else {
			CurrentYaw = FMath::Lerp(CurrentYaw, InitialYaw, DeltaTime * DoorCloseSpeed);
			//OpenDoorSound = false;

			if (!AudioComponent) { UE_LOG(LogTemp, Error, TEXT("No Doorsound")); }
			else if (!ClosedDoorSound) {
				AudioComponent->Play();
				ClosedDoorSound = true;
			}
		}

		FRotator DoorRotation = GetOwner()->GetActorRotation();
		DoorRotation.Yaw = CurrentYaw;
		GetOwner()->SetActorRotation(DoorRotation);

	}

}

float UOpenDoor::TotalMassOfActors() const {
	float TotalMass = 0.f;

	TArray<AActor*> OverlappingActors;

	if (IsValid(PressurePlate)) {
		PressurePlate->GetOverlappingActors(OUT OverlappingActors);
	}

	for (AActor* Actor : OverlappingActors) {
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();

	}


	return TotalMass;
}
