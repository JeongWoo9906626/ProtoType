#pragma once
#include <EngineCore/Level.h>

class UHiddenLevel : public ULevel
{
public:
	UHiddenLevel();
	~UHiddenLevel();

	UHiddenLevel(const UHiddenLevel& _Other) = delete;
	UHiddenLevel(UHiddenLevel&& _Other) noexcept = delete;
	UHiddenLevel& operator=(const UHiddenLevel& _Other) = delete;
	UHiddenLevel& operator=(UHiddenLevel&& _Other) noexcept = delete;
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void LevelStart(ULevel* _PrevLevel) override;
	void LevelEnd(ULevel* _NextLevel) override;

private:

};

