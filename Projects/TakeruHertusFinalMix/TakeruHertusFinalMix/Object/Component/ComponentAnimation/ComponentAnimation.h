#pragma once
#include "../Base/Component.h"
#include "../ComponentModel/ComponentModel.h"

	// プレイヤーのアニメーションの再生速度
#define PLAYER_PLAY_ANIM_SPEED 0.5f;

	// プレイヤーのアニメーションのブレンド率変化速度
#define PLAYER_ANIM_BLEND_SPEED 0.1f;


/// <summary>
/// 引数指定：modelHandle
/// </summary>
class ComponentAnimation : public Component
{
private:
	std::shared_ptr<ComponentModel> m_model;


	/*ブレンドで使用するアニメーションの変数*/
	int		m_blendPlayAnim1;				// 再生しているアニメーション１のアタッチ番号( -1:何もアニメーションがアタッチされていない )
	float	m_blendAnimPlayCount1;			// 再生しているアニメーション１の再生時間
	int		m_blendPlayAnim2;				// 再生しているアニメーション２のアタッチ番号( -1:何もアニメーションがアタッチされていない )
	float	m_blendAnimPlayCount2;			// 再生しているアニメーション２の再生時間
	float	m_blendAnimBlendRate;			// 再生しているアニメーション１と２のブレンド率
	float   m_blendAnimTotalTime;			// アニメーションの総再生時間
	
	void UpdatePlayBlendAnim();


	/*通常のアニメーション変数*/
	float anim_TotalTime;
	float anim_NowTime;
	int animIndex;
	int newAnimIndex;

	void UpdatePlayAnim();

	/*アニメーションが再生フラグ*/
	bool m_isPlayingAnimation;


public:
	
	ComponentAnimation(std::shared_ptr<ComponentModel> _model);

	/// <summary>
	///	ブレンド適応：アニメーションを再生する番号をセット
	/// </summary>
	/// <param name="_PlayAnim"></param>
	void PlayBlendAnim(int _PlayAnim);

	/// <summary>
	/// アニメーションを再生する番号をセット:※実装先での初期化はNG
	/// </summary>
	/// <param name="_PlayAnim"></param>
	void PlayAnim(int _PlayAnim);

	void ResetAnimationNowTime();

	void Init() override;
	void Update() override;
	void Draw() override;
	void Final() override;

	bool IsAnimPlaying() const { return m_isPlayingAnimation; }

};

