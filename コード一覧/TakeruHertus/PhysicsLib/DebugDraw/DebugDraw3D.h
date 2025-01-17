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
	/// 3D���C���̃f�o�b�N�\��
	/// </summary>
	/// <param name="_start">���̊J�n�_</param>
	/// <param name="_end">���̏I�_</param>
	/// <param name="_color">�f�o�b�N�\���̐F</param>
	static void DrawLine3D(const VECTOR& _start, const VECTOR& _end, int _color);

	/// <summary>
	/// ���̂̃f�o�b�N�\��
	/// </summary>
	/// <param name="_center">:�|�W�V����</param>
	/// <param name="_radius">�F���a</param>
	/// <param name="color">�F�f�o�b�N�\���̐F</param>
	/// <param name="alpha">�F�����x</param>
	/// <param name="isWire">�F���C���[�\�������邩�ۂ�</param>
	static void DrawSphere(const VECTOR& _center, float _radius, int _color, float _alpha = 1.0f, bool _isWire = true);

	/// <summary>
	/// �J�v�Z���̃f�o�b�N�\��
	/// </summary>
	/// <param name="_center">�F�|�W�V����</param>
	/// <param name="_start">�F�J�v�Z���̓�</param>
	/// <param name="_end">�F�J�v�Z���̑���</param>
	/// <param name="_size">�F�J�v�Z���̏㉺�̒���</param>
	/// <param name="_radius">�F�J�v�Z���̔��a</param>
	/// <param name="_color">�F�F</param>
	/// <param name="_alpha">�F�����x</param>
	/// <param name="_isWire">�F���C���[��\�����邩�ۂ�</param>
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

