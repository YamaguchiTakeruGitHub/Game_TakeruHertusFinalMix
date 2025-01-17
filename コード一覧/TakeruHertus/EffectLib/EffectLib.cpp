#include "EffectLib.h"

EffectLib::EffectLib(const char* _effectName)
	: effect()
{
	effect.handle = LoadEffekseerEffect(_effectName, 1.0f);
	effect.playHandle = -1;
	effect.position = VGet(0, 0, 0);
	effect.time = 0;
}

EffectLib::~EffectLib()
{
	DeleteEffekseerEffect(effect.handle);
}

void EffectLib::Init(const char* _effectName)
{
	effect.handle = LoadEffekseerEffect(_effectName, 1.0f);
	effect.playHandle = -1;
	effect.position = VGet(0, 0, 0);
	effect.time = 0;
}

void EffectLib::PlayEffectLib()
{
	effect.playHandle = PlayEffekseer3DEffect(effect.handle);
}

void EffectLib::Update(VECTOR _newPos)
{
	if (effect.time % 60 == 0)
	{
		effect.position.x = 0.0f;
	}
	effect.position = _newPos;

	SetPosPlayingEffekseer3DEffect(effect.playHandle, effect.position.x, effect.position.y, effect.position.z);
	effect.position.x += 0.2f;

	UpdateEffekseer3D();

	effect.time++;
}

void EffectLib::Draw()
{
	DrawEffekseer3D();
}

void EffectLib::Final()
{
	DeleteEffekseerEffect(effect.handle);
}
