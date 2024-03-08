#include "Mario.h"

#include <EnginePlatform\EngineInput.h>
#include <EngineBase\EngineDebug.h>
#include <EngineCore/EngineDebug.h>

#include "ContentsHelper.h"
#include "Goomba.h"
#include "Troopa.h"
#include "Plant.h"
#include "Flag.h"
#include "Brick.h"
#include "Gate.h"
#include "BreakBrick.h"
#include "ItemBox.h"
#include "Mushroom.h"
#include "Sunflower.h"
#include "HiddenGate.h"
#include "HiddenCoin.h"
#include "Koopa.h"
#include "SpinFire.h"
#include "KoopaFire.h"

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
	
	CurDieTime = 0.0f;
	CurDownTime = 0.0f;
	SizeState = EMarioSizeState::Small;
	StateChange(EPlayState::Idle);
}

void AMario::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	FVector PlayerPos = GetActorLocation();
	UEngineDebug::DebugTextPrint("X : " + std::to_string(PlayerPos.X) + ", Y : " + std::to_string(PlayerPos.Y), 30.0f);
	UEngineDebug::DebugTextPrint("\nDeltaTime : " + std::to_string(_DeltaTime), 30.0f);

	if (true == IsChange)
	{
		if (CurNoCollisionTime >= NoCollisionTime)
		{
			Renderer->SetAlpha(1.0f);
			BodyCollision->ActiveOn();
			BottomCollision->ActiveOn();
			HeadCollision->ActiveOn();
			IsChange = false;
		}
		CurNoCollisionTime += _DeltaTime;
		
	}

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



	StateUpdate(_DeltaTime);
}

void AMario::DirCheck()
{
	EActorDir Dir = DirState;

	if (UEngineInput::IsPress(VK_LEFT) && UEngineInput::IsPress(VK_RIGHT))
	{
		AnimationCheck(Dir);
		return;
	}

	if (UEngineInput::IsPress(VK_LEFT))
	{
		Dir = EActorDir::Left;
		AnimationCheck(Dir);
		return;
	}
	if (UEngineInput::IsPress(VK_RIGHT))
	{
		Dir = EActorDir::Right;
		AnimationCheck(Dir);
		return;
	}
}

void AMario::AnimationCheck(EActorDir _Dir)
{
	if (_Dir != DirState)
	{
		DirState = _Dir;
		std::string Name = GetAnimationName(CurAnimationName);
		Renderer->ChangeAnimation(Name, true, Renderer->GetCurAnimationFrame(), Renderer->GetCurAnimationTime());
	}
}

std::string AMario::GetAnimationName(std::string _Name)
{
	std::string SizeName = "";
	std::string DirName = "";

	switch (SizeState)
	{
	case EMarioSizeState::Small:
		SizeName = "_Small";
		break;
	case EMarioSizeState::Big:
		SizeName = "_Big";
		break;
	case EMarioSizeState::Red:
		SizeName = "_Fire";
		break;
	case EMarioSizeState::Star:
		break;
	default:
		break;
	}

	switch (DirState)
	{
	case EActorDir::Left:
		DirName = "_Left";
		break;
	case EActorDir::Right:
		DirName = "_Right";
		break;
	default:
		break;
	}

	CurAnimationName = _Name;

	return _Name + SizeName + DirName;
}

std::string AMario::GetReverseAnimationName(std::string _Name)
{
	std::string SizeName = "";
	std::string DirName = "";

	switch (SizeState)
	{
	case EMarioSizeState::Small:
		SizeName = "_Small";
		break;
	case EMarioSizeState::Big:
		SizeName = "_Big";
		break;
	case EMarioSizeState::Red:
		SizeName = "_Fire";
		break;
	case EMarioSizeState::Star:
		break;
	default:
		break;
	}

	switch (DirState)
	{
	case EActorDir::Left:
		DirName = "_Right";
		break;
	case EActorDir::Right:
		DirName = "_Left";
		break;
	default:
		break;
	}

	CurAnimationName = _Name;

	return _Name + SizeName + DirName;
}

