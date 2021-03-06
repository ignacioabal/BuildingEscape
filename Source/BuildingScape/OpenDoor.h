

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"



UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BUILDINGSCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void OpenDoor(float DeltaTime, bool openORclose);
	void FindAudioComponent();
	void FindPressurePlate();

	float TotalMassOfActors() const;



private:

	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate = nullptr;

	UPROPERTY()
		UAudioComponent* AudioComponent = nullptr;

	float InitialYaw;
	float CurrentYaw;
	bool OpenDoorSound = false;
	bool ClosedDoorSound = true;

	float DoorLastOpened = 0.f;

	UPROPERTY(EditAnywhere)
		float DoorOpenSpeed = 1.f;

	UPROPERTY(EditAnywhere)
		float DoorCloseSpeed = .5f;

	UPROPERTY(EditAnywhere)
		float DoorCloseDelay = 2.f;

	UPROPERTY(EditAnywhere)
		float OpenDoorAngle = 90.f;


	UPROPERTY(EditAnywhere)
		float MassToOpenDoor = 0.f;


};
