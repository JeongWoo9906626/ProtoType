#pragma once
#include <EngineCore/Actor.h>
#include "ContentsHelper.h"

class MarioFire : public AActor
{
public:
	MarioFire();
	~MarioFire();

	MarioFire(const MarioFire& _Other) = delete;
	MarioFire(MarioFire&& _Other) noexcept = delete;
	MarioFire& operator=(const MarioFire& _Other) = delete;
	MarioFire& operator=(MarioFire&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime);

private:
	UImageRenderer* Renderer = nullptr;
	UCollision* Collision = nullptr;

};