void AMario::StateChange(EPlayState _State)
{
	if (State != _State)
	{
		switch (_State)
		{
		case EPlayState::FreeMove:
			FreeMoveStart();
			break;
		case EPlayState::Idle:
			IdleStart();
			break;
		case EPlayState::Run:
			RunStart();
			break;
		case EPlayState::Jump:
			JumpStart();
			break;
		case EPlayState::Reverse:
			ReverseStart();
			break;
		case EPlayState::GrowUp:
			GrowUpStart();
			break;
		case EPlayState::GrowDown:
			GrowDownStart();
			break;
		case EPlayState::ChangeRed:
			ChangeRedStart();
			break;
		case EPlayState::HiddenStageEnter:
			HiddenStageEnterStart();
			break;
		case EPlayState::HiddenStageOut:
			HiddenStageOutStart();
			break;
		case EPlayState::HiddenStageOutUp:
			HiddenStageOutUpStart();
			break;
		case EPlayState::Die:
			DieStart();
			break;
		case EPlayState::Kill:
			KillStart();
			break;
		case EPlayState::FinishMove:
			FinishMoveStart();
			break;
		case EPlayState::FinishReverse:
			FinishReverseStart();
			break;
		case EPlayState::FinishWalk:
			FinishWalkStart();
			break;
		default:
			break;
		}
	}

	State = _State;
}

void AMario::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case EPlayState::CameraFreeMove:
		CameraFreeMove(_DeltaTime);
		break;
	case EPlayState::FreeMove:
		FreeMove(_DeltaTime);
		break;
	case EPlayState::Idle:
		Idle(_DeltaTime);
		break;
	case EPlayState::Run:
		Run(_DeltaTime);
		break;
	case EPlayState::Jump:
		Jump(_DeltaTime);
		break;
	case EPlayState::Reverse:
		Reverse(_DeltaTime);
		break;
	case EPlayState::GrowUp:
		GrowUp(_DeltaTime);
		break;
	case EPlayState::GrowDown:
		GrowDown(_DeltaTime);
		break;
	case EPlayState::ChangeRed:
		ChangeRed(_DeltaTime);
		break;
	case EPlayState::HiddenStageEnter:
		HiddenStageEnter(_DeltaTime);
		break;
	case EPlayState::HiddenStageOut:
		HiddenStageOut(_DeltaTime);
		break;
	case EPlayState::HiddenStageOutUp:
		HiddenStageOutUp(_DeltaTime);
		break;
	case EPlayState::Die:
		Die(_DeltaTime);
		break;
	case EPlayState::Kill:
		Kill(_DeltaTime);
		break;
	case EPlayState::FinishMove:
		FinishMove(_DeltaTime);
		break;
	case EPlayState::FinishReverse:
		FinishReverse(_DeltaTime);
		break;
	case EPlayState::FinishWalk:
		FinishWalk(_DeltaTime);
		break;
	default:
		break;
	}
}

void AMario::CameraFreeMove(float _DeltaTime)
{
	if (UEngineInput::IsPress(VK_LEFT))
	{
		GetWorld()->AddCameraPos(FVector::Left * _DeltaTime * 2000.0f);
	}

	if (UEngineInput::IsPress(VK_RIGHT))
	{
		GetWorld()->AddCameraPos(FVector::Right * _DeltaTime * 2000.0f);
	}

	if (UEngineInput::IsPress(VK_UP))
	{
		GetWorld()->AddCameraPos(FVector::Up * _DeltaTime * 500.0f);
	}

	if (UEngineInput::IsPress(VK_DOWN))
	{
		GetWorld()->AddCameraPos(FVector::Down * _DeltaTime * 500.0f);
	}

	if (UEngineInput::IsDown('2'))
	{
		StateChange(EPlayState::Idle);
	}
}

