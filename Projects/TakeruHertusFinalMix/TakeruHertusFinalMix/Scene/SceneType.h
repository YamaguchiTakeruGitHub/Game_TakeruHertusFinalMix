#pragma once

/// <summary>
/// シーンタイプ
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