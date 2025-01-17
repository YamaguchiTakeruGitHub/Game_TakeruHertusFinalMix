#include "EnemySmallFish.h"


EnemySmallFish::EnemySmallFish()
	: Collidable(Collidable::Priority::High , GameObjectTag::Enemy, ColliderData::Kind::Sphere)
	, m_modelHandle(-1)
	, scale(VGet(0,0,0))
	, helth(100)
	, tempScreen(-1)

	, count(0)
	, isSpawn(false)

	, state()
	, animCount(0)
{
	auto sphereColliderData = std::dynamic_pointer_cast<ColliderDataSphere3D>(m_colliderData);
	sphereColliderData->radius = 20.0f;

	m_path = std::make_shared<Path>();
	/*m_anim = std::make_shared<AnimationLib>();*/
	m_effect = std::make_shared<EffectLib>("../Asset/3D/Effect/Spawn.efkefc");
	

	state.currentState = eState_Walk;
	state.isIdle = false;
	state.isWalk = false;
	state.isAttack = false;
}


EnemySmallFish::~EnemySmallFish()
{
}

void EnemySmallFish::Init(std::shared_ptr<Physics> _physics)
{
	Collidable::Init(_physics);
	m_righdbody.Init(false);
	m_righdbody.SetPosition(VGet(-100.0f, 20.0f, 0.0f));
	m_modelHandle = MV1LoadModel("../Asset/3D/Character/Enemy/EnemySmole/Enemy_fox.mv1");
	scale = VGet(0.02f, 0.02f, 0.02f);

	m_effect.get()->Init("../Asset/3D/Effect/Spawn.efkefc");
	
	count = 0;
	isSpawn = false;

	helth = 100;

	state.currentState = eState_Walk;
	animCount = 0;
	state.isIdle = false;
	state.isWalk = false;
	state.isAttack = false;
}

void EnemySmallFish::Final(std::shared_ptr<Physics> _physics)
{
	Collidable::Final(_physics);
	MV1DeleteModel(m_modelHandle);
	m_effect.get()->Final();
}

void EnemySmallFish::Update(std::shared_ptr<Physics> _physics)
{
	auto sphereData = std::dynamic_pointer_cast<ColliderDataSphere3D>(m_colliderData);
	VECTOR start = m_righdbody.GetPosition();
	VECTOR END = VAdd(start, VGet(0, -sphereData->radius, 0));
	
	// 矢印キーを押していたらプレイヤーを移動させる
	// 向きを決定する.
	VECTOR dir = VGet(0, 0, 0);

	if (animCount >= 1000) animCount = 0;
	else { animCount++; }

	state.isAttack = false;

	AutoMove();
	
	if (state.isAttack == false)
	{
		// 余計な数値が入るので、純粋に長さ１の向きとして正規化する
		if (VSquareSize(dir) > 0)
		{
			dir = VNorm(dir);
		}

		m_righdbody.SetVelocity(VGet(dir.x, dir.y, dir.z));

		m_righdbody.SetPosition(m_righdbody.GetPosition());
		MV1SetPosition(m_modelHandle, m_righdbody.GetPosition());
	}



	MV1SetScale(m_modelHandle, scale);

	VECTOR efPos = m_righdbody.GetPosition();
	m_effect.get()->Update(efPos);

}

void EnemySmallFish::Draw(std::shared_ptr<Physics> _physics)
{
	Spawn();

	if (isSpawn == true)
	{
		if (helth >= 0)
		{
			MV1DrawModel(m_modelHandle);
		}
	}

	m_effect.get()->Draw();

	


	if (state.isAttack == true)
	{
		DrawCircle(1100, 400, 100, 0xff0000, true);
		DrawString(1100, 400, "attack", 0x000000);
		DrawSphere3D(m_righdbody.GetPosition(), 100.0f, 5, 0xffff00, 0xffff00, false);

	}

	if (state.isIdle == true)
	{
		DrawCircle(1100, 400, 100, 0x00ff00, true);
		DrawString(1100, 400, "idle", 0x000000);

	}

	if (state.isWalk == true)
	{
		DrawCircle(1100, 400, 100, 0x0000ff, true);
		DrawString(1100, 400, "walk", 0x000000);

	}

	DrawSphere3D(m_righdbody.GetPosition(), 100.0f, 5, 0x00ffff, 0x00ffff, false);

	DrawFormatString(1100, 420, 0xffffff, "ac : %d", animCount);
	DrawFormatString(1100, 440, 0xffffff, "cni : %d", state.currentState);
}

