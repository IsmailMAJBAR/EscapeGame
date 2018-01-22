// copyright ismail 2017

#pragma once

#include "Components/ActorComponent.h"
#include "Gameframework/Actor.h"
#include "PosReport.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPEGAME_API UPosReport : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPosReport();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

		
	
};
