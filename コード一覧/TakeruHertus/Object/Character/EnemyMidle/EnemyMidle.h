#pragma once
#include "../../../PhysicsLib/PhysicsLib.h"
#include <DxLib.h>
#include <string> 

class EnemyMidle : public Collidable
{
public:
	EnemyMidle();
	~EnemyMidle();

	void Init(std::shared_ptr<Physics> _physics);
	void Final(std::shared_ptr<Physics> _physics);
	void Update(std::shared_ptr<Physics> _physics);
	void Draw(std::shared_ptr<Physics> _physics);

	void OnCollide(const std::shared_ptr<Collidable>& _colider);


	void SetPosition(const VECTOR& _position) { m_righdbody.SetPosition(_position); }
	VECTOR GetPosition() const { return  m_righdbody.GetPosition(); }


private:
	int modelHandle;


};

