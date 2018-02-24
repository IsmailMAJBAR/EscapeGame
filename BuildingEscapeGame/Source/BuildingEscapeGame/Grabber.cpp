// copyright ismail 2017

#include "BuildingEscapeGame.h"
#include "Grabber.h"
#include "DrawDebugHelpers.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
    UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for dutty ")) ;
	
    
}


// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
    // Get player view point this tick
    FVector PlayerViewPointLocation;
    FRotator PlayerViewPointRotation;
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation,OUT PlayerViewPointRotation);
  
    /* visualize the location and the rotation in the log
    UE_LOG(LogTemp, Warning, TEXT("Location is %s   Position is %s")
           ,*PlayerViewPointLocation.ToString(),
           *PlayerViewPointRotation.ToString());
    */
    FVector LineTraceEnd = PlayerViewPointLocation + (PlayerViewPointRotation.Vector() * Reach) ; //FVector(0.0f,0.0f,80.0f);
    
    // draw a red trace in the world to visualize
    DrawDebugLine(GetWorld(),PlayerViewPointLocation,LineTraceEnd,FColor(200,0,0),false,0.0f,0.0f,5.0f);
    
    // setUp queryparamaters
    FCollisionQueryParams TraceParameters(FName(TEXT("")),false,GetOwner());
    
    // Ray-cast out to reach distance
    FHitResult Hit;
    GetWorld()->LineTraceSingleByObjectType(OUT Hit,PlayerViewPointLocation,LineTraceEnd,
                    FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
                                            TraceParameters);
    
    // See what se hit
    AActor * ActorHit =  Hit.GetActor();
    if(ActorHit)
        UE_LOG(LogTemp, Warning, TEXT("LineTrace hit %s"),*ActorHit->GetName()) ;


}

