#pragma once
class HPBar
{
public:
	HPBar();
	~HPBar();

	void Init();
	void Update();
	void Draw();
	void Final();

	void DrawArcHPBarWithThickness(int centerX, int centerY, int outerRadius, int innerRadius, float startAngle, float endAngle, float hpRatio, unsigned int color);

	void DrawHpBarLineKness(int centerX, int centerY, int outerRadius, int innerRadius, float startAngle, float endAngle, float hpRatio, unsigned int color);

private:

};