void AMario::FreeMove(float _DeltaTime)
{
	FVector CameraMovePos;
	if (UEngineInput::IsPress(VK_LEFT))
	{
		CameraMovePos += FVector::Left * _DeltaTime * FreeMoveSpeed;
	}

	if (UEngineInput::IsPress(VK_RIGHT))
	{
		CameraMovePos += FVector::Right * _DeltaTime * FreeMoveSpeed;
	}

	if (UEngineInput::IsPress(VK_UP))
	{
		CameraMovePos += FVector::Up * _DeltaTime * FreeMoveSpeed;
	}

	if (UEngineInput::IsPress(VK_DOWN))
	{
		CameraMovePos += FVector::Down * _DeltaTime * FreeMoveSpeed;
	}

	AddActorLocation(CameraMovePos);
	GetWorld()->AddCameraPos(CameraMovePos);

	if (UEngineInput::IsDown('1'))
	{
		StateChange(EPlayState::Idle);
	}
}

void AMario::FreeMoveStart()
{
	BodyCollision->ActiveOff();
	BottomCollision->ActiveOff();
	HeadCollision->ActiveOff();
	Renderer->SetAlpha(0.5f);
}

void AMario::IdleStart()
{
	if (false == IsChange)
	{
		BodyCollision->ActiveOn();
		BottomCollision->ActiveOn();
		HeadCollision->ActiveOn();
		Renderer->SetAlpha(1.0f);
	}
	DirCheck();
	SizeState = UContentsHelper::MSizeState;
	Renderer->ChangeAnimation(GetAnimationName("Idle"));
}

void AMario::RunStart()
{
	DirCheck();
	Renderer->ChangeAnimation(GetAnimationName("Move"));
}

void AMario::JumpStart()
{
	DirCheck();
	JumpVector += JumpPower;
	AddActorLocation(FVector::Up * 4);
	Renderer->ChangeAnimation(GetAnimationName("Jump"));
}

void AMario::ReverseStart()
{
	Renderer->ChangeAnimation(GetReverseAnimationName("Reverse"));
}

void AMario::GrowUpStart()
{
	UContentsHelper::MSizeState = SizeState;
	DirCheck();
	std::string DirName = "";
	switch (DirState)
	{
	case EActorDir::Left:
		DirName = "_Left";
		break;
	case EActorDir::Right:
		DirName = "_Right";
		break;
	default:
		break;
	}

	{
		BodyCollision->SetPosition({ 0, -70 });
		BodyCollision->SetScale({ 50, 130 });
	}

	{
		HeadCollision->SetPosition({ 0, -130 });
		HeadCollision->SetScale({ 10, 10 });
	}

	{
		BottomCollision->SetPosition({ 0, -5 });
		BottomCollision->SetScale({ 10, 10 });
	}

	Renderer->ChangeAnimation("GrowUp" + DirName);
}

void AMario::GrowDownStart()
{
	UContentsHelper::MSizeState = SizeState;
	IsChange = true;
	DirCheck();
	std::string DirName = "";
	switch (DirState)
	{
	case EActorDir::Left:
		DirName = "_Left";
		break;
	case EActorDir::Right:
		DirName = "_Right";
		break;
	default:
		break;
	}
	Renderer->SetAlpha(0.5f);
	{
		BodyCollision->SetPosition({ 0, -35 });
		BodyCollision->SetScale({ 50, 64 });
	}

	{
		HeadCollision->SetPosition({ 0, -62 });
		HeadCollision->SetScale({ 10, 10 });
	}

	{
		BottomCollision->SetPosition({ 0, -5 });
		BottomCollision->SetScale({ 10, 10 });
	}

	BodyCollision->ActiveOff();
	BottomCollision->ActiveOff();
	HeadCollision->ActiveOff();

	Renderer->ChangeAnimation("GrowDown" + DirName);
}

