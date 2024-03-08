#include "Mario.h"

#include <EnginePlatform\EngineInput.h>
#include <EngineBase\EngineDebug.h>
#include <EngineCore/EngineDebug.h>

#include "ContentsHelper.h"

AMario* AMario::MainPlayer = nullptr;

AMario::AMario()
{
}

AMario::~AMario()
{
}

void AMario::BeginPlay()
{
	AActor::BeginPlay();

	AMario::MainPlayer = this;

	{
		Renderer = CreateImageRenderer(ERenderOrder::Player);
		Renderer->SetImage("Mario_Right.png");
		Renderer->SetTransform({ { 0, 0 }, { 256, 256 } });
	}

	{
		Renderer->CreateAnimation("Idle_Small_Right", "Mario_Right.png", 0, 0, 0.1f, true);
		Renderer->CreateAnimation("Move_Small_Right", "Mario_Right.png", 1, 3, 0.1f, true);
		Renderer->CreateAnimation("MoveFast_Small_Right", "Mario_Right.png", 1, 3, 0.05f, true);
		Renderer->CreateAnimation("Reverse_Small_Right", "Mario_Right.png", 4, 4, 0.1f, true);
		Renderer->CreateAnimation("Jump_Small_Right", "Mario_Right.png", 5, 5, 0.1f, true);

		Renderer->CreateAnimation("Idle_Big_Right", "Mario_Right.png", 9, 9, 0.1f, true);
		Renderer->CreateAnimation("Move_Big_Right", "Mario_Right.png", 10, 12, 0.1f, true);
		Renderer->CreateAnimation("MoveFast_Big_Right", "Mario_Right.png", 10, 12, 0.05f, true);
		Renderer->CreateAnimation("Reverse_Big_Right", "Mario_Right.png", 13, 13, 0.1f, true);
		Renderer->CreateAnimation("Jump_Big_Right", "Mario_Right.png", 14, 14, 0.1f, true);

		Renderer->CreateAnimation("Idle_Fire_Right", "Mario_Right.png", 20, 20, 0.1f, true);
		Renderer->CreateAnimation("Move_Fire_Right", "Mario_Right.png", 21, 23, 0.1f, true);
		Renderer->CreateAnimation("MoveFast_Fire_Right", "Mario_Right.png", 21, 23, 0.05f, true);
		Renderer->CreateAnimation("Reverse_Fire_Right", "Mario_Right.png", 24, 24, 0.1f, true);
		Renderer->CreateAnimation("Jump_Fire_Right", "Mario_Right.png", 25, 25, 0.1f, true);

		Renderer->CreateAnimation("Idle_Small_Left", "Mario_Left.png", 0, 0, 0.1f, true);
		Renderer->CreateAnimation("Move_Small_Left", "Mario_Left.png", 1, 3, 0.1f, true);
		Renderer->CreateAnimation("MoveFast_Small_Left", "Mario_Left.png", 1, 3, 0.05f, true);
		Renderer->CreateAnimation("Reverse_Small_Left", "Mario_Left.png", 4, 4, 0.1f, true);
		Renderer->CreateAnimation("Jump_Small_Left", "Mario_Left.png", 5, 5, 0.1f, true);

		Renderer->CreateAnimation("Idle_Big_Left", "Mario_Left.png", 9, 9, 0.1f, true);
		Renderer->CreateAnimation("Move_Big_Left", "Mario_Left.png", 10, 12, 0.1f, true);
		Renderer->CreateAnimation("MoveFast_Big_Left", "Mario_Left.png", 10, 12, 0.05f, true);
		Renderer->CreateAnimation("Reverse_Big_Left", "Mario_Left.png", 13, 13, 0.1f, true);
		Renderer->CreateAnimation("Jump_Big_Left", "Mario_Left.png", 14, 14, 0.1f, true);

		Renderer->CreateAnimation("Idle_Fire_Left", "Mario_Left.png", 20, 20, 0.1f, true);
		Renderer->CreateAnimation("Move_Fire_Left", "Mario_Left.png", 21, 23, 0.1f, true);
		Renderer->CreateAnimation("MoveFast_Fire_Left", "Mario_Left.png", 21, 23, 0.05f, true);
		Renderer->CreateAnimation("Reverse_Fire_Left", "Mario_Left.png", 24, 24, 0.1f, true);
		Renderer->CreateAnimation("Jump_Fire_Left", "Mario_Left.png", 25, 25, 0.1f, true);

		Renderer->CreateAnimation("Die", "Mario_Left.png", 6, 6, 0.1f, true);
		Renderer->CreateAnimation("Down_Small", "Mario_Right.png", 7, 8, 0.1f, true);
		Renderer->CreateAnimation("DownReverse_Small", "Mario_Left.png", 8, 8, 0.1f, true);

		Renderer->CreateAnimation("Down_Big", "Mario_Right.png", 16, 17, 0.1f, true);
		Renderer->CreateAnimation("DownReverse_Big", "Mario_Left.png", 16, 16, 0.1f, true);

		Renderer->CreateAnimation("Down_Fire", "Mario_Right.png", 27, 28, 0.1f, true);
		Renderer->CreateAnimation("DownReverse_Fire", "Mario_Left.png", 28, 28, 0.1f, true);

		Renderer->CreateAnimation("GrowUp_Right", "Mario_Right.png", { 0, 19, 18, 19, 18 }, 0.1f, false);
		Renderer->CreateAnimation("GrowUp_Left", "Mario_Left.png", { 0, 19, 18, 19, 18 }, 0.1f, false);

		Renderer->CreateAnimation("GrowDown_Right", "Mario_Right.png", { 18, 19, 18, 19, 0 }, 0.1f, false);
		Renderer->CreateAnimation("GrowDown_Left", "Mario_Left.png", { 18, 19, 18, 19, 0 }, 0.1f, false);

		Renderer->CreateAnimation("ChangeRed_Right", "Mario_Right.png", { 33, 32, 33, 32, 33 }, 0.1f, false);
		Renderer->CreateAnimation("ChangeRed_Left", "Mario_Left.png", { 33, 32, 33, 32, 33 }, 0.1f, false);

		Renderer->CreateAnimation("FireShoot_Left", "Mario_Left.png", 31, 31, 0.1f, false);
		Renderer->CreateAnimation("FireShoot_Right", "Mario_Right.png", 31, 31, 0.1f, false);
	}

	{
		BodyCollision = CreateCollision(ECollisionOrder::Player);
		BodyCollision->SetColType(ECollisionType::Rect);
		BodyCollision->SetPosition({ 0, -35 });
		BodyCollision->SetScale({ 50, 64 });
	}

	{
		HeadCollision = CreateCollision(ECollisionOrder::PlayerHead);
		HeadCollision->SetColType(ECollisionType::Rect);
		HeadCollision->SetPosition({ 0, -62 });
		HeadCollision->SetScale({ 10, 10 });
	}

	{
		BottomCollision = CreateCollision(ECollisionOrder::PlayerBottom);
		BottomCollision->SetColType(ECollisionType::Rect);
		BottomCollision->SetPosition({ 0, -5 });
		BottomCollision->SetScale({ 10, 10 });
	}


	StateChange(EPlayState::Idle);
}

