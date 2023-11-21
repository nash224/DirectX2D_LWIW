#pragma once
#include "DynamicEntity.h"
#include "ActorEnum.h"


static constexpr const float MAX_STAMINA = 1000.0f;
static constexpr const float MAX_FUEL = 1000.0f;


enum class EELLIE_STATE
{
	None,
	Idle,
	SlowWalk,
	Walk,
	Run,
	Throw,
	Riding_Standing,
	Riding_Moving,
	Riding_Boosting,
	Approach,
	ButterflyNet,
	RootUp,
	Sit,
	MongSiri,
	Wait,
	Juicy,
	Cheer,
	Fail,
	Drink,
};

enum class EELLIE_STATUS
{
	None,
	Normal,
	Riding,
};


struct PixelCheckPoint
{
public:
	float4 TopLeft = float4::ZERO;
	float4 TopRight = float4::ZERO;
	float4 LeftTop = float4::ZERO;
	float4 LeftBottom = float4::ZERO;
	float4 RightTop = float4::ZERO;
	float4 RightBottom = float4::ZERO;
	float4 BottomLeft = float4::ZERO;
	float4 BottomRight = float4::ZERO;

};


// 설명 : 주인공 앨리입니다. 
class Ellie : public DynamicEntity
{
public:
	static Ellie* MainEllie;

private:
	static EELLIE_STATUS g_Status;
	static int Day;
	static float Stamina;
	static float BroomFuel;
	static bool FirstInitCheck;

private:
	class EllieBroom
	{
	public:
		enum class EBROOMSTRUCT
		{
			Head,
			Body,
			Max,
		};

	public:
		std::vector<std::shared_ptr<GameEngineSpriteRenderer>> BroomRenderer;

		float TransitionCoolDown = 0.0f;
		static constexpr const float Transition_Recovery_Time = 0.4f;

	};


public:
	// constrcuter destructer
	Ellie();
	~Ellie();

	// delete Function
	Ellie(const Ellie& _Other) = delete;
	Ellie(Ellie&& _Other) noexcept = delete;
	Ellie& operator=(const Ellie& _Other) = delete;
	Ellie& operator=(Ellie&& _Other) noexcept = delete;

	// 이니셜
	void Init();

	void OnControl();
	void OffControl();
	void FinishWork();
	void WaitDone(EELLIE_STATE _State);
	void SetAnimationByDirection(EDIRECTION _Dir = EDIRECTION::CENTER);

	EELLIE_STATE GetState() const
	{
		return m_State;
	}

	float GetStamina() const
	{
		return Stamina;
	}

	float GetBroomFuel() const
	{
		return BroomFuel;
	}


protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

	void RendererSetting();
	void VirgilSetting();
	void BroomSetting();
	void CollisionSetting();
	void SetPixelPointBaseOnCenter();
	
	void ChangeBroomAndVirgilIndexToRidingMode(int _HeadIndex, int _BodyIndex, int _VirgilIndex);

	void ChangeFrameAnimationInterAllDirection(std::string_view _AnimationName, const std::vector<float>& _Inter);
	void ChangeShawdowSprite(std::string_view _AnimationName);
	void ChangeVirgilSprite(std::string_view _AnimationName);
	void ChangeBroomSprite();


	// 레벨 시작 초기화 함수
	void OnLevelStart();
	void RenewStatus();
	void ChangeStatus(const EELLIE_STATUS _Status);

private:
	void UpdateCollision();
	void UpdatePortalCollsiion();
	void UpdateInteractionCollsiion();
	void CheckNetCollision();

	void UpdateTestCode();

	// FSM
	void ChangeState(EELLIE_STATE _State);
	void UpdateState(float _Delta);
	void ChangeAnimationByDirection(std::string_view  _StateName, bool _DirectionInfluence = true, bool _Force =  false, unsigned int _Index = 0);
	void ChangeDirectionAnimation(std::string_view  _StateName);
	

	void StartIdle();
	void StartSlowWalk();
	void StartWalk();
	void StartRun();
	void StartThrow();
	void StartRiding_Standing();
	void StartRiding_Moving();
	void StartRiding_Boosting();
	void StartApproach();
	void StartButterflyNet();
	void StartRootUp();
	void StartSit();
	void StartMongSiri();
	void StartWait();
	void StartJuicy();
	void StartCheer();
	void StartFail();
	void StartDrink();


