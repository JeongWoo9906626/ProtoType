#include "KoopaEvent.h"

AKoopaEvent::AKoopaEvent()
{
}

AKoopaEvent::~AKoopaEvent()
{
}

void AKoopaEvent::BeginPlay()
{
	AActor::BeginPlay();

	MoveCollision = CreateCollision(ECollisionOrder::Gate);
	MoveCollision->SetColType(ECollisionType::Rect);
	MoveCollision->SetTransform({ {0, -120}, {40, 320} });

	FireCollision = CreateCollision(ECollisionOrder::Gate);
	FireCollision->SetColType(ECollisionType::Rect);
	FireCollision->SetTransform({ {-2070, -180}, {40, 440} });
}

void AKoopaEvent::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	std::vector<UCollision*> MarioKoopaGateResult;
	if (true == MoveCollision->CollisionCheck(ECollisionOrder::Player, MarioKoopaGateResult))
	{
		UContentsHelper::KoopaWake = true;
		UContentsHelper::KoopaIsFire = true;
	}

	std::vector<UCollision*> MarioKoopaFireResult;
	if (true == FireCollision->CollisionCheck(ECollisionOrder::Player, MarioKoopaFireResult))
	{
		UContentsHelper::KoopaIsFire = true;
	}
}
