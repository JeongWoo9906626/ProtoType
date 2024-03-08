#pragma once
#include <EngineCore/Actor.h>
#include "ContentsHelper.h"

class AGoomba;
class ATroopa;
class APlant;
class AFlag;
class ABrick;
class ABreakBrick;
class AItemBox;
class AGate;
class AMushroom;
class ASunflower;
class AKoopa;
class ASpinFire;
class AKoopaFire;
// Ό³Έν :
class AMario : public AActor
{
	friend AGoomba;
	friend ATroopa;
	friend APlant;
	friend AFlag;
	friend ABrick;
	friend AGate;
	friend ABreakBrick;
	friend AItemBox;
	friend AMushroom;
	friend ASunflower;
	friend AKoopa;
	friend ASpinFire;
	friend AKoopaFire;

public:
	//static AMario* GetMainPlayer();
	static AMario* MainPlayer;

	// constrcuter destructer
	AMario();
	~AMario();

	// delete Function
	AMario(const AMario& _Other) = delete;
	AMario(AMario&& _Other) noexcept = delete;
	AMario& operator=(const AMario& _Other) = delete;
	AMario& operator=(AMario&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void StateChange(EPlayState _State);
	void StateUpdate(float _DeltaTime);

	void DirCheck();
	std::string GetAnimationName();

	void IdleStart();
	void MoveStart();
	void JumpStart();
	void ReverseStart();

	void Idle(float _DeltaTime);
	void Move(float _DeltaTime);
	void Jump(float _DeltaTime);
	void Reverse(float _DeltaTime);

private:
	UImageRenderer* Renderer = nullptr;
	UCollision* BodyCollision = nullptr;
	UCollision* HeadCollision = nullptr;
	UCollision* BottomCollision = nullptr;

	EPlayState State = EPlayState::None;
	EActorDir Dir = EActorDir::Left;

	FVector MoveVector = FVector::Zero;
	float MoveAcc = 300.0f;
	float MaxMoveSpeed = 300.0f;
	float BreakSpeed = 600.0f;

	FVector GravityVector = FVector::Zero;
	float GravityAcc = 600.0f;

	FVector JumpVector = FVector::Zero;
	float JumpPower = 500.0f;

	void MoveUpdate(float _DeltaTime);
};

