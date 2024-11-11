// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);



	// ...
}

void UGrabber::Release()
{
}

void UGrabber::Grab()
{
	FVector start = GetComponentLocation();
	FVector end = start + GetForwardVector() * MaxGrabDistance;

	DrawDebugLine(GetWorld(), start, end, FColor::Red);

	FHitResult hit;
	FCollisionShape sphere = FCollisionShape::MakeSphere(GrabRadius);

	bool hasHit = GetWorld()->SweepSingleByChannel(hit, start, end, FQuat::Identity, ECC_GameTraceChannel2, sphere);

	if (hasHit)
	{
		UE_LOG(LogTemp, Display, TEXT("Actor hit: %s"), *hit.GetActor()->GetActorNameOrLabel());
	}
}

