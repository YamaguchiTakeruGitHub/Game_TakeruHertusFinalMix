#include "SkyDome.h"

SkyDome::SkyDome()
	: modelHandle(-1)
	, position(VGet(0,0,0))
	, m_angle(0.0f)
{
}

SkyDome::~SkyDome()
{
	MV1DeleteModel(modelHandle);
}

void SkyDome::Init()
{
	modelHandle = MV1LoadModel("../Asset/3D/SkyDome/Skydome.mv1");
	position = VGet(0, 0, 0);
	m_angle = 0.0f;
}

void SkyDome::Update()
{
	if (m_angle >= 0.0f)
	{
		m_angle++;
	}
	else
	{
		m_angle = 0;
	}


	MV1SetPosition(modelHandle, position);
	MV1SetScale(modelHandle, VGet(1.2f, 1.2f, 1.2f));
	MV1SetRotationXYZ(modelHandle, VGet(0, m_angle / DX_PI_F * 2, 0));
}

void SkyDome::Draw()
{
	MV1DrawModel(modelHandle);
}

void SkyDome::Final()
{
	MV1DeleteModel(modelHandle);
}
