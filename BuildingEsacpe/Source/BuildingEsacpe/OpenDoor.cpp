// Copyright Zeno Ahn 2016.

#include "BuildingEsacpe.h"
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
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	Owner = GetOwner();
	// ...
}

void UOpenDoor::OpenDoor()
{
	Owner->SetActorRotation(FRotator(0, OpenAngle, 0));
}

void UOpenDoor::CloseDoor()
{
	Owner->SetActorRotation(FRotator(0, 0, 0));
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PressurePlate->IsOverlappingActor(ActorThatOpens))
	{
		OpenDoor();
		LastOpenDoorTime = GetWorld()->GetTimeSeconds();
	}

	float leavedTime = GetWorld()->GetTimeSeconds() - LastOpenDoorTime;
	if (leavedTime > DoorCloseDelay)
	{
		CloseDoor();
	}
}

