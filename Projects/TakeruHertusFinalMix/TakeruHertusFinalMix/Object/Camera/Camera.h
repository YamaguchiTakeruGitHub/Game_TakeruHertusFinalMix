#pragma once
#include "../Entity/Entity.h"

class Camera : public Entity
{
private:
	std::shared_ptr<ComponentTransform> m_transform;
	std::shared_ptr<ComponentCollisionSphere> m_sphere;
	std::shared_ptr<ComponentControlCamera> m_controlCamera;
	std::shared_ptr<ComponentEventCamera> m_eventCamera;

	VECTOR m_target;
	const char* m_tag;

public:
	Camera();

	void Init();
	void Update();
	void Draw();
	void Final();

	/*===============================================================*/
	//セッターとゲッター
	/*===============================================================*/

	void SetTag(const char* _tag) { m_tag = _tag; }
	const char* GetTag() const { return m_tag; }

	void SetRadius(const float& _radius) { m_sphere->radius; }
	float GetRadius() const { return m_sphere->radius; }

	void SetPosition(const VECTOR& _pos) { m_transform->position; }
	VECTOR GetPosition() const { return m_transform->position; }

	void SetTarget(const VECTOR& _target) { m_target = _target; }
	VECTOR GetTarget() const { return m_target; }

	void SetHAngle(const float& _hAngle) { m_controlCamera->SetHAngle(_hAngle); }
	float GetHAngle() const { return m_controlCamera->GetHAngle(); }

	void SetCosParam(const float& _cosParam) { m_controlCamera->SetCosParam(_cosParam); }
	float GetCosParam() const { return m_controlCamera->GetCosParam(); }

	void SetSinParam(const float& _sinParam) { m_controlCamera->SetSinParam(_sinParam); }
	float GetSinParam() const { return m_controlCamera->GetSinParam(); }
};

//タグシステムの導入をすることでゲームシーンでタグの切り替えを行いカメラクラスで
//カメラの種類を変更させる

