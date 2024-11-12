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

	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();


	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	

	if (PhysicsHandle == NULL)
	{
		return;
	}

	FVector targetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;

	PhysicsHandle->SetTargetLocationAndRotation(targetLocation, GetComponentRotation());

	// ...
}

void UGrabber::Release()
{
	if (PhysicsHandle == NULL)
	{
		return;
	}

	if (PhysicsHandle->GetGrabbedComponent() != nullptr)
	{
		AActor* grabbed = PhysicsHandle->GetGrabbedComponent()->GetOwner();
		grabbed->Tags.Remove("Grabbed");
		PhysicsHandle->ReleaseComponent();
	}

}

void UGrabber::Grab()
{

	if (PhysicsHandle == NULL)
	{
		return;
	}

	FHitResult hit;
	bool hasHit = GetGrabbableInReach(hit);

	if (hasHit)
	{
		hit.GetActor()->Tags.Add("Grabbed");
		PhysicsHandle->GrabComponentAtLocationWithRotation(hit.GetComponent(), NAME_None, hit.ImpactPoint, GetComponentRotation());
	}
}

bool UGrabber::GetGrabbableInReach(FHitResult& OutHitResult) const
{
	FVector start = GetComponentLocation();
	FVector end = start + GetForwardVector() * MaxGrabDistance;

	FCollisionShape sphere = FCollisionShape::MakeSphere(GrabRadius);

	bool hasHit = GetWorld()->SweepSingleByChannel(OutHitResult, start, end, FQuat::Identity, ECC_GameTraceChannel2, sphere);

	return hasHit;
}

