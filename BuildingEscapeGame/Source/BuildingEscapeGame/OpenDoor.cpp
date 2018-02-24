// copyright ismail 2017

#include "BuildingEscapeGame.h"
#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
    Owner = GetOwner();
  ActorThatOpenTheDoor = GetWorld()->GetFirstPlayerController()->GetPawn();
    
    
}

void UOpenDoor::OpenDoor(){
    Owner->SetActorRotation(FRotator(0.0f, OpenAngle, 0.0f));
}

void UOpenDoor::CloseDoor(){
    Owner->SetActorRotation(FRotator(0.0f,0.0f, 0.0f));
}


// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
    
    //pool the trigger volume
    if (PressurePlate != nullptr && ActorThatOpenTheDoor != nullptr && (PressurePlate -> IsOverlappingActor(ActorThatOpenTheDoor))){
        OpenDoor();
        LastDoorOpenTime = GetWorld()->GetTimeSeconds();
    }
    // check if its time to close the door
    
    if (GetWorld()->GetTimeSeconds()-LastDoorOpenTime > DoorCloseDelay) {
        CloseDoor();
    }
    
}
