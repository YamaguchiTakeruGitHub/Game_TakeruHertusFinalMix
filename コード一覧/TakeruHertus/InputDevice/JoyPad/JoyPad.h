#pragma once
#include <DxLib.h>

/// <summary>
/// パッドの各ボタンやスライダー
/// </summary>
enum PadButton
{
	//ボタン
	A = 0,
	B = 1,
	X = 2,
	Y = 3,
	LB = 4,
	RB = 5,
	BACK = 6,
	START = 7,
	STICKBL = 8,
	STICKBR = 9,

	/*十字キー*/
	CROSSKEY = 0,
	DUP = 0,			//上
	DRIGHT = 9000,			//右
	DDOWN = 18000,			//下
	DLEFT = 27000,			//左
	DNONE = true,			//何もしてない
};

/// <summary>
/// ジョイパッドクラス
/// </summary>
class JoyPad
{
public:
	JoyPad();
	~JoyPad();

	void Init();
	void Update();


	/// <summary>
	/// ジョイステック右（X軸）のゲッター
	/// </summary>
	/// <returns>pad.Rx</returns>
	float GetRightStickX() const { return pad.Rx / 32767.0f; }

	/// <summary>
	/// ジョイステック右（Y軸）のゲッター
	/// </summary>
	/// <returns>pad.Ry</returns>
	float GetRightStickY() const { return pad.Ry / 32767.0f; }

	/// <summary>
	/// ジョイステック左（X軸）のゲッター
	/// </summary>
	/// <returns>pad.X</returns>
	float GetLeftStickX() const { return pad.X / -32767.0f; }

	/// <summary>
	/// ジョイステック左（Y軸）のゲッター
	/// </summary>
	/// <returns>pad.Y</returns>
	float GetLeftStickY() const { return pad.Y / -32767.0f; }



private:
	DINPUT_JOYSTATE pad;

	int Pad1;
	int count;


public:

	/*別クラスで判定する用のフラグ(start)*/
	bool isA;
	bool isB;
	bool isX;
	bool isY;
	bool isLB;
	bool isRB;
	bool isBACK;
	bool isSTART;
	bool isSTICKBL;
	bool isSTICKBR;

	bool isDUP;
	bool isDRIGHT;
	bool isDDOWN;
	bool isDLEFT;

	/*別クラスで判定する用のフラグ(end)*/


private:

	/*押し込み瞬間の際のフラグ(start)*/
	bool pisA;
	bool pisB;
	bool pisX;
	bool pisY;
	bool pisLB;
	bool pisRB;
	bool pisBACK;
	bool pisSTART;
	bool pisSTICKL;
	bool pisSTICKR;

	bool pisDUP;
	bool pisDRIGHT;
	bool pisDDOWN;
	bool pisDLEFT;
	/*押し込み瞬間の際のフラグ(end)*/

};
