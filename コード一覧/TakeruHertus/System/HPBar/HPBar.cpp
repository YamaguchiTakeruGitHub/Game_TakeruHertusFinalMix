#include "HPBar.h"
#include <DxLib.h>
#include <cmath>

HPBar::HPBar()
{
}

HPBar::~HPBar()
{
}

void HPBar::Init()
{
}

void HPBar::Update()
{
}

void HPBar::Draw()
{
	DrawBox(900, 500, 1000, 600, 0xffffff, true);
}

void HPBar::Final()
{
}





void HPBar::DrawArcHPBarWithThickness(int centerX, int centerY, int outerRadius, int innerRadius, float startAngle, float endAngle, float hpRatio, unsigned int color) {
    const int segmentCount = 100;
    const float angleRange = endAngle - startAngle;

    for (int i = 0; i < segmentCount; i++) {
        float segmentStart = startAngle + angleRange * (i / static_cast<float>(segmentCount));
        float segmentEnd = startAngle + angleRange * ((i + 1) / static_cast<float>(segmentCount));

        if (i / static_cast<float>(segmentCount) > hpRatio) break;

        int outerX1 = centerX + static_cast<int>(outerRadius * cosf(segmentStart));
        int outerY1 = centerY + static_cast<int>(outerRadius * sinf(segmentStart));
        int outerX2 = centerX + static_cast<int>(outerRadius * cosf(segmentEnd));
        int outerY2 = centerY + static_cast<int>(outerRadius * sinf(segmentEnd));

        int innerX1 = centerX + static_cast<int>(innerRadius * cosf(segmentStart));
        int innerY1 = centerY + static_cast<int>(innerRadius * sinf(segmentStart));
        int innerX2 = centerX + static_cast<int>(innerRadius * cosf(segmentEnd));
        int innerY2 = centerY + static_cast<int>(innerRadius * sinf(segmentEnd));

        // ŠO‘¤‚Æ“à‘¤‚ÌŠÔ‚ð–„‚ß‚é
        DrawQuadrangle(outerX1, outerY1, outerX2, outerY2, innerX2, innerY2, innerX1, innerY1, color, TRUE);
    }

}

void HPBar::DrawHpBarLineKness(int centerX, int centerY, int outerRadius, int innerRadius, float startAngle, float endAngle, float hpRatio, unsigned int color)
{
    
}