	void UpdateIdle(float _Delta);
	void UpdateSlowWalk(float _Delta);
	void UpdateWalk(float _Delta);
	void UpdateRun(float _Delta);
	void UpdateThrow(float _Delta);
	void UpdateRiding_Standing(float _Delta);
	void UpdateRiding_Moving(float _Delta);
	void UpdateRiding_Boosting(float _Delta);
	void UpdateApproach(float _Delta);
	void UpdateButterflyNet(float _Delta);
	void UpdateRootUp(float _Delta);
	void UpdateSit(float _Delta);
	void UpdateMongSiri(float _Delta);
	void UpdateWait(float _Delta);
	void UpdateJuicy(float _Delta);
	void UpdateCheer(float _Delta);
	void UpdateFail(float _Delta);
	void UpdateDrink(float _Delta);


	void EndIdle();
	void EndApproach();
	void EndButterflyNet();
	void EndRootUp();
	void EndSit();
	void EndMongSiri();
	void EndWait();
	void EndJuicy();


	bool InputTestPattern();
	bool UsingTool();
	bool InputRidingMode();

	void SitShadowUpdate();

	void OnRideFx();
	void GenerateBroomDust(float _Delta);
	void GenerateBoostBroomDust(float _Delta);
	void CreateBroomParticle(float _ParticleDistance = 0.0f);
	float4 GetBroomParticlePosition(float _ParticleDistance);

	void ConsumeBroomFuel(float _Delta);

private:
	// 방향 키 감지
	bool DetectMovement();
	bool DetectVerticalMovement();
	bool DetectHorizontalMovement();

	// 방향 계산 함수
	float4 GetDirectionVectorToDir(const EDIRECTION _Direction);
	

	void CalulationMoveForceToNormalStatus(float _Delta, float _MAXMoveForce);
	EDIRECTION ReturnDirectionCheckBothSide(EDIRECTION _Direction, const float4& _LeftCheckPoint, const float4& _RightCheckPoint);

	void DecelerateNotDir(float _Delta, const float _MaxMoveForce);
	float4 GetMoveForceByDir(float _Delta, float _MAXMoveForce, float _Acceleration_Time);
	void LimitMoveVector(float _MAXMoveForce);
	void WallCollision();

	void PlaySFX(std::string_view _FileName);

	void DayChangeEvent();
	void CheckDayChange();

private:
	// 방향키
	EHORIZONTAL_KEY_STATE HorizontalInputKey = EHORIZONTAL_KEY_STATE::Center;
	EVERTICAL_KEY_STATE VerticalInputKey = EVERTICAL_KEY_STATE::Center;

	// 행동
	EELLIE_STATE m_State = EELLIE_STATE::None;
	EELLIE_STATE WaitState = EELLIE_STATE::None;

	EllieBroom Broom;
	std::shared_ptr<GameEngineSpriteRenderer> ShadowRenderer = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> EllieFx = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> Virgil = nullptr;
	std::shared_ptr<GameEngineCollision> m_EllieCol = nullptr;
	std::shared_ptr<GameEngineCollision> NetCollision = nullptr;
	InteractiveActor* OtherEntity = nullptr;
	PixelCheckPoint m_PixelCheckPoint;


	

	float Broom_Particle_Time = 0.0f;
	float BroomUsingTime = 0.0f;

	bool isFinishWork = false;
	bool IsControl = true;
	bool IsCollected = false;
	bool IsHolding = false;
	bool IsWaitDone = false;
	bool isRootup = false;

	static constexpr const float Broom_Particle_Cool_Down = 0.08f;

	static constexpr const float LWIW_Ellie_Y_Correction = 30.0f;
	
	static constexpr float SlowWalk_Speed = 100.0f;
	static constexpr float Walk_Speed = 160.0f;
	static constexpr float Run_Speed = 220.0f;
	static constexpr float Riding_Move_Acceleration_Time = 0.8f;
	static constexpr float Riding_Boost_Acceleration_Time = 0.8f;
	static constexpr float Riding_Move_Speed = 270.0f;
	static constexpr float Riding_Boost_Speed = 330.0f;

	static constexpr const float FOVAngle = 60.0f;
	static constexpr const float FrictionForce = 0.5f;

};