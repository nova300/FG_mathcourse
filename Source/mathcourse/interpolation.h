// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "interpolation.generated.h"

UCLASS()
class MATHCOURSE_API Ainterpolation : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	Ainterpolation();

	void SetTargetPosition(FVector pos);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	FVector lerpVector(FVector a, FVector b, float t);

	FVector targetPos;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
