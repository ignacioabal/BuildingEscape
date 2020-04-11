// Copyright Ignacio Abal 2020


#include "LightTrigger.h"
#include "Components/LightComponent.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

// Sets default values for this component's properties
ULightTrigger::ULightTrigger()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULightTrigger::BeginPlay()
{
	Super::BeginPlay();

	CheckTrigger();
	GetPlayer();



}


// Called every frame
void ULightTrigger::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (IsValid(Trigger)) {
		TurnOnLight(DeltaTime);
	}
}


void ULightTrigger::CheckTrigger() {
	if (!IsValid(Trigger)) {
		UE_LOG(LogTemp, Error, TEXT("Trigger not set for light %s"), *GetOwner()->GetName());
	}
}

void ULightTrigger::TurnOnLight(float DeltaTime) {
	if (Trigger->IsOverlappingActor(Player)) {
		GetOwner()->FindComponentByClass<ULightComponent>()->SetIntensity(LightIntensity);
	}
}

void ULightTrigger::GetPlayer() {
	Player = GetWorld()->GetFirstPlayerController()->GetPawn();
}