// copyright ismail 2017

#include "BuildingEscapeGame.h"
#include "PosReport.h"


// Sets default values for this component's properties
UPosReport::UPosReport()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPosReport::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPosReport::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