void AMario::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	FVector PlayerPos = GetActorLocation();
	UEngineDebug::DebugTextPrint("X : " + std::to_string(PlayerPos.X) + ", Y : " + std::to_string(PlayerPos.Y), 30.0f);
	UEngineDebug::DebugTextPrint("\nDeltaTime : " + std::to_string(_DeltaTime), 30.0f);

	/*
	std::vector<UCollision*> HiddenGateInResult;
	if (true == BottomCollision->CollisionCheck(ECollisionOrder::Gate, HiddenGateInResult))
	{
		AHiddenGate* HiddenGate = (AHiddenGate*)HiddenGateInResult[0]->GetOwner();
		EGateState GateState = HiddenGate->GetGateState();
		if (GateState == EGateState::In && true == UEngineInput::IsDown(VK_DOWN))
		{
			BottomCollision->ActiveOff();
			StateChange(EPlayState::HiddenStageEnter);
			return;
		}
	}

	std::vector<UCollision*> HiddenGateOutResult;
	if (true == BodyCollision->CollisionCheck(ECollisionOrder::Gate, HiddenGateOutResult))
	{
		AHiddenGate* HiddenGate = (AHiddenGate*)HiddenGateOutResult[0]->GetOwner();
		EGateState GateState = HiddenGate->GetGateState();
		if (GateState == EGateState::Out && true == UEngineInput::IsDown(VK_RIGHT))
		{
			BottomCollision->ActiveOn();
			StateChange(EPlayState::HiddenStageOut);
			return;
		}
	}

	std::vector<UCollision*> BoxTopResult;
	if (true == BottomCollision->CollisionCheck(ECollisionOrder::BoxTop, BoxTopResult))
	{
		GravityPower = FVector::Zero;
		JumpVector = FVector::Zero;

		// BottomCollision 마리오 바닥의 위치
		FVector MarioBottomCollisionPos = BottomCollision->GetActorBaseTransform().GetPosition();
		FVector MarioBottomCollisionScale = BottomCollision->GetActorBaseTransform().GetScale();

		// BoxPosition 박스콜리전의 위치
		FVector BoxCollisionPos = BoxTopResult[0]->GetActorBaseTransform().GetPosition();
		FVector BoxCollisionScale = BoxTopResult[0]->GetActorBaseTransform().GetScale();

		SetActorLocation({ MarioBottomCollisionPos.X, BoxCollisionPos.Y - 3.0f });

		IsJump = false;
		IsCollision = true;
	}
	else
	{
		IsCollision = false;
	}
	*/

	StateUpdate(_DeltaTime);
}

