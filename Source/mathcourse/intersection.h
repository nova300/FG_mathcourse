#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "intersection.generated.h"

UENUM(BlueprintType)
enum ObjectType
{
	COL_SPHERE,
	COL_AABB
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MATHCOURSE_API Uintersection : public USceneComponent
{
	GENERATED_BODY()

public:	
	Uintersection();

	UPROPERTY(EditAnywhere)
	TEnumAsByte<ObjectType> objectType;

	UPROPERTY(EditAnywhere)
	float sphereRadius;

	UPROPERTY(EditAnywhere)
	FVector AABBSize;

	bool intersecting;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
		
};
