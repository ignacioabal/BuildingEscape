// Copyright Ignacio Abal 2020

#include "Components/InputComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
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

	FindPhysicsHandle();
	FindInputComponent();
}

void UGrabber::FindInputComponent() {
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	
	if (IsValid(InputComponent)) {
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);

	}
}

void UGrabber::FindPhysicsHandle() {
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (!IsValid(PhysicsHandle)) {
		UE_LOG(LogTemp, Error, TEXT("Physics Handler not found in: %s . Please, check if that actor has the component attached to it."), *GetOwner()->GetName());
	}
}


void UGrabber::Grab() {
	UE_LOG(LogTemp, Warning, TEXT("Grabber Pressed."));

	GetFirstPhysicsBodyInReach();

}
 
void UGrabber::Release() {
	UE_LOG(LogTemp, Warning, TEXT("Grabber Released."));

}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const {

	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

		GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
			OUT PlayerViewPointLocation,
			OUT PlayerViewPointRotation
		);

		
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


		FHitResult Hit;

		FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

		GetWorld()->LineTraceSingleByObjectType(
			OUT Hit,
			PlayerViewPointLocation,
			LineTraceEnd,
			FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
			TraceParams
		);

		AActor *ActorHit = Hit.GetActor();

		if (IsValid(ActorHit)) {
			UE_LOG(LogTemp, Warning, TEXT("Object Grabbed: %s"), *ActorHit->GetName());
		}

		return Hit;
}