#include "AnimationLib.h"
#include <DxLib.h>

bool AnimationLib::UpdateAnim(int _modelHandle, int _attachNo, float _startTime)
{
	if (_attachNo == -1) return false;

	float nowFrame = MV1GetAttachAnimTime(_modelHandle, _attachNo);

	float totalAnimFrame = MV1GetAttachAnimTotalTime(_modelHandle, _attachNo);

	bool isLoop = false;

	while (totalAnimFrame <= nowFrame)
	{
		nowFrame -= totalAnimFrame;
		nowFrame += _startTime;
		isLoop = true;
	}

	MV1SetAttachAnimTime(_modelHandle, _attachNo, nowFrame);

	return isLoop;
}

void AnimationLib::ChangeAnim(int _modelHandle, int _animIndex, float _animSpeed)
{
	if (m_animPrevNo != -1)
	{
		MV1DetachAnim(_modelHandle, m_animPrevNo);
	}

	m_animPrevIdx = m_animNowIdx;
	m_animNowIdx = _animIndex;

	m_animPrevNo = m_animCurrentNo;

	m_animCurrentNo = MV1AttachAnim(_modelHandle, _animIndex);

	m_animBlendRate = 0.0f;

	m_animSpeed = _animSpeed;
}
