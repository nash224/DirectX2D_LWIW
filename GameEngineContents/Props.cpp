#include "PreCompile.h"
#include "Props.h"

Props::Props()
	:
	m_Renderer(nullptr),
	m_Position(float4::ZERO)
{
}

Props::~Props() 
{
}


void Props::Start()
{

}

void Props::Update(float _Delta)
{

}

void Props::LevelStart(class GameEngineLevel* _NextLevel)
{

}

void Props::LevelEnd(class GameEngineLevel* _NextLevel)
{

}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void Props::CreateRenderer(int _Order)
{
	m_Renderer = CreateComponent<GameEngineSpriteRenderer>(_Order);
	if (nullptr == m_Renderer)
	{
		MsgBoxAssert("잘못 만들어진 렌더러입니다.");
		return;
	}
}

void Props::SetSprite(std::string_view _SpriteName)
{
	if (nullptr == m_Renderer)
	{
		MsgBoxAssert("렌더러를 생성하지 않고 스프라이트를 세팅할 수 없습니다.");
		return;
	}

	m_Renderer->SetSprite(_SpriteName);
}

void Props::SetWorldPosition(const float4& _Position)
{
	Transform.SetLocalPosition(_Position);
}

void Props::CreateAnimation(

	std::string_view _AnimationName,
	std::string_view _SpriteName,
	float _Inter /*= 0.1f*/,
	unsigned int _Start /*= -1*/,
	unsigned int _End /*= -1*/,
	bool _Loop /*= true*/
)
{
	if (nullptr == m_Renderer)
	{
		MsgBoxAssert("렌더러를 생성하지 않고 애니메이션을 생성하려고 했습니다.");
		return;
	}

	m_Renderer->CreateAnimation(_AnimationName, _SpriteName, _Inter, _Start, _End, _Loop);
}


void Props::ChangeAnimation(std::string_view _AnimationName)
{
	if (nullptr == m_Renderer)
	{
		MsgBoxAssert("렌더러를 생성하지 않고 애니메이션을 생성하려고 했습니다.");
		return;
	}

	m_Renderer->ChangeAnimation(_AnimationName);
	m_Renderer->AutoSpriteSizeOn();
}


void Props::ActorRelease()
{
	if (nullptr == m_Renderer)
	{
		m_Renderer->Death();
		m_Renderer = nullptr;
	}

	Death();
}