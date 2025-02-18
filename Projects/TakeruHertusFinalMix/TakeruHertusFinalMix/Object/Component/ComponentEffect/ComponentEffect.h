#pragma once
#include "../Base/Component.h"
#include "../ComponentTransform/ComponentTransform.h"

class ComponentEffect : public Component
{
private:
	std::string filename;
	std::vector<std::vector<std::string>> Data;

	static constexpr int m_effectHandleNum = 11;
	
	VECTOR m_position[m_effectHandleNum];
	int m_effectHandle[m_effectHandleNum];
	int m_playEffectHandle[m_effectHandleNum];
	float m_effectSize[m_effectHandleNum];
	
	int m_effectTime;
	bool m_isPlayeing;

	//セクション１のエフェクトの初期化
	void Section1EffectInit();
	//セクション２のエフェクトの初期化
	void Section2EffectInit();

	void Section4EffectInit();


public:
	ComponentEffect();
	
	void Init()override;
	void Update()override;
	void Draw() override;
	void Final()override;

	void Update_Section1_Event();
	void Update_Section2_WeponSelectLeft();
	void Update_section4_WeponGetEvent();
	void Update_section4_EnemySpown();

	void Update_SavePoint();
	void Update_EnemySpown();

	/*===============================================================*/
	//セッターとゲッター
	/*===============================================================*/
	void SetStopEffect(const int _effectNumber);

	void SetEffectTime(const int& _setTime) { m_effectTime = _setTime; }

	/// <summary>
	/// ポジションのセット
	/// </summary>
	/// <param name="_pos">座標</param>
	/// <param name="_num">配列の番号</param>
	void SetPosition(const VECTOR& _pos, const int& _num) { m_position[_num] = _pos; }

	/// <summary>
	/// ポジションのゲット
	/// </summary>
	/// <param name="_num">配列の番号</param>
	/// <returns></returns>
	VECTOR GetPosition(const int& _num) const { return m_position[_num]; }

	
};

