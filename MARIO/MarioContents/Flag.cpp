#include "Flag.h"
#include "Mario.h"

AFlag::AFlag()
{
}

AFlag::~AFlag()
{
}

void AFlag::BeginPlay()
{
	FlagCollision = CreateCollision(ECollisionOrder::Flag);
	FlagCollision->SetColType(ECollisionType::Rect);
	FlagCollision->SetPosition({ 0, -230 });
	FlagCollision->SetScale({ 10, 600 });
}

void AFlag::Tick(float _DeltaTime)
{
	std::vector<UCollision*> MarioResult;
	if (true == FlagCollision->CollisionCheck(ECollisionOrder::Player, MarioResult))
	{
		AMario* Mario = (AMario*)MarioResult[0]->GetOwner();
		Mario->StateChange(EPlayState::FinishMove);
		return;
	}
}
