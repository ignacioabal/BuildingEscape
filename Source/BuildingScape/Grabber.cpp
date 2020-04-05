// Copyright Ignacio Abal 2020

#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Grabber.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for Duty!"));

}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	if (IsValid(GetWorld())) {
		GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
			OUT PlayerViewPointLocation,
			OUT PlayerViewPointRotation
		);

		/*UE_LOG(LogTemp, Warning, TEXT("Player Viewport Location: %s"), *PlayerViewPointLocation.ToString());
		UE_LOG(LogTemp, Warning, TEXT("Player Viewport Rotation: %s"), *PlayerViewPointRotation.ToCompactString());*/

		FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

		
		DrawDebugLine(
			GetWorld(),
			PlayerViewPointLocation,
			LineTraceEnd,
			FColor(0, 255, 0),
			false,
			0.f,
			0,
			5.f
		);


	}
	else {
		UE_LOG(LogTemp, Error, TEXT("GetWorld not found!"));
	}


	// ...
}

