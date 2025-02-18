#include "ComponentAnimation.h"

void ComponentAnimation::UpdatePlayBlendAnim()
{
	// �u�����h�����P�ȉ��̏ꍇ�͂P�ɋ߂Â���
	if (m_blendAnimBlendRate < 1.0f)
	{
		m_blendAnimBlendRate += PLAYER_ANIM_BLEND_SPEED;
		if (m_blendAnimBlendRate > 1.0f)
		{
			m_blendAnimBlendRate = 1.0f;
		}
	}

	// �Đ����Ă���A�j���[�V�����P�̏���
	if (m_blendPlayAnim1 != -1)
	{
		// �A�j���[�V�����̑����Ԃ��擾
		m_blendAnimTotalTime = MV1GetAttachAnimTotalTime(m_model->modelHandle, m_blendPlayAnim1);

		// �Đ����Ԃ�i�߂�
		m_blendAnimPlayCount1 += PLAYER_PLAY_ANIM_SPEED;

		// �Đ����Ԃ������Ԃɓ��B���Ă�����Đ����Ԃ����[�v������
		if (m_blendAnimPlayCount1 >= m_blendAnimTotalTime)
		{
			m_blendAnimPlayCount1 = fmod(m_blendAnimPlayCount1, m_blendAnimTotalTime);
		}

		// �ύX�����Đ����Ԃ����f���ɔ��f������
		MV1SetAttachAnimTime(m_model->modelHandle, m_blendPlayAnim1, m_blendAnimPlayCount1);

		// �A�j���[�V�����P�̃��f���ɑ΂��锽�f�����Z�b�g
		MV1SetAttachAnimBlendRate(m_model->modelHandle, m_blendPlayAnim1, m_blendAnimBlendRate);
	}

	// �Đ����Ă���A�j���[�V�����Q�̏���
	if (m_blendPlayAnim2 != -1)
	{
		// �A�j���[�V�����̑����Ԃ��擾
		m_blendAnimTotalTime = MV1GetAttachAnimTotalTime(m_model->modelHandle, m_blendPlayAnim2);

		// �Đ����Ԃ�i�߂�
		m_blendAnimPlayCount2 += PLAYER_PLAY_ANIM_SPEED;

		// �Đ����Ԃ������Ԃɓ��B���Ă�����Đ����Ԃ����[�v������
		if (m_blendAnimPlayCount2 > m_blendAnimTotalTime)
		{
			m_blendAnimPlayCount2 = fmod(m_blendAnimPlayCount2, m_blendAnimTotalTime);
		}

		// �ύX�����Đ����Ԃ����f���ɔ��f������
		MV1SetAttachAnimTime(m_model->modelHandle, m_blendPlayAnim2, m_blendAnimPlayCount2);

		// �A�j���[�V�����Q�̃��f���ɑ΂��锽�f�����Z�b�g
		MV1SetAttachAnimBlendRate(m_model->modelHandle, m_blendPlayAnim2, 1.0f - m_blendAnimBlendRate);
	}
}

void ComponentAnimation::UpdatePlayAnim()
{
	
	//�A�j���[�V�����̃C���f�b�N�X�ɂ��āAMV1Attachanim�͒��ŉ��Z�����d�g�݂������Ă��邪���߂ɁA
	//���ۂɃA�j���[�V���������s��ʂŌ���Ƃ����Ⴎ����ɂȂ�����A�������ōs�����肷��
	//�����h�����߂ɁA�A�j���[�V�������^�C�~���O�łŃ^�b�`�����˂΂Ȃ�Ȃ�
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

	/*�u�����h�A�j���[�V����*/
	, m_blendPlayAnim1(-1)
	, m_blendAnimPlayCount1(0.0f)
	, m_blendPlayAnim2(-1)
	, m_blendAnimPlayCount2(0.0f)
	, m_blendAnimBlendRate(0.0f)
	, m_blendAnimTotalTime(0.0f)

	/*�ʏ�A�j���[�V����*/
	, animIndex(-1)
	, newAnimIndex(-1)

	, anim_TotalTime(0.0f)
	, anim_NowTime(0.0f)
{
}

void ComponentAnimation::PlayBlendAnim(int _PlayBlendAnim)
{
	// �Đ����̃��[�V�����Q���L����������f�^�b�`����
	if (m_blendPlayAnim2 != -1)
	{
		m_blendPlayAnim2 = -1;
		MV1DetachAnim(m_model->modelHandle, m_blendPlayAnim2);

	}

	// ���܂ōĐ����̃��[�V�����P���������̂̏����Q�Ɉړ�����
	m_blendPlayAnim2 = m_blendPlayAnim1;
	m_blendAnimPlayCount2 = m_blendAnimPlayCount1;

	// �V���Ɏw��̃��[�V���������f���ɃA�^�b�`���āA�A�^�b�`�ԍ���ۑ�����
	m_blendPlayAnim1 = MV1AttachAnim(m_model->modelHandle, _PlayBlendAnim);
	m_blendAnimPlayCount1 = 0.0f;

	// �u�����h���͍Đ����̃��[�V�����Q���L���ł͂Ȃ��ꍇ�͂P�D�O��( �Đ����̃��[�V�����P���P�O�O���̏�� )�ɂ���
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
	/*�u�����h�A�j���[�V����*/
	m_blendPlayAnim1 = -1;
	m_blendAnimPlayCount1 = 0.0f;
	m_blendPlayAnim2 = -1;
	m_blendAnimPlayCount2 = 0.0f;
	m_blendAnimBlendRate = 1.0f;
	m_blendAnimTotalTime = 0.0f;

	/*�ʏ�A�j���[�V����*/
	animIndex = -1;
	newAnimIndex = -1;

	anim_TotalTime = 0.0f;
	anim_NowTime = 0.0f;

	/*�A�j���[�V�����Đ��̃t���O*/
	m_isPlayingAnimation = false;
}

void ComponentAnimation::Update()
{

	UpdatePlayAnim();

	//�u�����h�A�j���[�V�����̍X�V����
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
