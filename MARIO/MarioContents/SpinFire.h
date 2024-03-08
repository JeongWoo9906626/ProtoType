#pragma once
#include <EngineCore/Actor.h>
#include "ContentsHelper.h"

// Ό³Έν :
class ASpinFire : public AActor
{
public:
	// constrcuter destructer
	ASpinFire();
	~ASpinFire();

	// delete Function
	ASpinFire(const ASpinFire& _Other) = delete;
	ASpinFire(ASpinFire&& _Other) noexcept = delete;
	ASpinFire& operator=(const ASpinFire& _Other) = delete;
	ASpinFire& operator=(ASpinFire&& _Other) noexcept = delete;

	void SetSpinDir(EActorDir _Dir);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void FireSpin(float _DeltaTime);

private:
	UImageRenderer* Renderer[6] = { nullptr, };
	UCollision* Collision[6] = { nullptr, };
	EActorDir Dir = EActorDir::Left;

	float Degree = 0.0f;
	float SpinDir = 0.0f;
};

