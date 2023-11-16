#pragma once


constexpr float BroomFxLiveTime = 0.6f;


// ���� :
class BroomParticle : public GameEngineActor
{
public:
	// constrcuter destructer
	BroomParticle();
	~BroomParticle();

	// delete Function
	BroomParticle(const BroomParticle& _Other) = delete;
	BroomParticle(BroomParticle&& _Other) noexcept = delete;
	BroomParticle& operator=(const BroomParticle& _Other) = delete;
	BroomParticle& operator=(BroomParticle&& _Other) noexcept = delete;

	void Init();

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;


	void ApplyDepth();
	void RendererSetting();
	void ParticleUpate(float _Delta);

private:
	std::shared_ptr<GameEngineSpriteRenderer> FxRenderer = nullptr;

	

};

