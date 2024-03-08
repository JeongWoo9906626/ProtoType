#include "Mushroom.h"
#include "Mario.h"

AMushroom::AMushroom()
{
}

AMushroom::~AMushroom()
{
}

void AMushroom::BeginPlay()
{
	AActor::BeginPlay();

	{
		Renderer = CreateImageRenderer(ERenderOrder::Monster);
		Renderer->SetImage("MarioItem.png");
		Renderer->SetTransform({ { 0, 0 }, { 64 * 1.7f, 64 * 1.7f } });
	}

	{
		Renderer->CreateAnimation("MushroomMove", "OpenWorldGoomba.png", 0, 0, 0.1f, true);
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
		BottomCollision->SetPosition({ 0, 10 });
		BottomCollision->SetScale({ 30, 3 });
	}

	StateChange(EItemState::Spawn);
}

void AMushroom::Tick(float _DeltaTime)
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

		Player->SizeState = EMarioSizeState::Big;
		Player->StateChange(EPlayState::GrowUp);
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

void AMushroom::StateChange(EItemState _State)
{
	if (State != _State)
	{
		switch (_State)
		{
		case EItemState::Spawn:
			SpawnStart();
			break;
		case EItemState::Move:
			MoveStart();
			break;
		case EItemState::CollisionMove:
			CollisionMoveStart();
			break;
		default:
			break;
		}
	}

	State = _State;
}

void AMushroom::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case EItemState::Spawn:
		Spawn(_DeltaTime);
		break;
	case EItemState::Move:
		Move(_DeltaTime);
		break;
	case EItemState::CollisionMove:
		CollisionMove(_DeltaTime);
		break;
	default:
		break;
	}
}

void AMushroom::SpawnStart()
{
	DestroyValue = false;
}

void AMushroom::MoveStart()
{
	DestroyValue = false;
}

void AMushroom::CollisionMoveStart()
{
	DestroyValue = false;
}

void AMushroom::Spawn(float _DeltaTime)
{
	AddActorLocation(FVector::Up * SpawnUpSpeed * _DeltaTime);

	if (true == IsBoxCollision)
	{
		StateChange(EItemState::Move);
		return;
	}
}

void AMushroom::Move(float _DeltaTime)
{
	if (true == IsBoxCollision)
	{
		StateChange(EItemState::CollisionMove);
		return;
	}

	FVector ForwardVector = { 1.0f, 0.0f, 0.0f, 0.0f };
	GravityMove(_DeltaTime);

	FVector CheckPos = GetActorLocation();
	switch (DirState)
	{
	case EActorDir::Left:
		CheckPos.X -= 32.0f;
		break;
	case EActorDir::Right:
		CheckPos.X += 32.0f;
		break;
	default:
		break;
	}
	CheckPos.Y -= 32.0f;

	Color8Bit Color = UContentsHelper::MapColImage->GetColor(CheckPos.iX(), CheckPos.iY(), Color8Bit::MagentaA);
	if (Color == Color8Bit(255, 0, 255, 0))
	{
		ChangeDir(DirState);
	}

	if (EActorDir::Left == DirState)
	{
		DirUnitVector = -1.0f;
	}
	else
	{
		DirUnitVector = 1.0f;
	}

	CheckWindowPosition();

	if (true == DestroyValue)
	{
		Destroy();
	}

	AddActorLocation(ForwardVector * DirUnitVector * MoveSpeed * _DeltaTime);
}

void AMushroom::CollisionMove(float _DeltaTime)
{
	if (false == IsBoxCollision)
	{
		StateChange(EItemState::Move);
		return;
	}

	FVector ForwardVector = { 1.0f, 0.0f, 0.0f, 0.0f };

	FVector CheckPos = GetActorLocation();
	switch (DirState)
	{
	case EActorDir::Left:
		CheckPos.X -= 32.0f;
		break;
	case EActorDir::Right:
		CheckPos.X += 32.0f;
		break;
	default:
		break;
	}
	CheckPos.Y -= 32.0f;

	Color8Bit Color = UContentsHelper::MapColImage->GetColor(CheckPos.iX(), CheckPos.iY(), Color8Bit::MagentaA);
	if (Color == Color8Bit(255, 0, 255, 0))
	{
		ChangeDir(DirState);
	}

	if (EActorDir::Left == DirState)
	{
		DirUnitVector = -1.0f;
	}
	else
	{
		DirUnitVector = 1.0f;
	}

	CheckWindowPosition();

	if (true == DestroyValue)
	{
		Destroy();
	}

	AddActorLocation(ForwardVector * DirUnitVector * MoveSpeed * _DeltaTime);
}

void AMushroom::GravityMove(float _DeltaTime)
{
	FVector GravityVector = { 0.0f, 1.0f, 0.0f, 0.0f };
	Color8Bit Color = UContentsHelper::MapColImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::MagentaA);
	if (Color == Color8Bit(255, 0, 255, 0))
	{
		GravityVector = FVector::Zero;
	}
	else
	{
		AddActorLocation(GravityVector * GravitySpeed * _DeltaTime);
	}
}

void AMushroom::ChangeDir(EActorDir _State)
{
	if (EActorDir::Left == DirState)
	{
		DirState = EActorDir::Right;
	}
	else
	{
		DirState = EActorDir::Left;
	}
}

void AMushroom::CheckWindowPosition()
{
	FVector CurPosition = GetActorLocation();
	FVector CameraPos = GetWorld()->GetCameraPos();
	if (CameraPos.X >= CurPosition.X)
	{
		DestroyValue = true;
	}
}
