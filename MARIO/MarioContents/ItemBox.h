#pragma once
#include <EngineCore/Actor.h>
#include "ContentsHelper.h"

class AItemBox : public AActor
{
public:
	AItemBox();
	~AItemBox();

	AItemBox(const AItemBox& _Other) = delete;
	AItemBox(AItemBox&& _Other) noexcept = delete;
	AItemBox& operator=(const AItemBox& _Other) = delete;
	AItemBox& operator=(AItemBox&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

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
	EMarioSizeState MarioSizeState = EMarioSizeState::None;

	float MaxHitUpSize = 30.0f;
	float HitUpSpeed = 300.0f;
	FVector FirstPos = FVector::Zero;
	FVector MoveUpPos = FVector::Zero;
	FVector MoveDownPos = FVector::Zero;
};

