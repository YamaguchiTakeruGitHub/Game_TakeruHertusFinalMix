#pragma once
#include "../Base/Component.h"
#include "../ComponentModel/ComponentModel.h"

	// �v���C���[�̃A�j���[�V�����̍Đ����x
#define PLAYER_PLAY_ANIM_SPEED 0.5f;

	// �v���C���[�̃A�j���[�V�����̃u�����h���ω����x
#define PLAYER_ANIM_BLEND_SPEED 0.1f;


/// <summary>
/// �����w��FmodelHandle
/// </summary>
class ComponentAnimation : public Component
{
private:
	std::shared_ptr<ComponentModel> m_model;


	/*�u�����h�Ŏg�p����A�j���[�V�����̕ϐ�*/
	int		m_blendPlayAnim1;				// �Đ����Ă���A�j���[�V�����P�̃A�^�b�`�ԍ�( -1:�����A�j���[�V�������A�^�b�`����Ă��Ȃ� )
	float	m_blendAnimPlayCount1;			// �Đ����Ă���A�j���[�V�����P�̍Đ�����
	int		m_blendPlayAnim2;				// �Đ����Ă���A�j���[�V�����Q�̃A�^�b�`�ԍ�( -1:�����A�j���[�V�������A�^�b�`����Ă��Ȃ� )
	float	m_blendAnimPlayCount2;			// �Đ����Ă���A�j���[�V�����Q�̍Đ�����
	float	m_blendAnimBlendRate;			// �Đ����Ă���A�j���[�V�����P�ƂQ�̃u�����h��
	float   m_blendAnimTotalTime;			// �A�j���[�V�����̑��Đ�����
	
	void UpdatePlayBlendAnim();


	/*�ʏ�̃A�j���[�V�����ϐ�*/
	float anim_TotalTime;
	float anim_NowTime;
	int animIndex;
	int newAnimIndex;

	void UpdatePlayAnim();

	/*�A�j���[�V�������Đ��t���O*/
	bool m_isPlayingAnimation;


public:
	
	ComponentAnimation(std::shared_ptr<ComponentModel> _model);

	/// <summary>
	///	�u�����h�K���F�A�j���[�V�������Đ�����ԍ����Z�b�g
	/// </summary>
	/// <param name="_PlayAnim"></param>
	void PlayBlendAnim(int _PlayAnim);

	/// <summary>
	/// �A�j���[�V�������Đ�����ԍ����Z�b�g:��������ł̏�������NG
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

