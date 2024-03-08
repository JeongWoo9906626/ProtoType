#pragma once
#include <EngineCore/Actor.h>
#include "ContentsHelper.h"

class ATroopa : public AActor
{
public:
	ATroopa();
	~ATroopa();

	ATroopa(const ATroopa& _Other) = delete;
	ATroopa(ATroopa&& _Other) noexcept = delete;
	ATroopa& operator=(const ATroopa& _Other) = delete;
	ATroopa& operator=(ATroopa&& _Other) noexcept = delete;
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void StateChange(EMonsterState _State);
	void StateUpdate(float _DeltaTime);

	void AnimationCheck(EActorDir _Dir);

	std::string GetAnimationName(std::string _Name);

	void MoveStart();
	void DeadStart();
	void ShootStart();
	void WakeStart();

	void GravityMove(float _DeltaTime);
	void Move(float _DeltaTime);
	void Dead(float _DeltaTime);
	void Shoot(float _DeltaTime);
	void Wake(float _DeltaTime);

	void ChangeDir(EActorDir _State);
	void CheckWindowPosition();

private:
	UImageRenderer* Renderer = nullptr;
	UCollision* BodyCollision = nullptr;

	EMonsterState State = EMonsterState::None;
	EActorDir DirState = EActorDir::Left;
	EActorDir DeadState = EActorDir::Left;
	EMonsterShootDir ShootState = EMonsterShootDir::Left;
	
	FVector ShootMoveVector = FVector::Zero;

	std::string CurAnimationName = "";

	bool DeadValue = false;
	bool DestoryValue = false;

	bool IsAttack = false;

	float MoveSpeed = 100.0f;
	float ShootSpeed = 600.0f;
	float GravitySpeed = 500.0f;
	
	float DirUnitVector = -1.0f;

	float CollisionHideTime = 0.1f;
	float CollisionCurTime = 0.0f;

	float WakeUpTime = 5.0f;
	float CurTime = 0.0f;
};

