#include "PlayLevel.h"

#include "ContentsHelper.h"

#include "BackGround.h"
#include "UI.h"

#include "Mario.h"

UPlayLevel::UPlayLevel()
{
}

UPlayLevel::~UPlayLevel()
{
}

void UPlayLevel::BeginPlay()
{
	ULevel::BeginPlay();

	UContentsHelper::MapName = "FirstStage";

	ABackGround* BackGroundMap = SpawnActor<ABackGround>(ERenderOrder::Map);
	BackGroundMap->SetMapImage("Stage01.png");
	BackGroundMap->SetCollisionMapImage("Stage01_Col.png");
	BackGroundMap->SwitchDebug();

	AUI* UI = SpawnActor<AUI>(ERenderOrder::UI);
	UI->SetActorLocation({ 200, 200 });

	AMario* Mario = SpawnActor<AMario>(ERenderOrder::Player);
	Mario->SetName("Player");
	Mario->SetActorLocation({ 200, 500 });

}

void UPlayLevel::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);
}

void UPlayLevel::LevelStart(ULevel* _PrevLevel)
{
	ULevel::LevelStart(_PrevLevel);
}

void UPlayLevel::LevelEnd(ULevel* _NextLevel)
{
	ULevel::LevelEnd(_NextLevel);
	GEngine->DestroyLevel("Play");
}
