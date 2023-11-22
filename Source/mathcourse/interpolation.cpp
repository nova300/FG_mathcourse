// Fill out your copyright notice in the Description page of Project Settings.


#include "interpolation.h"

// Sets default values
Ainterpolation::Ainterpolation()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void Ainterpolation::BeginPlay()
{
	Super::BeginPlay();

	targetPos = GetActorLocation();
	
}

// Called every frame
void Ainterpolation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetActorLocation(lerpVector(GetActorLocation(), targetPos, 0.25f));

}

FVector Ainterpolation::lerpVector(FVector a, FVector b, float t)
{

	if (t > 1.0f) t = 1.0f;
	if (t < 0.0f) t = 0.0f;

	FVector out = FVector::ZeroVector;

	out.X = a.X + t * (b.X - a.X);
	out.Y = a.Y + t * (b.Y - a.Y);
	out.Z = a.Z + t * (b.Z - a.Z);

	return out;
}

void Ainterpolation::SetTargetPosition(FVector pos)
{
	targetPos = pos;
}

