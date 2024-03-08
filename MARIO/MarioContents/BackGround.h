#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class ABackGround : public AActor
{
public:
	// constrcuter destructer
	ABackGround();
	~ABackGround();

	// delete Function
	ABackGround(const ABackGround& _Other) = delete;
	ABackGround(ABackGround&& _Other) noexcept = delete;
	ABackGround& operator=(const ABackGround& _Other) = delete;
	ABackGround& operator=(ABackGround&& _Other) noexcept = delete;

	void SetMapImage(std::string_view _MapImageName);
	void SetCollisionMapImage(std::string_view _MapImageName);
	void SwitchDebug();

	UImageRenderer* GetRenderer()
	{
		return Renderer;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UImageRenderer* Renderer = nullptr;
	UImageRenderer* CollisionRenderer = nullptr;
};