void AMario::ChangeRedStart()
{
	UContentsHelper::MSizeState = SizeState;
	DirCheck();
	std::string DirName = "";
	switch (DirState)
	{
	case EActorDir::Left:
		DirName = "_Left";
		break;
	case EActorDir::Right:
		DirName = "_Right";
		break;
	default:
		break;
	}

	{
		BodyCollision->SetPosition({ 0, -70 });
		BodyCollision->SetScale({ 50, 130 });
	}

	{
		HeadCollision->SetPosition({ 0, -130 });
		HeadCollision->SetScale({ 10, 10 });
	}

	{
		BottomCollision->SetPosition({ 0, -5 });
		BottomCollision->SetScale({ 10, 10 });
	}

	Renderer->ChangeAnimation("ChangeRed" + DirName);
}

void AMario::HiddenStageEnterStart()
{
	IsHiddenStage = true;
	CurPortalTime = 0.0f;
	CurScreenChangeTime = 0.0f;

	Renderer->ChangeAnimation(GetAnimationName("Idle"));
	FVector PortalPos = { 3708.0f, 578.0f, 0.0f, 0.0f };
	SetActorLocation(PortalPos);
}

void AMario::HiddenStageOutStart()
{
	IsHiddenStage = false;
	CurPortalTime = 0.0f;
	CurScreenChangeTime = 0.0f;

	Renderer->ChangeAnimation(GetAnimationName("Idle"));
}

void AMario::HiddenStageOutUpStart()
{
	CurPortalTime = 0.0f;
	CurScreenChangeTime = 0.0f;
}

void AMario::DieStart()
{
	JumpVector = DieJumpPower;
	BodyCollision->ActiveOff();
	HeadCollision->ActiveOff();
	BottomCollision->ActiveOff();
	Renderer->ChangeAnimation("Die");
}

void AMario::KillStart()
{
	DirCheck();
	GravityPower = FVector::Zero;
	JumpVector = KillJumpPower;
	Renderer->ChangeAnimation(GetAnimationName("Jump"));
}

void AMario::FinishMoveStart()
{
	std::string FinishMoveName = "";

	switch (SizeState)
	{
	case EMarioSizeState::Small:
		FinishMoveName = "_Small";
		break;
	case EMarioSizeState::Big:
		FinishMoveName = "_Big";
		break;
	case EMarioSizeState::Red:
		FinishMoveName = "_Fire";
		break;
	case EMarioSizeState::Star:
		break;
	default:
		break;
	}
	Renderer->ChangeAnimation("Down" + FinishMoveName);
}

void AMario::FinishReverseStart()
{
	AddActorLocation(FVector::Right * 12.0f);

	std::string FinishMoveName = "";

	switch (SizeState)
	{
	case EMarioSizeState::Small:
		FinishMoveName = "_Small";
		break;
	case EMarioSizeState::Big:
		FinishMoveName = "_Big";
		break;
	case EMarioSizeState::Red:
		FinishMoveName = "_Fire";
		break;
	case EMarioSizeState::Star:
		break;
	default:
		break;
	}

	Renderer->ChangeAnimation("DownReverse" + FinishMoveName);
}

void AMario::FinishWalkStart()
{
	std::string FinishMoveName = "";

	switch (SizeState)
	{
	case EMarioSizeState::Small:
		FinishMoveName = "_Small";
		break;
	case EMarioSizeState::Big:
		FinishMoveName = "_Big";
		break;
	case EMarioSizeState::Red:
		FinishMoveName = "_Fire";
		break;
	case EMarioSizeState::Star:
		break;
	default:
		break;
	}

	Renderer->ChangeAnimation("Move" + FinishMoveName + "_Right");
}

