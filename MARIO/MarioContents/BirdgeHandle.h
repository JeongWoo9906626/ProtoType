#pragma once
#include <EngineCore/Actor.h>
#include "ContentsHelper.h"

class ABridge;

class ABirdgeHandle : public AActor
{
public:
	ABirdgeHandle();
	~ABirdgeHandle();

	ABirdgeHandle(const ABirdgeHandle& _Other) = delete;
	ABirdgeHandle(ABirdgeHandle&& _Other) noexcept = delete;
	ABirdgeHandle& operator=(const ABirdgeHandle& _Other) = delete;
	ABirdgeHandle& operator=(ABirdgeHandle&& _Other) noexcept = delete;

	void AddBridge(ABridge* _Bridge);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void DestroyBridge(float _DeltaTime);

private:
	UCollision* Collision = nullptr;
	UImageRenderer* Renderer = nullptr;

	float DestroyTime = 0.3f;
	float CurDestroyTime = 0.0f;

	bool IsCollision = false;
	int Count = 0;
	
	std::list<ABridge*> BridgeList;
};