void AMario::StateChange(EPlayState _State)
{
	if (State != _State)
	{
		switch (_State)
		{
		case EPlayState::Idle:
			IdleStart();
			break;
		case EPlayState::Move:
			MoveStart();
			break;
		case EPlayState::Jump:
			JumpStart();
			break;
		case EPlayState::Reverse:
			ReverseStart();
			break;
		}
	}

	State = _State;
}

void AMario::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case EPlayState::Idle:
		Idle(_DeltaTime);
		break;
	case EPlayState::Move:
		Move(_DeltaTime);
		break;
	case EPlayState::Jump:
		Jump(_DeltaTime);
		break;
	case EPlayState::Reverse:
		Reverse(_DeltaTime);
		break;
	}
}

void AMario::DirCheck()
{
	if (true == UEngineInput::IsPress(VK_RIGHT) && true == UEngineInput::IsPress(VK_LEFT))
	{
		return;
	}
	if (
			true == UEngineInput::IsPress(VK_RIGHT) && true == UEngineInput::IsUp(VK_LEFT) ||
			true == UEngineInput::IsPress(VK_RIGHT) && true == UEngineInput::IsFree(VK_LEFT)
		)
	{
		Dir = EActorDir::Right;
	}
	if (
			true == UEngineInput::IsPress(VK_LEFT) && true == UEngineInput::IsUp(VK_RIGHT) ||
			true == UEngineInput::IsPress(VK_LEFT) && true == UEngineInput::IsFree(VK_RIGHT)
		)
	{
		Dir = EActorDir::Left;
	}
}

std::string AMario::GetAnimationName()
{
	std::string AnimationDir = "";
	switch (Dir)
	{
	case EActorDir::Left:
		AnimationDir = "_Left";
		break;
	case EActorDir::Right:
		AnimationDir = "_Right";
		break;
	}
	return AnimationDir;
}

void AMario::IdleStart()
{
	DirCheck();
	Renderer->ChangeAnimation("Idle_Small" + GetAnimationName());
}

void AMario::MoveStart()
{
	DirCheck();
	Renderer->ChangeAnimation("Move_Small" + GetAnimationName());
}

void AMario::JumpStart()
{
	DirCheck();
	AddActorLocation(FVector::Up * 5);
	JumpVector = FVector::Up * JumpPower;
	Renderer->ChangeAnimation("Jump_Small" + GetAnimationName());
}

void AMario::ReverseStart()
{
	DirCheck();
	std::string ReverseName = "";
	switch (Dir)
	{
	case EActorDir::Left:
		ReverseName = "_Right";
		break;
	case EActorDir::Right:
		ReverseName = "_Left";
		break;
	}

	Renderer->ChangeAnimation("Reverse_Small" + ReverseName);
}

void AMario::Idle(float _DeltaTime)
{
	MoveUpdate(_DeltaTime);

	if (true == UEngineInput::IsPress(VK_RIGHT) && true == UEngineInput::IsPress(VK_LEFT))
	{
		MoveVector = FVector::Zero;
		return;
	}

	if (true == UEngineInput::IsDown(VK_SPACE))
	{
		StateChange(EPlayState::Jump);
		return;
	}

	if (true == UEngineInput::IsPress(VK_RIGHT) || true == UEngineInput::IsPress(VK_LEFT))
	{
		StateChange(EPlayState::Move);
		return;
	}
}

