// Fill out your copyright notice in the Description page of Project Settings.


#include "SItemChest.h"

// Sets default values
ASItemChest::ASItemChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	RootComponent = BaseMesh;

	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>("LidMesh");
	LidMesh->SetupAttachment(BaseMesh);

	ChestOpenTargetPitch = 110.0;
}

// Called when the game starts or when spawned
void ASItemChest::BeginPlay()
{
	Super::BeginPlay();
}

void ASItemChest::TimelineProgress(float Value)
{
	LidMesh->SetRelativeRotation(FRotator(CurveFloat->GetFloatValue(CurveTimeline.GetPlaybackPosition()), 0, 0));
}

void ASItemChest::TimelineFinished()
{
	if (bIsOpen)
	{
		bIsOpen = false;
	}
	else
	{
		bIsOpen = true;

		OnChestOpened();
	}
}

void ASItemChest::OnChestOpened_Implementation()
{
}

// Called every frame
void ASItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Must call tick on timeline for it to run
	if (CurveTimeline.IsPlaying())
	{
		CurveTimeline.TickTimeline(DeltaTime);	
	}
}

void ASItemChest::Interact_Implementation(APawn* InstigatorPawn)
{
	//Checks if the curve float is assigned
	if (CurveFloat)
	{
		FOnTimelineFloat TimelineProgressCallback;
		FOnTimelineEventStatic TimelineFinishedCallback;

		TimelineProgressCallback.BindUFunction(this, FName("TimelineProgress"));
		TimelineFinishedCallback.BindUFunction(this, FName("TimelineFinished"));
		
		CurveTimeline.AddInterpFloat(CurveFloat, TimelineProgressCallback);
		CurveTimeline.SetTimelineFinishedFunc(TimelineFinishedCallback);

		if (!bIsOpen)
		{
			CurveTimeline.PlayFromStart();	
		}
		else CurveTimeline.ReverseFromEnd();
	}
	
}

