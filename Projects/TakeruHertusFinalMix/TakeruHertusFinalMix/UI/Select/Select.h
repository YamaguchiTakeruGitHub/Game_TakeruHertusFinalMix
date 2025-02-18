#pragma once
class Select
{
public:
	Select();
	~Select();

	void Init();

	/// <summary>
	/// 項目を上に移動
	/// </summary>
	/// <param name="_nowSelect">現在の選択</param>
	/// <param name="_enum">項目の数</param>
	/// <param name="isUpButton">上ボタンのフラグ</param>
	void UpSelect(int& _nowSelect, int _enum, bool isUpButton);
	
	/// <summary>
	///	項目を下に移動
	/// </summary>
	/// <param name="_nowSelect">現在の選択</param>
	/// <param name="_enum">項目の数</param>
	/// <param name="isDownButton">下ボタンのフラグ</param>
	void DownSelect(int& _nowSelect, int _enum, bool isDownButton);

	/// <summary>
	///	項目を左に移動
	/// </summary>
	/// <param name="_nowSelect">現在の選択</param>
	/// <param name="_enum">項目の数</param>
	/// <param name="isDownButton">左ボタンのフラグ</param>
	void LeftSelect(int& _nowSelect, int _enum, bool isLeftButton);

	/// <summary>
	///	項目を右に移動
	/// </summary>
	/// <param name="_nowSelect">現在の選択</param>
	/// <param name="_enum">項目の数</param>
	/// <param name="isDownButton">右ボタンのフラグ</param>
	void RightSelect(int& _nowSelect, int _enum, bool isRightButton);



private:
	
	bool m_isUpButtonPressed;
	bool m_isDownButtonPressed;

	int m_pushNow;

};