void AMario::Idle(float _DeltaTime)
{
	GroundUp();
	MoveUpdate(_DeltaTime);
	if (true == UEngineInput::IsDown('1'))
	{
		StateChange(EPlayState::FreeMove);
		return;
	}

	if (true == UEngineInput::IsDown('2'))
	{
		StateChange(EPlayState::CameraFreeMove);
		return;
	}

	if (true == UEngineInput::IsDown('E'))
	{
		if (UContentsHelper::MapName._Equal("FinalStage"))
		{
			float XPos = 7700.0f;
			float YPos = 0.0f;

			FVector ChangePos = { XPos, YPos, 0.0f, 0.0f };
			GetWorld()->SetCameraPos(ChangePos);

			FVector SpawnPos = { 7945.0f, 641.0f, 0.0f, 0.0f };
			SetActorLocation(SpawnPos);
		}
		if (UContentsHelper::MapName._Equal("FirstStage"))
		{
			float XPos = 12460.0f;
			float YPos = 0.0f;

			FVector ChangePos = { XPos, YPos, 0.0f, 0.0f };
			GetWorld()->SetCameraPos(ChangePos);

			FVector SpawnPos = { 12900.0f, 833.0f, 0.0f, 0.0f };
			SetActorLocation(SpawnPos);
		}
	}


	if (true == UEngineInput::IsPress(VK_LEFT) && true == UEngineInput::IsPress(VK_RIGHT))
	{
		return;
	}

	if (true == UEngineInput::IsPress(VK_LSHIFT))
	{
		MaxRunSpeed = ShiftRunSpeed;
		CurBreakSpeed = ShiftBreakSpeed;
	}
	if (true == UEngineInput::IsFree(VK_LSHIFT))
	{
		MaxRunSpeed = NoramlRunSpeed;
		CurBreakSpeed = NormalBreakSpeed;
	}

	if (true == UEngineInput::IsPress(VK_LEFT) || true == UEngineInput::IsPress(VK_RIGHT))
	{
		StateChange(EPlayState::Run);
		GroundUp();
		return;
	}

	if (true == UEngineInput::IsDown(VK_SPACE) && false == IsJump)
	{
		StateChange(EPlayState::Jump);
		GroundUp();
		return;
	}
}

void AMario::Run(float _DeltaTime)
{
	GroundUp();
	if (true == UEngineInput::IsDown(VK_SPACE))
	{
		StateChange(EPlayState::Jump);
		GroundUp();
		return;
	}

	if (true == UEngineInput::IsFree(VK_LEFT) && true == UEngineInput::IsFree(VK_RIGHT))
	{
		if (abs(RunVector.X) <= 5.0f)
		{
			RunVector.X = 0.0f;
			StateChange(EPlayState::Idle);
			GroundUp();
			return;
		}
		else
		{
			MoveUpdate(_DeltaTime);
			return;
		}
	}

	if (true == UEngineInput::IsPress(VK_LEFT) && true == UEngineInput::IsPress(VK_RIGHT))
	{
		if (abs(RunVector.X) <= 5.0f)
		{
			RunVector.X = 0.0f;
			StateChange(EPlayState::Idle);
			GroundUp();
			return;
		}
		else
		{
			FVector BreakDirState = FVector::Zero;
			switch (DirState)
			{
			case EActorDir::Left:
				BreakDirState = FVector::Right;
				break;
			case EActorDir::Right:
				BreakDirState = FVector::Left;
				break;
			default:
				break;
			}
			SubtractRunVector(BreakDirState * _DeltaTime);
			MoveUpdate(_DeltaTime);
			return;
		}
	}

	if (true == UEngineInput::IsPress(VK_LSHIFT))
	{
		MaxRunSpeed = ShiftRunSpeed;
		CurBreakSpeed = ShiftBreakSpeed;
		Renderer->ChangeAnimation(GetAnimationName("MoveFast"));
	}
	if (true == UEngineInput::IsFree(VK_LSHIFT))
	{
		MaxRunSpeed = NoramlRunSpeed;
		CurBreakSpeed = NormalBreakSpeed;
		Renderer->ChangeAnimation(GetAnimationName("Move"));
	}

	if (true == UEngineInput::IsPress(VK_LEFT))
	{
		if (RunVector.X > 0.0f)
		{
			StateChange(EPlayState::Reverse);
			GroundUp();
			return;
		}

		AddRunVector(FVector::Left * _DeltaTime);
		MoveUpdate(_DeltaTime);
		return;
	}

	if (true == UEngineInput::IsPress(VK_RIGHT))
	{
		if (RunVector.X < 0.0f)
		{
			StateChange(EPlayState::Reverse);
			GroundUp();
			return;
		}

		AddRunVector(FVector::Right * _DeltaTime);
		MoveUpdate(_DeltaTime);
		return;
	}
}

