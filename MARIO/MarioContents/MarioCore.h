#pragma once
#include <EngineCore/EngineCore.h>

// Ό³Έν :
class UMarioCore : public UEngineCore
{
public:
	// constrcuter destructer
	UMarioCore();
	~UMarioCore();

	// delete Function
	UMarioCore(const UMarioCore& _Other) = delete;
	UMarioCore(UMarioCore&& _Other) noexcept = delete;
	UMarioCore& operator=(const UMarioCore& _Other) = delete;
	UMarioCore& operator=(UMarioCore&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void End() override;

private:

};

