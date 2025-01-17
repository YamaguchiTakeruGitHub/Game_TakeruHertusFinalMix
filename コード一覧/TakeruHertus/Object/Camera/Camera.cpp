#include "Camera.h"
#include <cmath>
#include <EffekseerForDXLib.h>

// カメラの回転速度
#define CAMERA_ANGLE_SPEED			1.5f

Camera::Camera()
    : m_position(VGet(0.0f, 0.0f, 50.0f))
    , m_LookAt(VGet(0, 0, 0))
    , m_previous(VGet(0, 0, 0))
    , m_angle(0.0f)
    , m_horizontalAngle(0.0f)
    , m_verticalAngle(0.0f)

    , m_Distance(80.0f)

    , lerpFactor()

    , m_cosParam(0.0f)
    , m_sinParam(0.0f)
    , m_speed   (1.5f)

{
    m_Idm = std::make_shared<InputDeviceManager>();
}

Camera::~Camera()
{
}

void Camera::Init()
{
    m_Idm.get()->Init();

    m_position = VGet(0.0f, 80.0f, 80.0f);
    m_LookAt = VGet(0, 0, 0);
    m_previous = VGet(0, 0, 0);
    m_angle = DX_PI_F / 4.0f;
    m_horizontalAngle = 0.0f;
    m_verticalAngle = 0.0f;

    m_Distance = 80.0f;

    m_cosParam = std::cos(static_cast<float>(m_horizontalAngle) / 180.0f * DX_PI_F);
    m_sinParam = std::sin(static_cast<float>(m_horizontalAngle) / 180.0f * DX_PI_F);

    lerpFactor = 0.0f;

    m_speed = 1.5f;

    //SetCameraNearFar(1.1f, 1000000.0f);
    SetCameraNearFar(10.0f, 4000.0f);

}

void Camera::Update(VECTOR _target, VECTOR _LookTarget)
{
    m_Idm.get()->Update();
    PlayerContorllCamera(_target, _LookTarget);
   
}

void Camera::PlayerContorllCamera(VECTOR _target, VECTOR _LookTarget)
{
    //左スティックの召喚
    float rightStickX = m_Idm.get()->joyPad->GetRightStickX();
    float rightStickY = m_Idm->joyPad->GetRightStickY();

    if (rightStickX != 0 && rightStickX >= -0.030519f && rightStickX <= 0.0f)
    {
        m_horizontalAngle += m_speed;
        if (m_horizontalAngle >= 180.0f) m_horizontalAngle -= 360.0f;
    }
    if (rightStickX != 0 && rightStickX <= 0.030519f && rightStickX >= 0.0f)
    {
        m_horizontalAngle -= m_speed;
        if (m_horizontalAngle <= -180.0f) m_horizontalAngle += 360.0f;
    }
    if (rightStickY != 0 && rightStickY <= 0.030519f && rightStickY >= 0.0f)
    {
        m_verticalAngle += m_speed;
        if (m_verticalAngle >= 70.0f) m_verticalAngle = 70.0f;
    }
    if (rightStickY != 0 && rightStickY >= -0.030519f && rightStickY <= 0.0f)
    {
        m_verticalAngle -= m_speed;
        if (m_verticalAngle <= -20.0f) m_verticalAngle = -20.0f;
    }

   

    //エフェクト用の制御関数
    Effekseer_Sync3DSetting();

    if (m_Idm->joyPad->isRB == true)
    {
       // LookOnCamera(_target, _LookTarget);
    }
    else
    {
        m_LookAt = _target;
        m_LookAt.y = 10.0f + _target.y;



        m_sinParam = sin(m_verticalAngle / 180.0f * DX_PI_F);
        m_cosParam = cos(m_verticalAngle / 180.0f * DX_PI_F);
        tempPosition1.x = 0.0f;
        tempPosition1.y = m_sinParam * m_Distance;
        tempPosition1.z = -m_cosParam * m_Distance;

        m_sinParam = sin(m_horizontalAngle / 180.0f * DX_PI_F);
        m_cosParam = cos(m_horizontalAngle / 180.0f * DX_PI_F);
        tempPosition2.x = m_cosParam * tempPosition1.x - m_sinParam * tempPosition1.z;
        tempPosition2.y = tempPosition1.y;
        tempPosition2.z = m_sinParam * tempPosition1.x + m_cosParam * tempPosition1.z;
        targetPositon = VAdd(m_LookAt, tempPosition2);

        m_position = VAdd(tempPosition2, m_LookAt);

        
        SetCameraPositionAndTarget_UpVecY(m_position, m_LookAt);
    }
}

void Camera::LookOnCamera(VECTOR _target, VECTOR _LookTarget)
{

    VECTOR lookOn = VSub(_target, _LookTarget);

    VECTOR hLookOn = VGet(lookOn.x, lookOn.y, lookOn.z);

    m_LookAt = hLookOn;
    m_LookAt.y = 10.0f + _target.y;



    m_sinParam = sin(m_verticalAngle / 180.0f * DX_PI_F);
    m_cosParam = cos(m_verticalAngle / 180.0f * DX_PI_F);
    tempPosition1.x = 0.0f;
    tempPosition1.y = m_sinParam * m_Distance;
    tempPosition1.z = -m_cosParam * m_Distance;

    m_sinParam = sin(m_horizontalAngle / 180.0f * DX_PI_F);
    m_cosParam = cos(m_horizontalAngle / 180.0f * DX_PI_F);
    tempPosition2.x = m_cosParam * tempPosition1.x - m_sinParam * tempPosition1.z;
    tempPosition2.y = tempPosition1.y;
    tempPosition2.z = m_sinParam * tempPosition1.x + m_cosParam * tempPosition1.z;
    targetPositon = VAdd(m_LookAt, tempPosition2);

    m_position = VAdd(tempPosition2, m_LookAt);


    SetCameraPositionAndTarget_UpVecY(m_position, m_LookAt);

}


