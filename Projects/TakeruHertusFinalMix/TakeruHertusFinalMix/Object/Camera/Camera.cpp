#include "Camera.h"


Camera::Camera()
{
	AddComponent<ComponentTransform>();
	m_transform = GetComponent<ComponentTransform>();

	AddComponent<ComponentCollisionSphere>(m_transform);
	m_sphere = GetComponent<ComponentCollisionSphere>();

	//操作カメラ
	AddComponent<ComponentControlCamera>(m_transform);
	m_controlCamera = GetComponent<ComponentControlCamera>();

	AddComponent<ComponentEventCamera>(m_transform);
	m_eventCamera = GetComponent<ComponentEventCamera>();
}

void Camera::Init()
{
	Entity::InitComponents();
	m_sphere->radius = 50.0f;

	SetCameraNearFar(2.0f, 6000.0f);
}

void Camera::Update()
{
	Effekseer_Sync3DSetting();
	//タグがコントロールカメラの場合
	if (m_tag == "controlCamera")
	{
		m_controlCamera->SetTarget(m_target);//ターゲットを設定
		m_controlCamera->Update();//更新
	}
	if (m_tag == "Section_1EventCamera")
	{
		m_eventCamera->SetTarget(m_target);
		m_eventCamera->Section_1UpdateCamera();
	}
	if (m_tag == "Section_2EventCamera")
	{
		m_eventCamera->SetTarget(m_target);
		m_eventCamera->Section_2UpdateCamera();
	}
	if (m_tag == "Section_2EventCameraLeftWeponSelectCamera")
	{
		m_eventCamera->SetTarget(m_target);
		m_eventCamera->Section_2UpdateLeftSelectWeponCamera();
	}
	if (m_tag == "Section_2EventCameraRightWeponSelectCamera")
	{
		m_eventCamera->SetTarget(m_target);
		m_eventCamera->Section_2UpdateRightSelectWeponCamera();
	}
	if (m_tag == "Section_2EventCameraFowerdWeponSelectCamera")
	{
		m_eventCamera->SetTarget(m_target);
		m_eventCamera->Section_2UpdateFowerdSelectWeponCamera();
	}
	if (m_tag == "Section_3EventCamera1")
	{
		m_eventCamera->SetTarget(m_target);
		m_eventCamera->Section_3UpdateEventCamera_1();
	}
	if (m_tag == "Section_3EventCamera2")
	{
		m_eventCamera->SetTarget(m_target);
		m_eventCamera->Section_3UpdateEventCamera_2();
	}
	if (m_tag == "Section_3EventCamera3")
	{
		m_eventCamera->SetTarget(m_target);
		m_eventCamera->Section_3UpdateEventCamera_3();
	}

	if (m_tag == "Section_4EventCamera_1")
	{
		m_eventCamera->SetTarget(m_target);
		m_eventCamera->Section_4EventCamera_1();
	}

	if (m_tag == "Section_4SaveClearEventCamera_2")
	{
		m_eventCamera->SetTarget(m_target);
		m_eventCamera->SetPosition(VGet(700, 200, 700));
		m_eventCamera->Section_4EventCamera_2();
	}

	SetCameraPositionAndTarget_UpVecY(m_transform->position, m_target);
}

void Camera::Draw()
{
	Entity::DrawComponents();
}

void Camera::Final()
{
	Entity::FinalComponents();
}
