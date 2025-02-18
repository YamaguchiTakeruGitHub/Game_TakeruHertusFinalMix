#pragma once
#include "../Entity/Entity.h"

class ObjectEffecter : public Entity
{
private:
	std::shared_ptr<ComponentEffect> m_effect;

	const char* m_tag;

public:
	ObjectEffecter();
	~ObjectEffecter();

	void Init();
	void Update();
	void Draw();
	void Final();

	//======================================================================
	// セッターゲッター
	//======================================================================

	void SetTag(const char* _tag) { m_tag = _tag; }
	const char* GetTag() const { return m_tag; }

};

