#include "ComponentModel.h"

ComponentModel::~ComponentModel()
{
	if (modelHandle != -1)
	{
		MV1DeleteModel(modelHandle);
	}
}

void ComponentModel::LoadModel(const char* _filePath)
{
	modelHandle = MV1LoadModel(_filePath);

	if (modelHandle == -1)
	{
#ifdef _DEBUG
		DrawFormatString(0, 40, 0xff0000, "ÉÇÉfÉãÇì«Ç›çûÇﬂÇ‹ÇπÇÒÇ≈ÇµÇΩÅB");
#endif // _DEBUG
	}
}

void ComponentModel::Init()
{
}

void ComponentModel::Update()
{
}

void ComponentModel::Draw()
{
	if (modelHandle != -1)
	{
		MV1DrawModel(modelHandle);
	}
}

void ComponentModel::Final()
{
	if (modelHandle != -1)
	{
		MV1DeleteModel(modelHandle);
	}
}