void EnemySmallFish::OnCollide(const std::shared_ptr<Collidable>& _colider)
{
#ifdef _DEBUG
	std::string message = "小敵が";
	if (_colider->GetTag() == GameObjectTag::Enemy)
	{
		message += "敵";
	}
	else if (_colider->GetTag() == GameObjectTag::EnemyDinamic)
	{
		message += "大敵";
	}
	else if (_colider->GetTag() == GameObjectTag::EnemyMidle)
	{
		message += "中敵";
	}
	else if (_colider->GetTag() == GameObjectTag::Player)
	{
		message += "プレイヤー";
	}

	message += "と当たった！\n";
	printfDx(message.c_str());
#endif // _DEBUG
}

void EnemySmallFish::SetPath(std::shared_ptr<Path> _path)
{
	m_path = _path;
	currentNodeIndex = 0;
}

void EnemySmallFish::HitTarget(VECTOR _center, float _r)
{
	VECTOR ctop = VSub(m_righdbody.GetPosition(), _center);
	auto ctopS = VSize(ctop);

	auto ctop_r = (_r + 100.0f);

	if (ctopS <= ctop_r)
	{
		state.isAttack == true;
		
		VECTOR direction = VNorm(VSub(_center, m_righdbody.GetPosition()));
		m_righdbody.SetPosition(VAdd(m_righdbody.GetPosition(), VScale(direction, 2.7f)));
		MV1SetPosition(m_modelHandle, VAdd(m_righdbody.GetPosition(), VScale(direction, 0.7f)));

	}
}

void EnemySmallFish::State()
{


}

void EnemySmallFish::State_Idle()
{
	//m_anim->ChangeAnim();
}

void EnemySmallFish::State_Walk()
{
	AutoMove();
}

void EnemySmallFish::State_Attack()
{
	//m_anim->ChangeAnim();
}



void EnemySmallFish::Spawn()
{
	if (count <= 100)
	{
		count++;
	}
	else
	{
		count = 0;
		isSpawn = true;
	}

	if (isSpawn == false && count >= 90)
	{
		m_effect.get()->PlayEffectLib();
	}

}

void EnemySmallFish::AutoMove()
{
	if (!m_path || m_path->nodes.empty()) return;

	VECTOR curretnNode = m_path->nodes[currentNodeIndex].position;
	nextNode = (currentNodeIndex + 1 < m_path->nodes.size())
		? m_path->nodes[currentNodeIndex + 1].position
		: m_path->nodes[currentNodeIndex].position;
	if (state.isAttack == false)
	{
		VECTOR direction = VNorm(VSub(nextNode, m_righdbody.GetPosition()));
		m_righdbody.SetPosition(VAdd(m_righdbody.GetPosition(), VScale(direction, 1.7f)));
	}
	if (VSize(VSub(m_righdbody.GetPosition(), nextNode)) <= 10.0f)
	{
		currentNodeIndex = (currentNodeIndex + 1) % m_path->nodes.size();
	}

}

bool EnemySmallFish::UpdateAnim(int _modelHandle, int _attachNo, float _startTime)
{
	if (_attachNo == -1) return false;

	float nowFrame = MV1GetAttachAnimTime(_modelHandle, _attachNo);

	float totalAnimFrame = MV1GetAttachAnimTotalTime(_modelHandle, _attachNo);

	bool isLoop = false;

	while (totalAnimFrame <= nowFrame)
	{
		nowFrame -= totalAnimFrame;
		nowFrame += _startTime;
		isLoop = true;
	}

	MV1SetAttachAnimTime(_modelHandle, _attachNo, nowFrame);

	return isLoop;
}

void EnemySmallFish::ChangeAnim(int _modelHandle, int _animIndex, float _animSpeed)
{
	if (m_animPrevNo != -1)
	{
		MV1DetachAnim(_modelHandle, m_animPrevNo);
	}

	m_animPrevIdx = m_animNowIdx;
	m_animNowIdx = _animIndex;

	m_animPrevNo = m_animCurrentNo;

	m_animCurrentNo = MV1AttachAnim(_modelHandle, _animIndex);

	m_animBlendRate = 0.0f;

	m_animSpeed = _animSpeed;
}


