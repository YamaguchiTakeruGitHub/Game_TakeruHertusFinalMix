#include "ComponentAnimation.h"

void ComponentAnimation::UpdatePlayBlendAnim()
{
	// ブレンド率が１以下の場合は１に近づける
	if (m_blendAnimBlendRate < 1.0f)
	{
		m_blendAnimBlendRate += PLAYER_ANIM_BLEND_SPEED;
		if (m_blendAnimBlendRate > 1.0f)
		{
			m_blendAnimBlendRate = 1.0f;
		}
	}

	// 再生しているアニメーション１の処理
	if (m_blendPlayAnim1 != -1)
	{
		// アニメーションの総時間を取得
		m_blendAnimTotalTime = MV1GetAttachAnimTotalTime(m_model->modelHandle, m_blendPlayAnim1);

		// 再生時間を進める
		m_blendAnimPlayCount1 += PLAYER_PLAY_ANIM_SPEED;

		// 再生時間が総時間に到達していたら再生時間をループさせる
		if (m_blendAnimPlayCount1 >= m_blendAnimTotalTime)
		{
			m_blendAnimPlayCount1 = fmod(m_blendAnimPlayCount1, m_blendAnimTotalTime);
		}

		// 変更した再生時間をモデルに反映させる
		MV1SetAttachAnimTime(m_model->modelHandle, m_blendPlayAnim1, m_blendAnimPlayCount1);

		// アニメーション１のモデルに対する反映率をセット
		MV1SetAttachAnimBlendRate(m_model->modelHandle, m_blendPlayAnim1, m_blendAnimBlendRate);
	}

	// 再生しているアニメーション２の処理
	if (m_blendPlayAnim2 != -1)
	{
		// アニメーションの総時間を取得
		m_blendAnimTotalTime = MV1GetAttachAnimTotalTime(m_model->modelHandle, m_blendPlayAnim2);

		// 再生時間を進める
		m_blendAnimPlayCount2 += PLAYER_PLAY_ANIM_SPEED;

		// 再生時間が総時間に到達していたら再生時間をループさせる
		if (m_blendAnimPlayCount2 > m_blendAnimTotalTime)
		{
			m_blendAnimPlayCount2 = fmod(m_blendAnimPlayCount2, m_blendAnimTotalTime);
		}

		// 変更した再生時間をモデルに反映させる
		MV1SetAttachAnimTime(m_model->modelHandle, m_blendPlayAnim2, m_blendAnimPlayCount2);

		// アニメーション２のモデルに対する反映率をセット
		MV1SetAttachAnimBlendRate(m_model->modelHandle, m_blendPlayAnim2, 1.0f - m_blendAnimBlendRate);
	}
}

void ComponentAnimation::UpdatePlayAnim()
{
	
	//アニメーションのインデックスについて、MV1Attachanimは中で加算される仕組みを持っているがために、
	//実際にアニメーションを実行画面で見るとぐちゃぐちゃになったり、吹っ飛んで行ったりする
	//これを防ぐために、アニメーションをタイミングででタッチしせねばならない
	if (newAnimIndex != animIndex)
	{
		animIndex = newAnimIndex;
		anim_NowTime = 0.0f;
	}

	anim_NowTime += PLAYER_PLAY_ANIM_SPEED;

	MV1SetAttachAnimTime(m_model->modelHandle, animIndex, anim_NowTime);

	m_isPlayingAnimation = true;

	if (anim_NowTime >= MV1GetAttachAnimTotalTime(m_model->modelHandle, animIndex))
	{
		anim_NowTime = 0.0f;
		m_isPlayingAnimation = false;
	}

}

ComponentAnimation::ComponentAnimation(std::shared_ptr<ComponentModel> _model)
	: m_model(_model)

	/*ブレンドアニメーション*/
	, m_blendPlayAnim1(-1)
	, m_blendAnimPlayCount1(0.0f)
	, m_blendPlayAnim2(-1)
	, m_blendAnimPlayCount2(0.0f)
	, m_blendAnimBlendRate(0.0f)
	, m_blendAnimTotalTime(0.0f)

	/*通常アニメーション*/
	, animIndex(-1)
	, newAnimIndex(-1)

	, anim_TotalTime(0.0f)
	, anim_NowTime(0.0f)
{
}

void ComponentAnimation::PlayBlendAnim(int _PlayBlendAnim)
{
	// 再生中のモーション２が有効だったらデタッチする
	if (m_blendPlayAnim2 != -1)
	{
		m_blendPlayAnim2 = -1;
		MV1DetachAnim(m_model->modelHandle, m_blendPlayAnim2);

	}

	// 今まで再生中のモーション１だったものの情報を２に移動する
	m_blendPlayAnim2 = m_blendPlayAnim1;
	m_blendAnimPlayCount2 = m_blendAnimPlayCount1;

	// 新たに指定のモーションをモデルにアタッチして、アタッチ番号を保存する
	m_blendPlayAnim1 = MV1AttachAnim(m_model->modelHandle, _PlayBlendAnim);
	m_blendAnimPlayCount1 = 0.0f;

	// ブレンド率は再生中のモーション２が有効ではない場合は１．０ｆ( 再生中のモーション１が１００％の状態 )にする
	m_blendAnimBlendRate = m_blendPlayAnim2 == -1 ? 1.0f : 0.0f;
}

void ComponentAnimation::PlayAnim(int _PlayAnim)
{
	
	animIndex = MV1DetachAnim(m_model->modelHandle, animIndex);
	newAnimIndex = MV1AttachAnim(m_model->modelHandle, _PlayAnim);
}

void ComponentAnimation::ResetAnimationNowTime()
{
	anim_NowTime = 0;
}

void ComponentAnimation::Init()
{
	/*ブレンドアニメーション*/
	m_blendPlayAnim1 = -1;
	m_blendAnimPlayCount1 = 0.0f;
	m_blendPlayAnim2 = -1;
	m_blendAnimPlayCount2 = 0.0f;
	m_blendAnimBlendRate = 1.0f;
	m_blendAnimTotalTime = 0.0f;

	/*通常アニメーション*/
	animIndex = -1;
	newAnimIndex = -1;

	anim_TotalTime = 0.0f;
	anim_NowTime = 0.0f;

	/*アニメーション再生のフラグ*/
	m_isPlayingAnimation = false;
}

void ComponentAnimation::Update()
{

	UpdatePlayAnim();

	//ブレンドアニメーションの更新処理
	UpdatePlayBlendAnim();
	
}

void ComponentAnimation::Draw()
{
#ifdef _DEBUG
	DrawFormatString(0, 160, 0xffffff, "animCount1:%f, animCoune2:%f", m_blendAnimPlayCount1, m_blendAnimPlayCount2);
	DrawFormatString(0, 180, 0xffffff, "animTotalTime:%f", m_blendAnimTotalTime);
	DrawFormatString(0, 200, 0xffffff, "animBlendRate:%f", m_blendAnimBlendRate);
	DrawFormatString(0, 220, 0xffffff, "attachanimNum:%d", MV1GetAnimNum(m_model->modelHandle));
	
#endif // _DEBUG


}

void ComponentAnimation::Final()
{
}
