#pragma once
#include "../../../PhysicsLib/PhysicsLib.h"


class EnemyDinamic : public Collidable
{
public:
	EnemyDinamic();
	~EnemyDinamic();

	void Init(std::shared_ptr<Physics> _physics);
	void Final(std::shared_ptr<Physics> _physics);
	void Update(std::shared_ptr<Physics> _physics);
	void Draw(std::shared_ptr<Physics> _physics);

	void OnCollide(const std::shared_ptr<Collidable>& _colider);

private:
	int modelHandle;
};

