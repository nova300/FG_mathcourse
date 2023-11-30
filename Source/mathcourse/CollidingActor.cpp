#include "CollidingActor.h"

TArray<ACollidingActor*> collisionActors;

ACollidingActor::ACollidingActor()
{
	PrimaryActorTick.bCanEverTick = true;
	sphereRadius = 50.0f;
	skip = false;
	velocity = FVector(150.0f, 200.0f, 100.0f);
}

void ACollidingActor::BeginPlay()
{
	Super::BeginPlay();
	collisionActors.Add(this);
}

void ACollidingActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (collisionActors.Contains(this)) collisionActors.Remove(this);
	Super::EndPlay(EndPlayReason);
}

void ACollidingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	skip = false;
	DrawDebugSphere(GetWorld(), GetActorLocation(), this->sphereRadius, 10, FColor::Green);

	for (int i = 0; i < collisionActors.Num(); i++)
	{
		if (collisionActors[i] == this) continue;
		if (this->skip) continue;

		ACollidingActor* near = this;
		ACollidingActor* far = collisionActors[i];

		float distP = FVector::Dist(far->GetActorLocation(), near->GetActorLocation()); //positional distance
		float distL = near->sphereRadius + far->sphereRadius;	//total collider distance

		if (distL > distP)
		{
			float disO = distL - distP;	// get collision depth/offset
			FVector dir = far->GetActorLocation() - near->GetActorLocation();	//get collision direction and normalize
			dir.Normalize();
			dir = dir * disO;		//scale it by offset, deeper collisions gets more speed
			FVector vel = -velocity;
			vel = vel / 2;
			vel = vel + (far->velocity / 2); //add half of colliding objects velocity
			velocity = vel - dir;
			collisionActors[i]->skip = true;
			break;
		}
	}


	FVector currentPos = this->GetActorLocation();


	// wall checks
	float limit = 2000.0f;

	if (currentPos.X < -limit)
	{
		velocity = FVector(-velocity.X, velocity.Y, velocity.Z);
		currentPos.X = -limit;
	}
	else if (currentPos.X > limit)
	{
		velocity = FVector(-velocity.X, velocity.Y, velocity.Z);
		currentPos.X = limit;
	}
	else if (currentPos.Y < -limit)
	{
		velocity = FVector(velocity.X, -velocity.Y, velocity.Z);
		currentPos.Y = -limit;
	}
	else if (currentPos.Y > limit)
	{
		velocity = FVector(velocity.X, -velocity.Y, velocity.Z);
		currentPos.Y = limit;
	}
	else if (currentPos.Z < -limit)
	{
		velocity = FVector(velocity.X, velocity.Y, -velocity.Z);
		currentPos.Z = -limit;
	}
	else if (currentPos.Z > limit)
	{
		velocity = FVector(velocity.X, velocity.Y, -velocity.Z);
		currentPos.Z = limit;
	}

	this->SetActorLocation(currentPos + (velocity * DeltaTime));

}