void AMario::Jump(float _DeltaTime)
{
	IsJump = true;

	if (UEngineInput::IsPress(VK_LEFT))
	{
		AddRunVector(FVector::Left * _DeltaTime);
	}
	if (UEngineInput::IsPress(VK_RIGHT))
	{
		AddRunVector(FVector::Right * _DeltaTime);
	}

	if (UEngineInput::IsUp(VK_SPACE))
	{
		JumpVector = FVector::Zero;
	}

	MoveUpdate(_DeltaTime);

	FVector Location = GetActorLocation();

	Color8Bit Color = UContentsHelper::MapColImage->GetColor(Location.iX(), Location.iY(), Color8Bit::MagentaA);

	if (Color == Color8Bit(255, 0, 255, 0))
	{
		JumpVector = FVector::Zero;
		GravityPower = FVector::Zero;

		if (RunVector.X > 0.0f)
		{
			if (true == UEngineInput::IsPress(VK_LEFT))
			{
				StateChange(EPlayState::Reverse);
				GroundUp();
				return;
			}
		}

		if (RunVector.X < 0.0f)
		{
			if (true == UEngineInput::IsPress(VK_RIGHT))
			{
				StateChange(EPlayState::Reverse);
				GroundUp();
				return;
			}
		}
	}

	if (JumpVector.Y == 0.0f && GravityPower.Y == 0.0f)
	{
		StateChange(EPlayState::Idle);
		GroundUp();
		return;
	}
}

void AMario::Reverse(float _DeltaTime)
{
	if (true == UEngineInput::IsDown(VK_SPACE))
	{
		StateChange(EPlayState::Jump);
		GroundUp();
		return;
	}

	if (DirState == EActorDir::Left)
	{
		if (true == UEngineInput::IsDown(VK_LEFT))
		{
			StateChange(EPlayState::Run);
			GroundUp();
			return;
		}

		if (true == UEngineInput::IsPress(VK_RIGHT))
		{
			SubtractRunVector(FVector::Right * _DeltaTime);
		}

		if (0.0f <= RunVector.X)
		{
			RunVector.X = 0.0f;
			ReverseDir();
			StateChange(EPlayState::Idle);
			GroundUp();
			return;
		}
	}

	if (DirState == EActorDir::Right)
	{
		if (true == UEngineInput::IsDown(VK_RIGHT))
		{
			StateChange(EPlayState::Run);
			GroundUp();
			return;
		}

		if (true == UEngineInput::IsPress(VK_LEFT))
		{
			SubtractRunVector(FVector::Left * _DeltaTime);
		}

		if (0.0f >= RunVector.X)
		{
			RunVector.X = 0.0f;
			ReverseDir();
			StateChange(EPlayState::Idle);
			GroundUp();
			return;
		}
	}

	MoveUpdate(_DeltaTime);
}

void AMario::GrowUp(float _DeltaTime)
{
	if (CurChangeTime > ChangeTime)
	{
		JumpVector.Y = 0.0f;
		GravityPower.Y = 0.0f;
		CurChangeTime = 0.0f;
		StateChange(EPlayState::Idle);
		return;
	}
	CurChangeTime += _DeltaTime;
}

void AMario::GrowDown(float _DeltaTime)
{
	if (CurChangeTime > ChangeTime)
	{
		JumpVector.Y = 0.0f;
		GravityPower.Y = 0.0f;
		CurChangeTime = 0.0f;

		StateChange(EPlayState::Idle);
		return;
	}
	CurChangeTime += _DeltaTime;
}

void AMario::ChangeRed(float _DeltaTime)
{
	if (CurChangeTime > ChangeTime)
	{
		JumpVector.Y = 0.0f;
		GravityPower.Y = 0.0f;
		CurChangeTime = 0.0f;
		StateChange(EPlayState::Idle);
		return;
	}
	CurChangeTime += _DeltaTime;
}

