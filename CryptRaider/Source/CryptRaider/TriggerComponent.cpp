// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AActor* actor = GetActor();
	if (actor != nullptr)
	{
		UPrimitiveComponent* component = Cast<UPrimitiveComponent>(actor->GetRootComponent());
		if (component != NULL)
		{
			component->SetSimulatePhysics(false);
		}

		actor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
		Mover->SetShouldMove(true);
	}
	else
	{
		Mover->SetShouldMove(false);
	}

}

void UTriggerComponent::SetMover(UMover* mover)
{

	Mover = mover;

}

AActor* UTriggerComponent::GetActor() const
{
	TArray<AActor*> actors;

	GetOverlappingActors(actors);

	for (AActor* actor : actors)
	{
		if (actor->ActorHasTag(ActorTag) && !actor->ActorHasTag("Grabbed"))
		{
			return actor;
		}
	}

	return nullptr;

}

