#pragma once
#include <EngineCore/Actor.h>
#include "ContentsHelper.h"

class AGoomba : public AActor
{
public:
	AGoomba();
	~AGoomba();

	AGoomba(const AGoomba& _Other) = delete;
	AGoomba(AGoomba&& _Other) noexcept = delete;
	AGoomba& operator=(const AGoomba& _Other) = delete;
	AGoomba& operator=(AGoomba&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void StateChange(EMonsterState _State);
	void StateUpdate(float _DelatTime);

	void MoveStart();
	void CollisionMoveStart();
	void DeadStart();

	void Move(float _DeltaTime);
	void CollisionMove(float _DeltaTime);
	void GravityMove(float _DeltaTime);

	void ChangeDir(EActorDir _State);
	void CheckWindowPosition();

private:
	UImageRenderer* Renderer = nullptr;
	UCollision* BodyCollision = nullptr;
	UCollision* BottomCollision = nullptr;

	EMonsterState State = EMonsterState::None;
	EActorDir DirState = EActorDir::Left;

	bool DestroyValue = false;
	bool IsBoxCollision = false;

	float MoveSpeed = 100.0f;
	float GravitySpeed = 500.0f;
	float DirUnitVector = -1.0f;
};

