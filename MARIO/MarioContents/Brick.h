#pragma once
#include <EngineCore/Actor.h>
#include "ContentsHelper.h"

class ABrick : public AActor
{
public:
	ABrick();
	~ABrick();

	ABrick(const ABrick& _Other) = delete;
	ABrick(ABrick&& _Other) noexcept = delete;
	ABrick& operator=(const ABrick& _Other) = delete;
	ABrick& operator=(ABrick&& _Other) noexcept = delete;
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void SetHitCount(int _HitCount);

	void StateChange(EBoxState _State);
	void StateUpdate(float _DeltaTime);

	void IdleStart();
	void HitStart();
	void BlockStart();

	void Idle(float _DeltaTime);
	void Hit(float _DeltaTime);
	void Block(float _DeltaTime);

private:
	UImageRenderer* Renderer = nullptr;
	UCollision* TopCollision = nullptr;
	UCollision* BottomCollision = nullptr;
	UCollision* LeftCollision = nullptr;
	UCollision* RightCollision = nullptr;

	EBoxState State = EBoxState::None;

	int HitCount = 10;
	bool IsBreak = false;
	float MaxHitUpSize = 30.0f;
	float HitUpSpeed = 300.0f;
	FVector FirstPos = FVector::Zero;
	FVector MoveUpPos = FVector::Zero;
	FVector MoveDownPos = FVector::Zero;
};

