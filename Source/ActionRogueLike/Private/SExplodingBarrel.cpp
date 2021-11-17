// Fill out your copyright notice in the Description page of Project Settings.


#include "SExplodingBarrel.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
ASExplodingBarrel::ASExplodingBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComp");
	RootComponent = StaticMeshComp;
	
	StaticMeshComp->SetSimulatePhysics(true);

	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>("RadialForceComp");
	RadialForceComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASExplodingBarrel::BeginPlay()
{
	Super::BeginPlay();
}

void ASExplodingBarrel::CreateExplosionForce()
{
	RadialForceComp->FireImpulse();

	UGameplayStatics::SpawnEmitterAtLocation(this, ExplosionEffect, GetActorLocation(), GetActorRotation(), FVector(3));

	Destroy();
}

// Called every frame
void ASExplodingBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

