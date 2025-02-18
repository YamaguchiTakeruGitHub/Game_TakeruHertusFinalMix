#pragma once
#include "../Base/Component.h"
#include "../ComponentTransform/ComponentTransform.h"
#include "../../../InputDevice/InputDeviceManager.h"

namespace CONTROLCAMERAPARAMETER
{
	constexpr float CAMERA_ANGLE_SPEED = 0.8f;		// 旋回速度
	constexpr float CAMERA_PLAYER_TARGET_HEIGHT = 100.0f;	// プレイヤー座標からどれだけ高い位置を注視点とするか
	constexpr float CAMERA_PLAYER_DISTANCE = 300.0f;		// プレイヤーとの距離
}


/// <summary>
/// 注視点・カメラ速度・注視点からカメラまでの距離を管理
/// </summary>
class ComponentControlCamera : public Component
{
private:
	std::shared_ptr<ComponentTransform> m_transform;
	std::shared_ptr<InputDeviceManager> m_Idm;

	float m_speed;
	float m_Distance;

	VECTOR m_target;

	float  m_sinParam;
	float  m_cosParam;
	float  m_horizontalAngle;
	float  m_verticalAngle;

public:
	ComponentControlCamera(std::shared_ptr<ComponentTransform> _transform);

	void Init();
	void Update();
	void Draw();
	void Final();

	/*===============================================================*/
	//セッターとゲッター
	/*===============================================================*/

	/*座標のデータ*/
	void SetPosition(const VECTOR& _pos) { m_transform->position = _pos; }
	VECTOR GetPosition() const { return m_transform->position; }

	/*速度のデータ*/
	void SetSpeed(const float& _speed) { m_speed = _speed; }
	float GetSpeed() const { return m_speed; }

	/*注視点までの距離のデータ*/
	void SetDistance(const float& _distance) { m_Distance = _distance; }
	float GetDistance() const { return m_Distance; }

	/*注視点のデータ*/
	void SetTarget(const VECTOR& _target) { m_target = _target; }
	VECTOR GetTarget() const { return m_target; }

	/*Sinパラメータのデータ*/
	void SetSinParam(const float& _sinParam) { m_sinParam = _sinParam; }
	float GetSinParam() const { return m_sinParam; }

	/*Cosパラメータのデータ*/
	void SetCosParam(const float& _cosParam) { m_cosParam = _cosParam; }
	float GetCosParam() const { return m_cosParam; }

	/*水平アングルのデータ*/
	void SetHAngle(const float& _hAngle) { m_horizontalAngle = _hAngle; }
	float GetHAngle() const { return m_horizontalAngle; }

	/*垂直アングルのデータ*/
	void SetVAngle(const float& _vAngle) { m_verticalAngle = _vAngle; }
	float GetVAngle() const { return m_verticalAngle; }
};


//ここでセッターとゲッターを作成しておくことでカメラクラスでの引数指定としての扱い
//安さを指定することができる