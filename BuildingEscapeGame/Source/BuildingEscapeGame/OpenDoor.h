// copyright ismail 2017

#pragma once

#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPEGAME_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();
	// Called when the game starts
	virtual void BeginPlay() override;
    virtual void OpenDoor();
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

private:
    UPROPERTY(VisibleAnywhere)
    float OpenAngle = 90.0f;
	
    UPROPERTY(EditAnywhere)
    ATriggerVolume* PressurePlate;
    
    //UPROPERTY(EditAnywhere)
    AActor* ActorThatOpenTheDoor;
};
