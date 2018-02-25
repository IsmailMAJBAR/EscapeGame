 // copyright ismail 2017

#pragma once

#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPEGAME_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

private:
    //  how far a head of the player we can reach
    float Reach =100.0f;
    UPhysicsHandleComponent* PhysicsHandle = nullptr ;
    UInputComponent* InputComponent = nullptr ;
    //Ray cast and grab what in reach
    void Grab();
    // caled when grab key is released
    void Release();
    
    // find attached componnent
    void FindPhysicsHandelComponant();
    // set Up attached input component
    void SetUpMethodComponent();
    // return hit for first physics body in reach
    const FHitResult GetFirstPhysicsBodyInReach();
};
