#pragma once
#include "../Base/Component.h"
#include "../ComponentTransform/ComponentTransform.h"

namespace EVENTCAMERA
{
	constexpr float CAMERA_ANGLE_SPEED = 0.8f;		// 旋回速度
	constexpr float CAMERA_PLAYER_TARGET_HEIGHT = 100.0f;	// プレイヤー座標からどれだけ高い位置を注視点とするか
	constexpr float CAMERA_PLAYER_DISTANCE = 300.0f;		// プレイヤーとの距離
}

class ComponentEventCamera : public Component
{
private:
	std::shared_ptr<ComponentTransform> m_transform;

	float m_speed;
	float m_Distance;

	VECTOR m_target;

	float  m_sinParam;
	float  m_cosParam;
	float  m_horizontalAngle;
	float  m_verticalAngle;

	/*セクション用*/
	int m_section_2Time;


	//セクション４
	int m_section_4Time_1;

public:
	ComponentEventCamera(std::shared_ptr<ComponentTransform> _transform);

	void Init() override;
	void Update() override;
	void Draw() override;
	void Final() override;

	void Section_1UpdateCamera();
	void Section_2UpdateCamera();
	void Section_2UpdateLeftSelectWeponCamera();
	void Section_2UpdateRightSelectWeponCamera();
	void Section_2UpdateFowerdSelectWeponCamera();

	void Section_3UpdateEventCamera_1();
	void Section_3UpdateEventCamera_2();
	void Section_3UpdateEventCamera_3();

	void Section_4EventCamera_1();
	void Section_4EventCamera_2();



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

