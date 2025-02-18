#include "ComponentEffect.h"
#include "../../../CSVLib/CsvData_Reading_And_Writing_Equipment.h"

void ComponentEffect::Section1EffectInit()
{
	//セクション１の道しるべエフェクト
	m_effectHandle[0] = LoadEffekseerEffect("../Asset/3D/Effect/TutorialEffect_Section_1.efkefc", CSVLib::GetCell_float(Data, 1, 2));
	m_position[0] = VGet(CSVLib::GetCell_float(Data, 1, 3),
		CSVLib::GetCell_float(Data, 1, 4),
		CSVLib::GetCell_float(Data, 1, 5));
}

void ComponentEffect::Section2EffectInit()
{
	//セクション２の土台出現エフェクト（左）
	m_effectHandle[1] = LoadEffekseerEffect("../Asset/3D/Effect/fog/fog.efkefc", CSVLib::GetCell_float(Data, 2, 2));
	m_position[1] = VGet(-CSVLib::GetCell_float(Data, 2, 3),
		CSVLib::GetCell_float(Data, 2, 4),
		CSVLib::GetCell_float(Data, 2, 5));
	

}

void ComponentEffect::Section4EffectInit()
{
	m_effectHandle[5] = LoadEffekseerEffect("../Asset/3D/Effect/Section4Event/TutorialSection_4WeponGetEffect_1.efkefc", CSVLib::GetCell_float(Data, 3, 2));
	m_position[5] = VGet(-CSVLib::GetCell_float(Data, 3, 3),
						CSVLib::GetCell_float(Data, 3, 4),
						CSVLib::GetCell_float(Data, 3, 5));

	m_effectHandle[6] = LoadEffekseerEffect("../Asset/3D/Effect/EnemySpown/EnemySpown.efkefc", 50);
	m_position[6] = VGet(-CSVLib::GetCell_float(Data, 4, 3),
		CSVLib::GetCell_float(Data, 4, 4),
		CSVLib::GetCell_float(Data, 4, 5));

	m_effectHandle[7] = LoadEffekseerEffect("../Asset/3D/Effect/EnemySpown/EnemySpown.efkefc", 50);
	m_position[7] = VGet(-CSVLib::GetCell_float(Data, 5, 3),
		CSVLib::GetCell_float(Data, 5, 4),
		CSVLib::GetCell_float(Data, 5, 5)); m_effectHandle[7] = LoadEffekseerEffect("../Asset/3D/Effect/EnemySpown/EnemySpown.efkefc", 50);
	
	m_position[8] = VGet(-CSVLib::GetCell_float(Data, 5, 3),
		CSVLib::GetCell_float(Data, 5, 4),
		CSVLib::GetCell_float(Data, 5, 5));

	m_effectHandle[9] = LoadEffekseerEffect("../Asset/3D/Effect/SavePoint.efkefc", 25);
	m_position[9] = VGet(700.0f, 4.0f, 700.0f);

	m_effectHandle[10] = LoadEffekseerEffect("../Asset/3D/Effect/EnemySpown/EnemySpown.efkefc", 25);
	m_position[10] = VGet(700.0f, 4.0f, 700.0f);

}

ComponentEffect::ComponentEffect()
	: m_effectHandle()
	, m_playEffectHandle()
	, m_effectTime()
	, m_position()
	, m_isPlayeing(false)
{
}

void ComponentEffect::Init()
{
	//外部ファイルの読み込み
	filename = "../GameData/3DEffectResourceData.csv";
	Data = CSVLib::ReadCSV(filename);
	
	
	/*エフェクトのロード*/
	Section1EffectInit();
	
	Section2EffectInit();
	
	Section4EffectInit();


	for (int i = 0; i < m_effectHandleNum; i++)
	{
		m_playEffectHandle[i] = -1;
	}
}

void ComponentEffect::Update()
{
	
}

void ComponentEffect::Draw()
{
	DrawEffekseer3D();//エフェクトの描画
}

void ComponentEffect::Final()
{
	for (int i = 0; i < m_effectHandleNum; i++)
	{
		//エフェクトの解放
		DeleteEffekseerEffect(m_effectHandle[i]);
	}
}

