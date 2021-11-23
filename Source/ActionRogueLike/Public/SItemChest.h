// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "SGameplayInterface.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "SItemChest.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ASItemChest : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASItemChest();

protected:

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* LidMesh;

	UPROPERTY(EditAnywhere)
	float ChestOpenTargetPitch;

	bool bIsOpen;

	FTimeline CurveTimeline;

	UPROPERTY(EditAnywhere, Category = "Open Timeline")
	UCurveFloat* CurveFloat;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void TimelineProgress(float Value);

	UFUNCTION()
	void TimelineFinished();

	UFUNCTION(BlueprintNativeEvent)
	void OnChestOpened();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Interact_Implementation(APawn* InstigatorPawn);
};
