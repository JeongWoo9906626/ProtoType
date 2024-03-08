#include "FinalLevel.h"
#include "BackGround.h"
#include "ContentsHelper.h"
#include "Mario.h"
#include "ItemBox.h"
#include "UI.h"
#include "BirdgeHandle.h"
#include "Bridge.h"
#include "Koopa.h"
#include "SpinFire.h"
#include "KoopaEvent.h"
#include "KoopaFire.h"

UFinalLevel::UFinalLevel()
{
}

UFinalLevel::~UFinalLevel()
{
}

void UFinalLevel::BeginPlay()
{
	ULevel::BeginPlay();

	UContentsHelper::Time = 1300;
	UContentsHelper::SubStage = 4;
	UContentsHelper::MapName = "FinalStage";

	ABackGround* BackGroundMap = SpawnActor<ABackGround>(ERenderOrder::Map);
	BackGroundMap->SetMapImage("Stage04.png");
	BackGroundMap->SetCollisionMapImage("Stage04_Col.png");
	BackGroundMap->SwitchDebug();

	AUI* UI = SpawnActor<AUI>(ERenderOrder::UI);
	UI->SetActorLocation({ 200, 200 });

	AMario* Mario = SpawnActor<AMario>(ERenderOrder::Player);
	Mario->SetName("Player");
	Mario->SetActorLocation({ 100, 700 });

	ABirdgeHandle* BirdgeHandle = SpawnActor<ABirdgeHandle>(ERenderOrder::Brick);
	BirdgeHandle->SetName("Handle");
	BirdgeHandle->SetActorLocation({ 9050, 540 });

	AKoopa* Koopa = SpawnActor<AKoopa>(ERenderOrder::Monster);
	Koopa->SetActorLocation({ 8862, 600 });

	AKoopaEvent* KoopaEvent = SpawnActor<AKoopaEvent>(ERenderOrder::Gate);
	KoopaEvent->SetActorLocation({ 8000, 600 });

	AItemBox* ItemBrick;
	ItemBrick = SpawnActor<AItemBox>(ERenderOrder::Brick);
	ItemBrick->SetName("Item");
	ItemBrick->SetActorLocation({ 1950, 448 });

	// SpinFire
	{
		ASpinFire* SpinFire1 = SpawnActor<ASpinFire>(ERenderOrder::Monster);
		SpinFire1->SetActorLocation({ 1950, 690 });
		SpinFire1->SetSpinDir(EActorDir::Left);

		ASpinFire* SpinFire2 = SpawnActor<ASpinFire>(ERenderOrder::Monster);
		SpinFire2->SetActorLocation({ 3165, 440 });
		SpinFire2->SetSpinDir(EActorDir::Left);

		ASpinFire* SpinFire3 = SpawnActor<ASpinFire>(ERenderOrder::Monster);
		SpinFire3->SetActorLocation({ 3870, 440 });
		SpinFire3->SetSpinDir(EActorDir::Left);

		ASpinFire* SpinFire4 = SpawnActor<ASpinFire>(ERenderOrder::Monster);
		SpinFire4->SetActorLocation({ 4324, 440 });
		SpinFire4->SetSpinDir(EActorDir::Left);

		ASpinFire* SpinFire5 = SpawnActor<ASpinFire>(ERenderOrder::Monster);
		SpinFire5->SetActorLocation({ 4890, 630 });
		SpinFire5->SetSpinDir(EActorDir::Left);

		ASpinFire* SpinFire6 = SpawnActor<ASpinFire>(ERenderOrder::Monster);
		SpinFire6->SetActorLocation({ 5410, 630 });
		SpinFire6->SetSpinDir(EActorDir::Left);

		ASpinFire* SpinFire7 = SpawnActor<ASpinFire>(ERenderOrder::Monster);
		SpinFire7->SetActorLocation({ 5660, 315 });
		SpinFire7->SetSpinDir(EActorDir::Right);
	}

	// Bridge
	{
		ABridge* Bridge1 = SpawnActor<ABridge>(ERenderOrder::Brick);
		Bridge1->SetActorLocation({ 8222, 672 });
		BirdgeHandle->AddBridge(Bridge1);

		ABridge* Bridge2 = SpawnActor<ABridge>(ERenderOrder::Brick);
		Bridge2->SetActorLocation({ 8286, 672 });
		BirdgeHandle->AddBridge(Bridge2);

		ABridge* Bridge3 = SpawnActor<ABridge>(ERenderOrder::Brick);
		Bridge3->SetActorLocation({ 8350, 672 });
		BirdgeHandle->AddBridge(Bridge3);

		ABridge* Bridge4 = SpawnActor<ABridge>(ERenderOrder::Brick);
		Bridge4->SetActorLocation({ 8414, 672 });
		BirdgeHandle->AddBridge(Bridge4);

		ABridge* Bridge5 = SpawnActor<ABridge>(ERenderOrder::Brick);
		Bridge5->SetActorLocation({ 8478, 672 });
		BirdgeHandle->AddBridge(Bridge5);

		ABridge* Bridge6 = SpawnActor<ABridge>(ERenderOrder::Brick);
		Bridge6->SetActorLocation({ 8542, 672 });
		BirdgeHandle->AddBridge(Bridge6);

		ABridge* Bridge7 = SpawnActor<ABridge>(ERenderOrder::Brick);
		Bridge7->SetActorLocation({ 8606, 672 });
		BirdgeHandle->AddBridge(Bridge7);

		ABridge* Bridge8 = SpawnActor<ABridge>(ERenderOrder::Brick);
		Bridge8->SetActorLocation({ 8670, 672 });
		BirdgeHandle->AddBridge(Bridge8);

		ABridge* Bridge9 = SpawnActor<ABridge>(ERenderOrder::Brick);
		Bridge9->SetActorLocation({ 8734, 672 });
		BirdgeHandle->AddBridge(Bridge9);

		ABridge* Bridge10 = SpawnActor<ABridge>(ERenderOrder::Brick);
		Bridge10->SetActorLocation({ 8798, 672 });
		BirdgeHandle->AddBridge(Bridge10);

		ABridge* Bridge11 = SpawnActor<ABridge>(ERenderOrder::Brick);
		Bridge11->SetActorLocation({ 8862, 672 });
		BirdgeHandle->AddBridge(Bridge11);

		ABridge* Bridge12 = SpawnActor<ABridge>(ERenderOrder::Brick);
		Bridge12->SetActorLocation({ 8926, 672 });
		BirdgeHandle->AddBridge(Bridge12);

		ABridge* Bridge13 = SpawnActor<ABridge>(ERenderOrder::Brick);
		Bridge13->SetActorLocation({ 8990, 672 });
		BirdgeHandle->AddBridge(Bridge13);
	}
}

void UFinalLevel::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);
}

void UFinalLevel::LevelStart(ULevel* _PrevLevel)
{
	ULevel::LevelStart(_PrevLevel);
	int a = 0;
}

void UFinalLevel::LevelEnd(ULevel* _NextLevel)
{
	ULevel::LevelEnd(_NextLevel);
}