void AMario::HiddenStageEnter(float _DeltaTime)
{
	float DownSpeed = 0.0f;
	switch (SizeState)
	{
	case EMarioSizeState::Small:
		DownSpeed = 32.0f;
		break;
	case EMarioSizeState::Big:
	case EMarioSizeState::Red:
		DownSpeed = 63.0f;
		break;
	default:
		break;
	}
	if (CurPortalTime <= PortalTime)
	{
		AddActorLocation(FVector::Down * _DeltaTime * DownSpeed);
		CurPortalTime += _DeltaTime;
	}
	else
	{
		if (CurScreenChangeTime <= ScreenChangeTime)
		{
			CurScreenChangeTime += _DeltaTime;
		}
		else
		{
			float XPos = 3064.0f;
			float YPos = GEngine->MainWindow.GetWindowScale().Y;

			FVector ChangePos = { XPos, YPos, 0.0f, 0.0f };
			GetWorld()->SetCameraPos(ChangePos);

			FVector SpawnPos = { 3218.0f, 1262.0f, 0.0f, 0.0f };
			SetActorLocation(SpawnPos);
			StateChange(EPlayState::Idle);
			return;
		}
	}
}

void AMario::HiddenStageOut(float _DeltaTime)
{
	if (CurPortalTime <= PortalTime)
	{
		AddActorLocation(FVector::Right * _DeltaTime * 30.f);
		CurPortalTime += _DeltaTime;
	}
	else
	{
		if (CurScreenChangeTime <= ScreenChangeTime)
		{
			CurScreenChangeTime += _DeltaTime;
		}
		else
		{
			float XPos = 10260.0f;
			float YPos = 0.0f;

			FVector ChangePos = { XPos, YPos, 0.0f, 0.0f };
			GetWorld()->SetCameraPos(ChangePos);

			FVector SpawnPos = { 10492.0f, 803.0f, 0.0f, 0.0f };
			SetActorLocation(SpawnPos);
			StateChange(EPlayState::HiddenStageOutUp);
			return;
		}
	}
}

void AMario::HiddenStageOutUp(float _DeltaTime)
{
	if (CurPortalTime < PortalTime)
	{
		AddActorLocation(FVector::Up * _DeltaTime * 50.0f);
		CurPortalTime += _DeltaTime;
	}
	else
	{
		StateChange(EPlayState::Idle);
		return;
	}
}

void AMario::Die(float _DeltaTime)
{
	if (CurDieTime >= DieTime)
	{
		AddActorLocation(JumpVector * (_DeltaTime));
		JumpVector += GravityAcc * _DeltaTime;
	}
	else
	{
		CurDieTime += _DeltaTime;
	}
}

void AMario::Kill(float _DeltaTime)
{
	MoveUpdate(_DeltaTime);
	State = EPlayState::Jump;
	Color8Bit Color = UContentsHelper::MapColImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::MagentaA);
	if (Color == Color8Bit(255, 0, 255, 0))
	{
		JumpVector = FVector::Zero;
		StateChange(EPlayState::Idle);
		GroundUp();
		return;
	}
}

void AMario::FinishMove(float _DeltaTime)
{
	Color8Bit Color = UContentsHelper::MapColImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::MagentaA);
	if (Color == Color8Bit(255, 0, 255, 0))
	{
		StateChange(EPlayState::FinishReverse);
		return;
	}
	else
	{
		AddActorLocation(FVector::Down * FinishDownSpeed * _DeltaTime);
	}
}

void AMario::FinishReverse(float _DeltaTime)
{
	if (DownTime <= CurDownTime)
	{
		StateChange(EPlayState::FinishWalk);
		return;
	}
	else
	{
		CurDownTime += _DeltaTime;
	}
}

void AMario::FinishWalk(float _DeltaTime)
{
	JumpVector = FVector::Zero;
	GroundUp();
	AddRunVector(FVector::Right * _DeltaTime);
	MoveUpdate(_DeltaTime);
}

