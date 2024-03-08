#include "Gate.h"
#include "Mario.h"
#include "FinalLevel.h"

AGate::AGate()
{
}

AGate::~AGate()
{
}

void AGate::BeginPlay()
{
	AActor::BeginPlay();

	BodyCollision = CreateCollision(ECollisionOrder::HiddenCoin);
	BodyCollision->SetColType(ECollisionType::Rect);
	BodyCollision->SetPosition({ 0, -30 });
	BodyCollision->SetScale({ 65, 70 });
}

void AGate::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	std::vector<UCollision*> Result;
	if (true == BodyCollision->CollisionCheck(ECollisionOrder::Player, Result))
	{
		UCollision* MarioPosition = Result[0];
		AMario* Player = (AMario*)MarioPosition->GetOwner();

		FTransform MarioCollision = MarioPosition->GetActorBaseTransform();
		FTransform MyTransform = BodyCollision->GetActorBaseTransform();

		Player->Renderer->ActiveOff();
		Player->IsStageEnd = true;

		if (CurChangeLevelTime >= ChangeLevelTime)
		{
			UContentsHelper::Time = 1400;
			GEngine->CreateLevel<UFinalLevel>("Final");
			GEngine->ChangeLevel("Final");
			return;
		}
		CurChangeLevelTime += _DeltaTime;
	}
}