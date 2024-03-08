#include "ItemBox.h"
#include "Mario.h"
#include "Mushroom.h"
#include "Sunflower.h"

AItemBox::AItemBox()
{
}

AItemBox::~AItemBox()
{
}

void AItemBox::BeginPlay()
{
	AActor::BeginPlay();

	Renderer = CreateImageRenderer(ERenderOrder::Brick);
	Renderer->SetImage("OpenWorldBox.png");
	Renderer->SetTransform({ { 0, 0 }, { 256, 256 } });

	Renderer->CreateAnimation("BrickIdle", "OpenWorldBox.png", 0, 3, 0.2f, true);
	Renderer->CreateAnimation("BrickHit", "OpenWorldBox.png", 4, 4, 0.1f, true);
	Renderer->CreateAnimation("BrickBlock", "OpenWorldBox.png", 5, 5, 0.1f, true);

	TopCollision = CreateCollision(ECollisionOrder::BoxTop);
	TopCollision->SetColType(ECollisionType::Rect);
	TopCollision->SetPosition({ 0, -60 });
	TopCollision->SetScale({ 64, 10 });

	BottomCollision = CreateCollision(ECollisionOrder::Box);
	BottomCollision->SetColType(ECollisionType::Rect);
	BottomCollision->SetPosition({ 0, -5 });
	BottomCollision->SetScale({ 50, 10 });

	LeftCollision = CreateCollision(ECollisionOrder::Box);
	LeftCollision->SetColType(ECollisionType::Rect);
	LeftCollision->SetPosition({ -28, -28 });
	LeftCollision->SetScale({ 10, 55 });

	RightCollision = CreateCollision(ECollisionOrder::Box);
	RightCollision->SetColType(ECollisionType::Rect);
	RightCollision->SetPosition({ +28, -28 });
	RightCollision->SetScale({ 10, 55 });

	StateChange(EBoxState::Idle);
}

void AItemBox::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	std::vector<UCollision*> BottomResult;
	if (true == BottomCollision->CollisionCheck(ECollisionOrder::PlayerHead, BottomResult))
	{
		UCollision* MarioPosition = BottomResult[0];
		AMario* Player = (AMario*)MarioPosition->GetOwner();

		if (EBoxState::Idle == State)
		{
			MarioSizeState = Player->SizeState;
			Player->JumpVector = FVector::Zero;
			StateChange(EBoxState::Hit);
			return;
		}
		if (EBoxState::Block == State)
		{
			Player->JumpVector = FVector::Zero;
			return;
		}
	}

	std::vector<UCollision*> LeftResult;
	if (true == LeftCollision->CollisionCheck(ECollisionOrder::Player, LeftResult))
	{
		UCollision* MarioPosition = LeftResult[0];
		AMario* Player = (AMario*)MarioPosition->GetOwner();

		Player->RunVector.X = 0.0f;
		return;
	}

	std::vector<UCollision*> RightResult;
	if (true == RightCollision->CollisionCheck(ECollisionOrder::Player, RightResult))
	{
		UCollision* MarioPosition = RightResult[0];
		AMario* Player = (AMario*)MarioPosition->GetOwner();

		Player->RunVector.X = 0.0f;
		return;
	}

	StateUpdate(_DeltaTime);
}

void AItemBox::StateChange(EBoxState _State)
{
	if (State != _State)
	{
		switch (_State)
		{
		case EBoxState::Idle:
			IdleStart();
			break;
		case EBoxState::Hit:
			HitStart();
			break;
		case EBoxState::Block:
			BlockStart();
			break;
		default:
			break;
		}
	}

	State = _State;
}

void AItemBox::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case EBoxState::Idle:
		Idle(_DeltaTime);
		break;
	case EBoxState::Hit:
		Hit(_DeltaTime);
		break;
	case EBoxState::Block:
		Block(_DeltaTime);
		break;
	default:
		break;
	}
}

void AItemBox::IdleStart()
{
	Renderer->ChangeAnimation("BrickIdle");
}

void AItemBox::HitStart()
{	
	FirstPos = GetActorLocation();
	Renderer->ChangeAnimation("BrickHit");
}

void AItemBox::BlockStart()
{
	Renderer->ChangeAnimation("BrickBlock");
}

void AItemBox::Idle(float _DeltaTime)
{
}

void AItemBox::Hit(float _DeltaTime)
{
	if (abs(MoveUpPos.Y) >= MaxHitUpSize)
	{
		if (abs(MoveDownPos.Y) >= MaxHitUpSize)
		{
			switch (MarioSizeState)
			{
			case EMarioSizeState::Small:
			{
				AMushroom* Mushroom = GetWorld()->SpawnActor<AMushroom>(ERenderOrder::Item);
				Mushroom->SetName("Mushroom");
				FVector BoxLocation = GetActorLocation();
				Mushroom->SetActorLocation({ BoxLocation.X, BoxLocation.Y - 15.0f });
				break;
			}
			case EMarioSizeState::Big:
			{
				ASunflower* Sunflower = GetWorld()->SpawnActor<ASunflower>(ERenderOrder::Item);
				Sunflower->SetName("Sunflower");
				FVector BoxLocation = GetActorLocation();
				Sunflower->SetActorLocation({ BoxLocation.X, BoxLocation.Y - 15.0f });
				break;
			}
			case EMarioSizeState::Red:
			{
				ASunflower* Sunflower = GetWorld()->SpawnActor<ASunflower>(ERenderOrder::Item);
				Sunflower->SetName("Sunflower");
				FVector BoxLocation = GetActorLocation();
				Sunflower->SetActorLocation({ BoxLocation.X, BoxLocation.Y - 15.0f });
				break;
			}
			case EMarioSizeState::Star:
				break;
			default:
				break;
			}

			SetActorLocation(FirstPos);
			StateChange(EBoxState::Block);
			return;
		}
		else
		{
			MoveDownPos += FVector::Down * HitUpSpeed * _DeltaTime;
			AddActorLocation(FVector::Down * HitUpSpeed * _DeltaTime);
		}
	}
	else
	{
		MoveUpPos += FVector::Up * HitUpSpeed * _DeltaTime;
		AddActorLocation(FVector::Up * HitUpSpeed * _DeltaTime);
	}
}

void AItemBox::Block(float _DeltaTime)
{
}

