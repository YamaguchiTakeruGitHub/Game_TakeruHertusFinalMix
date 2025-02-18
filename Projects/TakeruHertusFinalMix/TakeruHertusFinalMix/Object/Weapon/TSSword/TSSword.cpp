#include "TSSword.h"

TSSword::TSSword()
	: m_attachCharacterRightHandPos(VGet(0,0,0))
{
	AddComponent<ComponentTransform>();
	m_transform = GetComponent<ComponentTransform>();

	AddComponent<ComponentModel>();
	m_model = GetComponent<ComponentModel>();
}

TSSword::~TSSword()
{
}

void TSSword::Init()
{
	Entity::InitComponents();
	m_attachCharacterRightHandPos = VGet(0, 0, 0);
	m_transform->position = VGet(0, 0, 0);
	m_transform->scale = VGet(0.08, 0.08, 0.08);
	m_transform->rotation = VGet(0, 0, 0);
	m_transform->angle = 0.0f;
	m_playerAngle = 0.0f;
	m_model->LoadModel("../Asset/3D/Wepon/Sorwd/Section2Sorwd/TSSword.mv1");
}

void TSSword::Update()
{
	Entity::UpdateComponents();

	if (m_tag == "nonSelectSword")
	{
		if (m_transform->angle >= 360)
		{
			m_transform->angle = 0;
		}
		else
		{
			m_transform->angle++;
		}
		MV1SetRotationXYZ(m_model->modelHandle, VGet(0, m_transform->angle * DX_PI_F / 180.0f, 0));
		MV1SetPosition(m_model->modelHandle, m_transform->position);
	}

	if (m_tag == "nowSelectSword")
	{
		if (m_transform->angle >= 360)
		{
			m_transform->angle = 0;
		}
		else
		{
			m_transform->angle+=10.0f;
		}
		MV1SetRotationXYZ(m_model->modelHandle, VGet(0, m_transform->angle * DX_PI_F / 180.0f, 0));
		MV1SetPosition(m_model->modelHandle, m_transform->position);
	}

	if (m_tag == "playerAttachWeponTS_Sword")
	{
		MATRIX handMatrix = MV1GetFrameLocalMatrix(m_attachCharacterModel, 71);

		// 右手のボーンの行列を取得
		VECTOR handMatrixp = MV1GetFramePosition(m_attachCharacterModel, 71);

		// 武器の座標をボーンの位置に設定
		m_transform->position = VGet(handMatrixp.x - 5, handMatrixp.y + 13.0f, handMatrixp.z + 10.0f);

		MATRIX matrixangleY = MMult(handMatrix, MGetRotY(0.5));
		MATRIX matrixangleX = MMult(handMatrix, MGetRotX(0.5));


		// 武器の回転もボーンに合わせる
		//MV1SetRotationXYZ(m_model->modelHandle, VGet(handMatrix.m[0][0], handMatrix.m[1][0], handMatrix.m[2][0]));
		MV1SetRotationXYZ(m_model->modelHandle, VGet(matrixangleX.m[0][0] + handMatrix.m[0][0], matrixangleY.m[1][0] + handMatrix.m[1][0], handMatrix.m[2][0]));
		MV1SetPosition(m_model->modelHandle, m_transform->position);

		//MATRIX handMatrix = MV1GetFrameLocalMatrix(m_attachCharacterModel, 21);
		//// 武器の座標をボーンの位置に設定
		//m_transform->position = VGet(handMatrix.m[3][0], handMatrix.m[3][1], handMatrix.m[3][2]);

		//// 武器の回転もボーンに合わせる
		//MV1SetRotationXYZ(m_model->modelHandle, VGet(handMatrix.m[0][0], handMatrix.m[1][0], handMatrix.m[2][0]));
		//MV1SetPosition(m_model->modelHandle, VAdd(m_transform->position, m_attachCharacterRightHandPos));
	}

	
	MV1SetScale(m_model->modelHandle, m_transform->scale);
	}

void TSSword::Draw()
{
	Entity::DrawComponents();
}

void TSSword::Final()
{
	Entity::FinalComponents();
}

//
//MATRIX handMatrix = MV1GetFrameLocalMatrix(characterModel, handBoneIndex);
//
//// 武器の座標をボーンの位置に設定
//MV1SetPosition(weaponModel, VGet(handMatrix.m[3][0], handMatrix.m[3][1], handMatrix.m[3][2]));
//
//// 武器の回転もボーンに合わせる
//MV1SetRotationXYZ(weaponModel, VGet(handMatrix.m[0][0], handMatrix.m[1][0], handMatrix.m[2][0]));
//}