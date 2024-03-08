#pragma once
#include <EngineCore/Level.h>

class UFinalLevel : public ULevel
{
public:
	UFinalLevel();
	~UFinalLevel();

	UFinalLevel(const UFinalLevel& _Other) = delete;
	UFinalLevel(UFinalLevel&& _Other) noexcept = delete;
	UFinalLevel& operator=(const UFinalLevel& _Other) = delete;
	UFinalLevel& operator=(UFinalLevel&& _Other) noexcept = delete;
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void LevelStart(ULevel* _PrevLevel) override;
	void LevelEnd(ULevel* _NextLevel) override;

private:

};

