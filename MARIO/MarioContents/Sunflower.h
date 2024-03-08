#pragma once
#include <EngineCore/Actor.h>
#include "ContentsHelper.h"

class ASunflower : public AActor
{
public:
	ASunflower();
	~ASunflower();

	ASunflower(const ASunflower& _Other) = delete;
	ASunflower(ASunflower&& _Other) noexcept = delete;
	ASunflower& operator=(const ASunflower& _Other) = delete;
	ASunflower& operator=(ASunflower&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void StateChange(EItemState _State);
	void StateUpdate(float _DeltaTime);

	void SpawnStart();

	void Spawn(float _DeltaTime);

private:
	UImageRenderer* Renderer = nullptr;
	UCollision* BodyCollision = nullptr;
	UCollision* BottomCollision = nullptr;

	EMarioSizeState MarioSizeState = EMarioSizeState::None;
	EItemState State = EItemState::None;
	EActorDir DirState = EActorDir::Right;

	bool DestroyValue = false;
	bool IsBoxCollision = false;

	float SpawnUpSpeed = 100.0f;
	float MoveSpeed = 200.0f;
	float GravitySpeed = 500.0f;
	float DirUnitVector = -1.0f;
};

