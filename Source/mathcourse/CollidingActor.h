#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CollidingActor.generated.h"

UCLASS()
class MATHCOURSE_API ACollidingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ACollidingActor();

	UPROPERTY(EditAnywhere)
	float sphereRadius;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	FVector velocity;
	bool skip;

};