void AMario::MarioInit(AMario* _Mario)
{
	if (AMario::MainPlayer == nullptr) {
		AMario::MainPlayer = _Mario;
	}
	else {
		return;
	}
}

void AMario::ReverseDir()
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

void AMario::AddRunVector(const FVector& _DirDelta)
{
	RunVector += _DirDelta * RunAcc;
}

void AMario::SubtractRunVector(const FVector& _DirDelta)
{
	RunVector += _DirDelta * CurBreakSpeed;
}

void AMario::RunVectorUpdate(float _DeltaTime)
{
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
		RunVector = FVector::Zero;
	}

	if (true == UEngineInput::IsFree(VK_LEFT) && true == UEngineInput::IsFree(VK_RIGHT))
	{
		if (0.001 <= RunVector.Size2D())
		{
			RunVector += (-RunVector.Normalize2DReturn()) * _DeltaTime * CurBreakSpeed * 5;
		}
		else
		{
			RunVector = FVector::Zero;
		}
	}

	if (MaxRunSpeed <= RunVector.Size2D())
	{
		RunVector = RunVector.Normalize2DReturn() * MaxRunSpeed;
	}

	if (State == EPlayState::FinishWalk)
	{
		RunVector = RunVector.Normalize2DReturn() * FinishMoveSpeed;
	}

	float CamerPos = GetWorld()->GetCameraPos().X;

	if (CheckPos.X <= CamerPos)
	{
		RunVector = FVector::Zero;
	}
}

void AMario::GravityVectorUpdate(float _DeltaTime)
{
	if (!IsCollision) 
	{
		GravityPower += GravityAcc * _DeltaTime;
	}
	Color8Bit Color = UContentsHelper::MapColImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::MagentaA);
	if (Color == Color8Bit(255, 0, 255, 0))
	{
		IsJump = false;
		GravityPower = FVector::Zero;
	}
}

void AMario::MoveVectorUpdate(float _DeltaTime)
{
	TotalForceVector = FVector::Zero;
	TotalForceVector = TotalForceVector + RunVector;
	TotalForceVector = TotalForceVector + GravityPower;
	TotalForceVector = TotalForceVector + JumpVector;
}

void AMario::Move(float _DeltaTime)
{
	FVector CurPos = GetActorLocation();
	FVector CurCameraPos = GetWorld()->GetCameraPos();
	FVector NextMarioPos = CurPos + (RunVector * _DeltaTime);
	float Center = GEngine->MainWindow.GetWindowScale().hX();
	float ScaleX = GEngine->MainWindow.GetWindowScale().X;
	if (false == IsHiddenStage && CurCameraPos.X + Center < NextMarioPos.X && CurCameraPos.X + ScaleX <= UContentsHelper::MapColImage->GetScale().X)
	{
		GetWorld()->AddCameraPos(RunVector * _DeltaTime);
	}

	if (EActorDir::Left == DirState)
	{
		NextMarioPos.X -= 32.0f;
	}
	if (EActorDir::Right == DirState)
	{
		NextMarioPos.X += 32.0f;
	}

	if (CurCameraPos.X <= NextMarioPos.X)
	{
		AddActorLocation(TotalForceVector * _DeltaTime);
	}
}

void AMario::MoveUpdate(float _DeltaTime)
{
	GravityVectorUpdate(_DeltaTime);
	RunVectorUpdate(_DeltaTime);
	MoveVectorUpdate(_DeltaTime);
	Move(_DeltaTime);
}

void AMario::GroundUp()
{
	if (false == IsStageEnd)
	{
		while (true)
		{
			FVector Location = GetActorLocation();
			Location.Y -= 1.0f;
			Color8Bit Color = UContentsHelper::MapColImage->GetColor(Location.iX(), Location.iY(), Color8Bit::MagentaA);
			if (Color == Color8Bit(255, 0, 255, 0))
			{
				AddActorLocation(FVector::Up);
			}
			else
			{
				break;
			}
		}
	}
}