void ComponentEffect::Update_Section1_Event()
{
	/*エフェクトの位置更新*/
	m_effectTime++;

	//100秒に一回再生（これは後で変更しておく）
	if (m_effectTime % 100 == 0)
	{
		//エフェクトの格納数分プレイエフェクトに格納
		m_playEffectHandle[0] = PlayEffekseer3DEffect(m_effectHandle[0]);
	}
	if (m_effectTime >= 100)
	{
		m_effectTime = 0.0f;
	}

	//再生するエフェクトの位置更新
	SetPosPlayingEffekseer3DEffect(m_playEffectHandle[0], m_position[0].x, m_position[0].y, m_position[0].z);

	UpdateEffekseer3D();//エフェクトの更新
}

void ComponentEffect::Update_Section2_WeponSelectLeft()
{
	/*エフェクトの位置更新*/
	m_effectTime++;

	//100秒に一回再生（これは後で変更しておく）
	if (m_effectTime % 100 == 0)
	{
		m_playEffectHandle[1] = PlayEffekseer3DEffect(m_effectHandle[1]);
	}
	if (m_effectTime >= 100)
	{
		m_effectTime = 0.0f;
	}
	
	//再生するエフェクトの位置更新
	SetPosPlayingEffekseer3DEffect(m_playEffectHandle[1], m_position[1].x, m_position[1].y, m_position[1].z);
	UpdateEffekseer3D();//エフェクトの更新
}

void ComponentEffect::Update_section4_WeponGetEvent()
{
	/*エフェクトの位置更新*/
	m_effectTime++;

	//100秒に一回再生（これは後で変更しておく）
	if (m_effectTime % 375 == 0)
	{
		m_playEffectHandle[5] = PlayEffekseer3DEffect(m_effectHandle[5]);
	}
	if (m_effectTime >= 375)
	{
		m_effectTime = 376.0f;
	}

	//再生するエフェクトの位置更新
	SetPosPlayingEffekseer3DEffect(m_playEffectHandle[5], m_position[5].x, m_position[5].y, m_position[5].z);
	UpdateEffekseer3D();//エフェクトの更新
}

void ComponentEffect::Update_section4_EnemySpown()
{
	/*エフェクトの位置更新*/
	m_effectTime++;

	//100秒に一回再生（これは後で変更しておく）
	if (m_effectTime % 240 == 0)
	{
		m_playEffectHandle[6] = PlayEffekseer3DEffect(m_effectHandle[6]);
		m_playEffectHandle[7] = PlayEffekseer3DEffect(m_effectHandle[7]);
		m_playEffectHandle[8] = PlayEffekseer3DEffect(m_effectHandle[8]);

	}
	if (m_effectTime >= 240)
	{
		m_effectTime = 240.0f;
	}

	//再生するエフェクトの位置更新
	SetPosPlayingEffekseer3DEffect(m_playEffectHandle[6], m_position[6].x, m_position[6].y, m_position[6].z);
	SetPosPlayingEffekseer3DEffect(m_playEffectHandle[7], m_position[7].x, m_position[7].y, m_position[7].z);
	SetPosPlayingEffekseer3DEffect(m_playEffectHandle[8], m_position[8].x, m_position[8].y, m_position[8].z);
	
	UpdateEffekseer3D();//エフェクトの更新
}

void ComponentEffect::Update_SavePoint()
{
	/*エフェクトの位置更新*/
	m_effectTime++;

	//100秒に一回再生（これは後で変更しておく）
	if (m_effectTime % 151 == 0)
	{
		m_playEffectHandle[9] = PlayEffekseer3DEffect(m_effectHandle[9]);
	}
	if (m_effectTime >= 151)
	{
		m_effectTime = 0.0f;
	}

	SetPosPlayingEffekseer3DEffect(m_playEffectHandle[9], m_position[9].x, m_position[9].y, m_position[9].z);
	UpdateEffekseer3D();//エフェクトの更新

}

void ComponentEffect::Update_EnemySpown()
{
	/*エフェクトの位置更新*/
	m_effectTime++;

	//100秒に一回再生（これは後で変更しておく）
	if (m_effectTime % 151 == 0)
	{
		m_playEffectHandle[10] = PlayEffekseer3DEffect(m_effectHandle[10]);
	}
	if (m_effectTime >= 151)
	{
		m_effectTime = 0.0f;
	}

	if (m_effectTime >= 300)
	{
		StopEffekseer3DEffect(m_playEffectHandle[10]);
	}

	SetPosPlayingEffekseer3DEffect(m_playEffectHandle[10], m_position[10].x, m_position[10].y, m_position[10].z);
	UpdateEffekseer3D();//エフェクトの更新
}

void ComponentEffect::SetStopEffect(const int _effectNumber)
{
	StopEffekseer3DEffect(m_playEffectHandle[_effectNumber]);
}