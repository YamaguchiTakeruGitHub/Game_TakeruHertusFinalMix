#pragma once
#include <vector>
#include <DxLib.h>
#include <array>

class DebugDraw3D
{
public:

	static void Clear();
	static void Draw3D();


	/// <summary>
	/// 3Dラインのデバック表示
	/// </summary>
	/// <param name="_start">線の開始点</param>
	/// <param name="_end">線の終点</param>
	/// <param name="_color">デバック表示の色</param>
	static void DrawLine3D(const VECTOR& _start, const VECTOR& _end, int _color);

	/// <summary>
	/// 球体のデバック表示
	/// </summary>
	/// <param name="_center">:ポジション</param>
	/// <param name="_radius">：半径</param>
	/// <param name="color">：デバック表示の色</param>
	/// <param name="alpha">：透明度</param>
	/// <param name="isWire">：ワイヤー表示をするか否か</param>
	static void DrawSphere(const VECTOR& _center, float _radius, int _color, float _alpha = 1.0f, bool _isWire = true);

	/// <summary>
	/// カプセルのデバック表示
	/// </summary>
	/// <param name="_center">：ポジション</param>
	/// <param name="_start">：カプセルの頭</param>
	/// <param name="_end">：カプセルの足元</param>
	/// <param name="_size">：カプセルの上下の長さ</param>
	/// <param name="_radius">：カプセルの半径</param>
	/// <param name="_color">：色</param>
	/// <param name="_alpha">：透明度</param>
	/// <param name="_isWire">：ワイヤーを表示するか否か</param>
	static void DrawCapsule(const VECTOR& _center, const VECTOR& _start, const VECTOR& _end, const float _size, float _radius, int _color, float _alpha = 1.0f, bool _isWire = true);

	static void DrawOBB(const VECTOR& _center, const VECTOR& extents, const MATRIX& rotation, int _color, float _alpha = 1.0f, bool _isWire = true);

private:

	void DrawBox3DLine(VECTOR minPos, VECTOR maxPos, unsigned int color);


	std::array<VECTOR, 8> CalculateCorners(const VECTOR& _center, const VECTOR& extents, const MATRIX& _rotation) const;


	struct Line3DInfo
	{
		VECTOR start;
		VECTOR end;
		int color;
	};

	struct SphereInfo
	{
		VECTOR center;
		float radius;
		int color;
		float alpha;
		bool isWire;
	};

	struct CapsuleInfo
	{
		VECTOR center;
		VECTOR start;
		VECTOR end;
		float size;
		float radius;
		int color;
		float alpha;
		bool isWire;
	};

	struct OBBInfo
	{
		VECTOR center;
		VECTOR extents;
		MATRIX rotation;
		
		int color;
		float alpha;
		bool isWire;
	};


	static std::vector<CapsuleInfo> capsuleInfo;
	static std::vector<SphereInfo> sphereInfo;
	static std::vector<Line3DInfo> line3DInfo;
	static std::vector<OBBInfo> obbInfo;



};

