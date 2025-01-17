#pragma once
#include <map>
#include <string>

class AnimationLib
{
public:
	bool UpdateAnim(int _modelHandle, int _attachNo, float _startTime);

	void ChangeAnim(int _modelHandle, int _animIndex, float _animSpeed);


	std::map<std::string, int> m_animIdx;
	int m_animCurrentNo;
	int m_animPrevNo;
	float m_animBlendRate;

	int m_animNowIdx;
	int m_animPrevIdx;

	float m_animSpeed;
	bool m_animIsFinish;

};