void AMario::Move(float _DeltaTime)
{
	if (
			(true == UEngineInput::IsFree(VK_RIGHT) && true == UEngineInput::IsFree(VK_LEFT)) ||
			(true == UEngineInput::IsPress(VK_RIGHT) && true == UEngineInput::IsPress(VK_LEFT))
		)
	{
		FVector MoveDirVector = FVector::Zero;
		switch (Dir)
		{
		case EActorDir::Left:
			MoveDirVector = FVector::Right;
			break;
		case EActorDir::Right:
			MoveDirVector = FVector::Left;
			break;
		}

		if (abs(MoveVector.X) > 5.0f)
		{
			MoveVector += MoveDirVector * BreakSpeed * _DeltaTime;
			MoveUpdate(_DeltaTime);
			return;
		}
		else
		{
			MoveVector = FVector::Zero;
			StateChange(EPlayState::Idle);
			return;
		}
	}

	if (true == UEngineInput::IsDown(VK_SPACE))
	{
		StateChange(EPlayState::Jump);
		return;
	}

	if (true == UEngineInput::IsPress(VK_RIGHT))
	{
		if (MoveVector.X < -30.0f)
		{
			StateChange(EPlayState::Reverse);
			return;
		}

		if (MoveVector.X <= MaxMoveSpeed)
		{
			MoveVector += FVector::Right * MoveAcc * _DeltaTime;
		}
		else
		{
			MoveVector.X = MaxMoveSpeed;
		}
	}

	if (true == UEngineInput::IsPress(VK_LEFT))
	{
		if (MoveVector.X > 30.0f)
		{
			StateChange(EPlayState::Reverse);
			return;
		}

		if (MoveVector.X >= -MaxMoveSpeed)
		{
			MoveVector += FVector::Left * MoveAcc * _DeltaTime;
		}
		else
		{
			MoveVector.X = -MaxMoveSpeed;
		}
	}

	MoveUpdate(_DeltaTime);
}

void AMario::Jump(float _DeltaTime)
{
	MoveUpdate(_DeltaTime);

	if (JumpVector.Y == 0.0f && GravityVector.Y == 0.0f)
	{
		if (MoveVector.X == 0.0f)
		{
			StateChange(EPlayState::Idle);
			return;
		}
		else
		{
			StateChange(EPlayState::Move);
			return;
		}
	}

	if (true == UEngineInput::IsPress(VK_RIGHT))
	{
		MoveVector += FVector::Right * MoveAcc * 0.5f * _DeltaTime;
	}

	if (true == UEngineInput::IsPress(VK_LEFT))
	{
		MoveVector += FVector::Left * MoveAcc * 0.5f * _DeltaTime;
	}

	if (UEngineInput::IsUp(VK_SPACE))
	{
		JumpVector = FVector::Zero;
	}
}

void AMario::Reverse(float _DeltaTime)
{
	FVector MoveDirVector = FVector::Zero;
	switch (Dir)
	{
	case EActorDir::Left:
		MoveDirVector = FVector::Left;
		break;
	case EActorDir::Right:
		MoveDirVector = FVector::Right;
		break;
	}

	if (abs(MoveVector.X) < 5.0f)
	{
		MoveVector.X = 0.0f;
		StateChange(EPlayState::Idle);
		return;
	}
	else
	{
		MoveVector += MoveDirVector * BreakSpeed * _DeltaTime;
	}

	MoveUpdate(_DeltaTime);
}

void AMario::MoveUpdate(float _DeltaTime)
{
	FVector MarioPos = GetActorLocation();
	Color8Bit CurPosColor = UContentsHelper::MapColImage->GetColor(MarioPos.iX(), MarioPos.iY(), Color8Bit::MagentaA);
	if (CurPosColor != Color8Bit::MagentaA)
	{
		GravityVector += FVector::Down * GravityAcc * _DeltaTime;
	}
	else
	{
		GravityVector = FVector::Zero;
		JumpVector = FVector::Zero;
	}
	FVector TotalForceVector = MoveVector + JumpVector + GravityVector;
	AddActorLocation(TotalForceVector * _DeltaTime);
}

