#pragma once

/// <summary>
/// �V�[���^�C�v
/// </summary>
enum class SceneType
{
	Title,
	Game,
	Result,
	Clear,
	Loading,

#ifdef _DEBUG
	Debug,
#endif // _DEBUG

};