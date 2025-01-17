#pragma once
#include <DxLib.h>
#include <vector>

class MapEventOne
{
public:
	MapEventOne();
	~MapEventOne();

	void Init();
	void Update(VECTOR _startpos, VECTOR _endpos, float _radius);
	void Draw();
	void Final();

private:

	int modelHandle;
	VECTOR position;
	float angle;


};



