#include "intersection.h"

TArray<Uintersection*> intersectionObjects;

Uintersection::Uintersection()
{
	PrimaryComponentTick.bCanEverTick = true;
	intersecting = false;
	objectType = ObjectType::COL_SPHERE;
	sphereRadius = 50.0f;
	AABBSize = FVector(10.0f, 10.0f, 10.0f);
}

void Uintersection::BeginPlay()
{
	Super::BeginPlay();
	intersectionObjects.Add(this);
}

void Uintersection::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (intersectionObjects.Contains(this)) intersectionObjects.Remove(this);
	Super::EndPlay(EndPlayReason);
}

bool SphereTest(Uintersection* near, Uintersection* far)
{
	float distP = FVector::DistSquared(far->GetOwner()->GetActorLocation(), near->GetOwner()->GetActorLocation());
	float distL = FMath::Square(near->sphereRadius + far->sphereRadius);

	if (distL > distP)
	{
		return true;
	}
	return false;
}

bool AABBTest(Uintersection* near, Uintersection* far)
{
	FVector nearPosA = near->GetOwner()->GetActorLocation();
	FVector nearPosB = nearPosA + near->AABBSize;
	FVector farPosA = far->GetOwner()->GetActorLocation();
	FVector farPosB = farPosA + far->AABBSize;

	if (nearPosA.X > farPosB.X) return true;
	if (farPosA.X > nearPosB.X) return true;
	if (nearPosA.Y > farPosB.Y) return true;
	if (farPosA.Y > nearPosB.Y) return true;
	if (nearPosA.Z > farPosB.Z) return true;
	if (farPosA.Z > nearPosB.Z) return true;

	return false;
}

bool MixedTest(Uintersection* near, Uintersection* far)
{
	FVector nearPos = near->GetOwner()->GetActorLocation();
	FVector farPosA = far->GetOwner()->GetActorLocation();
	FVector farPosB = farPosA + far->AABBSize;

	FVector closePoint = FVector
	(
		FMath::Clamp(nearPos.X, farPosA.X, farPosB.X),
		FMath::Clamp(nearPos.Y, farPosA.Y, farPosB.Y),
		FMath::Clamp(nearPos.Z, farPosA.Z, farPosB.Z)
	);

	float dist = FVector::Dist(nearPos, closePoint);

	if (dist < near->sphereRadius)
	{
		return true;
	}
	return false;
}

void Uintersection::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FColor drawCol = FColor::Green;
	if (intersecting) drawCol = FColor::Red;
	if (this->objectType == ObjectType::COL_SPHERE)
	{
		DrawDebugSphere(GetWorld(), GetOwner()->GetActorLocation(), this->sphereRadius, 10, drawCol);
	}
	else if (this->objectType == ObjectType::COL_AABB)
	{
		DrawDebugBox(GetWorld(), GetOwner()->GetActorLocation(), this->AABBSize, drawCol);
	}

	for (int i = 0; i < intersectionObjects.Num(); i++)
	{
		if (intersectionObjects[i] == this) continue;

		if (this->objectType == ObjectType::COL_SPHERE)
		{
			if (intersectionObjects[i]->objectType == ObjectType::COL_SPHERE)
			{
				if (SphereTest(this, intersectionObjects[i]))
				{
					intersecting = true;
					return;
				}
			}
			else if (intersectionObjects[i]->objectType == ObjectType::COL_AABB)
			{
				if (MixedTest(this, intersectionObjects[i]))
				{
					intersecting = true;
					return;
				}
			}
		}
		else if (this->objectType == ObjectType::COL_AABB)
		{
			if (intersectionObjects[i]->objectType == ObjectType::COL_SPHERE)
			{
				if (MixedTest(intersectionObjects[i], this))
				{
					intersecting = true;
					return;
				}
			}
			else if (intersectionObjects[i]->objectType == ObjectType::COL_AABB)
			{
				if (AABBTest(this, intersectionObjects[i]))
				{
					intersecting = true;
					return;
				}
			}
		}

	}

	intersecting = false;
}

