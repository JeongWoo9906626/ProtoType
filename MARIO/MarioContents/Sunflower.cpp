#include "Sunflower.h"
#include "Mario.h"

ASunflower::ASunflower()
{
}

ASunflower::~ASunflower()
{
}

void ASunflower::BeginPlay()
{
	AActor::BeginPlay();

	{
		Renderer = CreateImageRenderer(ERenderOrder::Monster);
		Renderer->SetImage("MarioItem.png");
		Renderer->SetTransform({ { 0, 0 }, { 64 * 1.7f, 64 * 1.7f } });
	}

	{
		Renderer->CreateAnimation("Sunflower", "MarioItem.png", 2, 2, 0.1f, true);
	}

	{
		BodyCollision = CreateCollision(ECollisionOrder::Goomba);
		BodyCollision->SetColType(ECollisionType::Rect);
		BodyCollision->SetPosition({ 0, -30 });
		BodyCollision->SetScale({ 55, 55 });
	}

	{
		BottomCollision = CreateCollision(ECollisionOrder::Goomba);
		BottomCollision->SetColType(ECollisionType::Rect);
		BottomCollision->SetPosition({ 0, 0 });
		BottomCollision->SetScale({ 30, 3 });
	}

	Renderer->ChangeAnimation("Sunflower");
	StateChange(EItemState::Spawn);
}

void ASunflower::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	std::vector<UCollision*> MarioResult;
	if (true == BodyCollision->CollisionCheck(ECollisionOrder::Player, MarioResult))
	{
		UCollision* MarioPosition = MarioResult[0];
		AMario* Player = (AMario*)MarioPosition->GetOwner();

		Renderer->ActiveOff();
		BodyCollision->ActiveOff();
		Destroy();

		UContentsHelper::Score += 1000;

		Player->SizeState = EMarioSizeState::Red;
		Player->StateChange(EPlayState::ChangeRed);
		return;
	}

	std::vector<UCollision*> BoxTopResult;
	if (true == BottomCollision->CollisionCheck(ECollisionOrder::BoxTop, BoxTopResult))
	{
		for (UCollision* BoxPosition : BoxTopResult)
		{
			IsBoxCollision = true;
		}
	}
	else
	{
		IsBoxCollision = false;
	}

	StateUpdate(_DeltaTime);
}

void ASunflower::StateChange(EItemState _State)
{
	if (State != _State)
	{
		switch (_State)
		{
		case EItemState::Spawn:
			SpawnStart();
			break;
		default:
			break;
		}
	}

	State = _State;
}

void ASunflower::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case EItemState::Spawn:
		Spawn(_DeltaTime);
		break;
	default:
		break;
	}
}

void ASunflower::SpawnStart()
{
	DestroyValue = false;
}

void ASunflower::Spawn(float _DeltaTime)
{
	if (false == IsBoxCollision)
	{
		AddActorLocation(FVector::Up * SpawnUpSpeed * _DeltaTime);
	}
}
