#include "PreCompile.h"
#include "PlayLevel.h"


// Actor
#include "Ellie.h"
#include "FadeObject.h"

// Manager
#include "CameraControler.h"
#include "UIManager.h"
#include "TimeManager.h"



std::shared_ptr<TimeManager> PlayLevel::s_TimeManager;
float PlayLevel::PlaySoundInfo::BGMVolume = 1.0f;
PlayLevel::PlayLevel()
{
}

PlayLevel::~PlayLevel()
{
}

void PlayLevel::Start()
{
	ContentsLevel::Start();

	if (nullptr == s_TimeManager)
	{
		s_TimeManager = std::make_shared<TimeManager>();
		s_TimeManager->Init();
	}
}

void PlayLevel::Update(float _Delta)
{
	ContentsLevel::Update(_Delta);

	if (nullptr != s_TimeManager)
	{
		s_TimeManager->Update(_Delta);
	}
}

void PlayLevel::LevelStart(GameEngineLevel* _NextLevel)
{
	ContentsLevel::LevelStart(_NextLevel);

	if (false == LevelInitCheck)
	{
		CreateEllie();			// 敲饭捞绢 积己
		CreateUIManager();		// UI 积己
	}


	std::shared_ptr<FadeObject> Fade = CreateActor<FadeObject>(EUPDATEORDER::Fade);
	Fade->CallFadeIn(0.2f);

	LevelInitCheck = true;
}

void PlayLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	ContentsLevel::LevelEnd(_NextLevel);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



// UI 概聪历 积己
void PlayLevel::CreateUIManager()
{
	m_UIManager = CreateActor<UIManager>(EUPDATEORDER::UIMagnaer);
	m_UIManager->Init();
}

// 敲饭捞绢 积己
void PlayLevel::CreateEllie()
{
	m_Ellie = CreateActor<Ellie>(EUPDATEORDER::Player);
	m_Ellie->Init();
}


void PlayLevel::PlaySoundInfo::PlayBGM(std::string_view _BGMName, std::string_view _BGM_SFXName /*= ""*/)
{
	if (nullptr == GameEngineSound::FindSound(_BGMName))
	{
		ResourceLoad();
	}

	if (BGMName == _BGMName.data())
	{
		return;
	}

	Stop();

	BGM = GameEngineSound::SoundPlay(_BGMName, 999);
	BGM.SetVolume(GlobalValue::GetSoundVolume() * BGMVolume);

	BGMName = _BGMName.data();

	if (false == _BGM_SFXName.empty())
	{
		BGM_SFX = GameEngineSound::SoundPlay(_BGM_SFXName, 999);
		BGM_SFX.SetVolume(GlobalValue::GetSoundVolume() * BGMVolume);
	}
}

void PlayLevel::PlaySoundInfo::ResourceLoad()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("Resources");
	Dir.MoveChild("Resources\\Sound\\BGM\\Play");
	std::vector<GameEngineFile> Files = Dir.GetAllFile();
	for (GameEngineFile pFile : Files)
	{
		GameEngineSound::SoundLoad(pFile.GetStringPath());
	}
}

void PlayLevel::PlaySoundInfo::Stop()
{
	BGM.Stop();
	BGM_SFX.Stop();
}

void PlayLevel::PlaySoundInfo::SetVolume(float _Value)
{
	if (_Value > Max_BGM_Volume)
	{
		BGMVolume = Max_BGM_Volume;
	}

	if (_Value < Min_BGM_Volume)
	{
		BGMVolume = Min_BGM_Volume;
	}

	BGMVolume = _Value;
}