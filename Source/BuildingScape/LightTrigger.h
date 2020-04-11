// Copyright Ignacio Abal 2020

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "Components/ActorComponent.h"
#include "LightTrigger.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BUILDINGSCAPE_API ULightTrigger : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	ULightTrigger();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	void CheckTrigger();
	void TurnOnLight(float DeltaTime);
	void GetPlayer();

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	UPROPERTY(EditAnywhere)
		ATriggerVolume* Trigger = nullptr;

	UPROPERTY(EditAnywhere)
		float LightIntensity = 0.f;

	AActor* Player = nullptr;

};
