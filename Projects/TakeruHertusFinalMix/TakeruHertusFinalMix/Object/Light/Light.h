#pragma once
#include "../Entity/Entity.h"

class Light : public Entity
{
private:
	std::shared_ptr<ComponentDirectionLight> m_directionLight;
	std::shared_ptr<ComponentTransform> m_transform;
	const char* m_tag;

public:
	Light();

	void Init();
	void Update();
	void Draw();
	void Final();
	
	/*===============================================================*/
	//セッターとゲッター
	/*===============================================================*/

	void SetTag(const char* _tag) { m_tag = _tag; }
	const char* GetTag() const { return m_tag; }

	void SetPosition(const VECTOR& _pos) { m_transform->position; }
	VECTOR GetPosition() const { return m_transform->position; }


};

