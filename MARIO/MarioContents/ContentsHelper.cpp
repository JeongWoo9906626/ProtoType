#include "ContentsHelper.h"
#include "Mario.h"

UWindowImage* UContentsHelper::MapColImage = nullptr;
EMarioSizeState UContentsHelper::MSizeState = EMarioSizeState::Small;
std::string UContentsHelper::MapName = "";
int UContentsHelper::CoinCount = 100;
int UContentsHelper::Score = 1000000;
int UContentsHelper::Time = 1400;
int UContentsHelper::MainStage = 1;
int UContentsHelper::SubStage = 1;

bool UContentsHelper::KoopaDie = false;
bool UContentsHelper::KoopaWake = false;
bool UContentsHelper::KoopaIsFire = false;
bool UContentsHelper::MarioDie = false;

UContentsHelper::UContentsHelper() 
{
}

UContentsHelper::~UContentsHelper() 
{
}

