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
    // ..
    UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for dutty ")) ;
    FindPhysicsHandelComponant();
    SetUpMethodComponent();
}

// look for attached physics Handle
void UGrabber::FindPhysicsHandelComponant(){
    PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
    if(PhysicsHandle){
        // physics handle is  found nothing to do
    }else{
        UE_LOG(LogTemp, Error, TEXT("%s physicsHandle not detected  "), *GetOwner()->GetName()) ;
    }
}
void UGrabber::SetUpMethodComponent(){
    // look for attached inpuy components appear in run time
    InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
    if(InputComponent){
        UE_LOG(LogTemp, Warning, TEXT("InputComponent found ")) ;
        // bind the input
        InputComponent->BindAction("Grab",IE_Pressed,this,&UGrabber::Grab);
        InputComponent->BindAction("Grab",IE_Released,this,&UGrabber::Release);
    }else{
        
        UE_LOG(LogTemp, Error, TEXT("InputComponent missing : %s"), *GetOwner()->GetName()) ;
        
    }
}


void UGrabber::Grab(){
    UE_LOG(LogTemp, Warning, TEXT("Grabbed")) ;
    // line trace and see if we reach any actor with phisics body collision channel
    auto HitResult =  GetFirstPhysicsBodyInReach();
    auto ComponentToGrab = HitResult.GetComponent();
    auto ActorHit =  HitResult.GetActor();
    
    // if we hit something then attach a physics handle
    if(ActorHit){
        PhysicsHandle->GrabComponent(
                    ComponentToGrab,
                    NAME_None,
                    ComponentToGrab->GetOwner()->GetActorLocation(),
                    true) ;
    }
    // attach physics handle

}
void UGrabber::Release(){
    UE_LOG(LogTemp, Warning, TEXT("Released grab ")) ;
    PhysicsHandle->ReleaseComponent();
    // release physics handel
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
    FVector LineTraceEnd = PlayerViewPointLocation + (PlayerViewPointRotation.Vector() * Reach) ; //FVector(0.0f,0.0f,80.0f);
    
   // if the physics Handle is attached
    if(PhysicsHandle->GrabbedComponent){
        PhysicsHandle->SetTargetLocation(LineTraceEnd);
    }
    
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach(){
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
    
    return Hit;
}
