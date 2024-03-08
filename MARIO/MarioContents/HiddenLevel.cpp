#include "HiddenLevel.h"

#include "BackGround.h"
#include "ContentsHelper.h"
#include "Mario.h"
#include "Gate.h"

UHiddenLevel::UHiddenLevel()
{
}

UHiddenLevel::~UHiddenLevel()
{
}

void UHiddenLevel::BeginPlay()
{
	ULevel::BeginPlay();

	ABackGround* BackGroundMap = SpawnActor<ABackGround>(ERenderOrder::Map);
	BackGroundMap->SetMapImage("Stage01_Hidden.png");
	BackGroundMap->SetCollisionMapImage("Stage01_Hidden_Col.png");
	BackGroundMap->SwitchDebug();

	AMario* Mario = SpawnActor<AMario>(ERenderOrder::Player);
	Mario->SetName("Player");
	Mario->SetActorLocation({ 200, 500 });
}

void UHiddenLevel::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);
}

void UHiddenLevel::LevelStart(ULevel* _PrevLevel)
{
	ULevel::LevelStart(_PrevLevel);
}

void UHiddenLevel::LevelEnd(ULevel* _NextLevel)
{
	ULevel::LevelEnd(_NextLevel);
}
