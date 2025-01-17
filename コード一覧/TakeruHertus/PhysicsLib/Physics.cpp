#include "Physics.h"

void Physics::Entry(std::shared_ptr<Collidable> _collidable)
{
	//�w�肳�ꂽ�l���������Ĉ�ԍŌ�ȊO
	bool found = (std::find(m_collidables.begin(), m_collidables.end(), _collidable) != m_collidables.end());
	
	//�o�^����ĂȂ��ꍇ
	if (!found)
	{
		m_collidables.emplace_back(_collidable);
	}
	else//�o�^����Ă����ꍇ�̓G���[��Ԃ�
	{
		assert(0 && "�w���collidable�͓o�^�ς݂ł��B");
	}
}

void Physics::Exit(std::shared_ptr<Collidable> _collidable)
{
	bool found = (std::find(m_collidables.begin(), m_collidables.end(), _collidable) != m_collidables.end());

	//�o�^�̉���
	if (found)
	{
		m_collidables.remove(_collidable);
	}
	else//�o�^����Ă��Ȃ��ꍇ�G���[���o��
	{
		assert(0 && "�w���collidable���o�^����Ă��܂���B");
	}

}

void Physics::Update()
{
	//m_collidables�͈͎̔w��
	for (auto& item : m_collidables)
	{
		auto pos = item->m_righdbody.GetPosition();//�e�I�u�W�F�N�g����|�W�V�������擾
		auto velocity = item->m_righdbody.GetVelocity();//�e�I�u�W�F�N�g����x���V�e�B���擾

		//�d�͂�K������I�u�W�F�N�g�ɑ΂���
		if (item->m_righdbody.UseGravity())
		{
			velocity = VAdd(velocity, VGet(0, m_gravity, 0));//�x���V�e�B�ɏd�͂����Z

			//�x���V�e�BY���W���ő�d�͉����x��������Ă�����
			if (velocity.y < m_maxGravityAccel)
			{
				//����ȏ�������Ȃ��悤�ɂ���
				velocity = VGet(velocity.x, m_maxGravityAccel, velocity.z);
			}
		}

		auto nextPos = VAdd(pos, velocity);//�X�V���W���i�[

		//�x���V�e�B�ƃf�B���N�V�����������ϊ�
		item->m_righdbody.SetVelocity(velocity);

#ifdef _DEBUG
		//�e�I�u�W�F�N�g�̎�ނ��擾
		auto kind = item->m_colliderData->GetKind();
		
		//�I�u�W�F�N�g�����̂̏ꍇ
		if (kind == ColliderData::Kind::Sphere)
		{
			//���̃f�[�^�̃|�C���^���L
			std::shared_ptr<ColliderDataSphere3D> sphereData;
			//�Q�Ƃ����|�C���^��ϊ�����
			sphereData = std::dynamic_pointer_cast<ColliderDataSphere3D>(item->m_colliderData);
			//���a���擾
			float radius = sphereData.get()->radius;

			/*���̂̃f�o�b�N�\�����s��*/
			DebugDraw3D::DrawSphere(pos, radius, BeforFixInfoColor);
			DebugDraw3D::DrawLine3D(pos, nextPos, AimInfoColor);
			DebugDraw3D::DrawSphere(nextPos, radius, AimInfoColor);
		}
		//�I�u�W�F�N�g���J�v�Z���̏ꍇ
		else if (kind == ColliderData::Kind::Capsule)
		{
			//�J�v�Z���f�[�^���|�C���^���L
			std::shared_ptr<ColliderDataCapsule3D> capsuleData;
			//�Q�Ƃ��|�C���^��ϊ�����
			capsuleData = std::dynamic_pointer_cast<ColliderDataCapsule3D>(item->m_colliderData);
			
			//�J�v�Z�������擾
			VECTOR start = capsuleData.get()->start;
			//�J�v�Z���̑������擾
			VECTOR end = capsuleData.get()->end;
			//�J�v�Z���̏㉺�̒������擾
			float size = capsuleData.get()->size;
			//���a���擾
			float radius = capsuleData.get()->radius;

			/*�J�v�Z���̃f�o�b�N�\�����s��*/
			DebugDraw3D::DrawCapsule(pos, start, end, size, radius, BeforFixInfoColor);
			DebugDraw3D::DrawLine3D(pos, nextPos, AimInfoColor);
			DebugDraw3D::DrawCapsule(pos, start, end, size, radius, AimInfoColor);
		}
		else if (kind == ColliderData::Kind::OBB)
		{
			std::shared_ptr<ColliderDataOBB3D> obbData;

			obbData = std::dynamic_pointer_cast<ColliderDataOBB3D>(item->m_colliderData);

			VECTOR extents = obbData.get()->extents;
			MATRIX rotation = obbData.get()->rotation;

			//DebugDraw3D::DrawOBB(pos, axes, extents, BeforFixInfoColor)

		}



#endif // _DEBUG

		//���W���X�V����
		item->m_nextPos = nextPos;
	}

	//�Փ˂��m�F
	std::vector<OnCollideInfo> onCollideInfo = CheckColide();

	//�ʒu�̊m��
	FixPosition();

	//�����蔻���ʒm
	for (auto& item : onCollideInfo)
	{
		item.owner->OnCollide(item.colider);
	}

}

std::vector<Physics::OnCollideInfo> Physics::CheckColide() const
{
	std::vector<OnCollideInfo> onCollideInfo;
	bool doCheck = true;
	int checkCount = 0;

	while (doCheck)
	{
		doCheck = false;
		++checkCount;

		for (auto& objA : m_collidables)
		{
			for (auto& objB : m_collidables)
			{
				if (objA != objB)
				{
					if (IsCollide(objA, objB))
					{
						auto priorityA = objA->GetPriority();
						auto priorityB = objB->GetPriority();

						std::shared_ptr<Collidable> primary = objA;
						std::shared_ptr<Collidable> secondary = objB;
						if (priorityA < priorityB)
						{
							primary = objB;
							primary = objA;
						}
						FixNextPosition(primary, secondary);

						bool hasPrimaryInfo = false;
						bool hasSecondaryInfo = false;
						for (const auto& item : onCollideInfo)
						{
							if (item.owner == primary)
							{
								hasPrimaryInfo = true;
							}
							if (item.owner == secondary)
							{
								hasSecondaryInfo = true;
							}
						}
						if (!hasPrimaryInfo)
						{
							onCollideInfo.push_back({ primary, secondary });
						}
						if (!hasSecondaryInfo)
						{
							onCollideInfo.push_back({ secondary, primary });
						}

						doCheck = true;
						break;
					}
				}
			}
			if (doCheck)
			{
				break;
			}
		}

		if (checkCount > 1000 && doCheck)
		{
#ifdef _DEBUG
			printfDx("�����蔻��̌J��Ԃ��`�F�b�N����ꐔ�𒴂���\n");
#endif // _DEBUG
			break;
		}
	}
	return onCollideInfo;
}

/// <summary>
/// �w�胉�C�����I�u�W�F�N�g�ƂԂ����Ă��邩�ǂ������肵�A�Ԃ����Ă���I�u�W�F�N�g��Ԃ�
/// </summary>
/// <param name="_start"></param>
/// <param name="_end"></param>
/// <returns></returns>
std::list<std::shared_ptr<Collidable>> Physics::IsCollideLine(const VECTOR& _start, const VECTOR& _end) const
{
	std::list<std::shared_ptr<Collidable>> ret;
	for (auto& obj : m_collidables)
	{
		auto kind = obj->m_colliderData->GetKind();
		if (kind == ColliderData::Kind::Sphere)
		{
			auto circleColliderData = std::dynamic_pointer_cast<ColliderDataSphere3D>(obj->m_colliderData);
			bool isHit = (Segment_Point_MinLength(_start, _end, obj->m_righdbody.GetPosition()) < circleColliderData->radius);
			if (isHit)
			{
				ret.emplace_back(obj);
			}
		}
		//���C���ƃJ�v�Z��
		else if (kind == ColliderData::Kind::Capsule)
		{
			auto capsuleColliderData = std::dynamic_pointer_cast<ColliderDataCapsule3D>(obj->m_colliderData);
			float capsuleLength = VSize(VSub(capsuleColliderData->start, capsuleColliderData->end));
			bool isHit = (Segment_Point_MinLength(_start, _end, obj->m_righdbody.GetPosition()) < capsuleLength + capsuleColliderData->radius);
			if (isHit)
			{
				ret.emplace_back(obj);
			}
		}



	}

	return ret;
}

bool Physics::IsCollide(const std::shared_ptr<Collidable> _objA, const std::shared_ptr<Collidable> _objB) const
{
	bool isHit = false;
	auto aKind = _objA->m_colliderData->GetKind();
	auto bKind = _objB->m_colliderData->GetKind();

	if (aKind == ColliderData::Kind::Sphere && bKind == ColliderData::Kind::Sphere)
	{
		auto atob = VSub(_objB->m_nextPos, _objA->m_nextPos);
		auto atobLength = VSize(atob);

		auto objAColliderData = std::dynamic_pointer_cast<ColliderDataSphere3D>(_objA->m_colliderData);
		auto objBColliderData = std::dynamic_pointer_cast<ColliderDataSphere3D>(_objB->m_colliderData);
		isHit = (atobLength < objAColliderData->radius + objBColliderData->radius);
	}
	//�J�v�Z���ƃJ�v�Z��
	else if (aKind == ColliderData::Kind::Capsule && bKind == ColliderData::Kind::Capsule)
	{
		//auto closestPoint1, closestPoint2;
		auto objAColliderData = std::dynamic_pointer_cast<ColliderDataCapsule3D>(_objA->m_colliderData);
		auto objBColliderData = std::dynamic_pointer_cast<ColliderDataCapsule3D>(_objB->m_colliderData);
		
		//2�̍X�V��̍��W�̋��������߂�
		auto atob = VSub(_objB->m_nextPos, _objA->m_nextPos);
		auto atobLength = VSize(atob);//�x�N�g���̃T�C�Y���擾

		auto objAStart = VAdd(_objA->m_nextPos, VGet(0, objAColliderData->size, 0));
		auto objAEnd = VSub(_objA->m_nextPos, VGet(0, objAColliderData->size, 0));

		auto objBStart = VAdd(_objB->m_nextPos, VGet(0, objBColliderData->size, 0));
		auto objBEnd = VSub(_objB->m_nextPos, VGet(0, objBColliderData->size, 0));

		//2�̐��̊Ԃ̍ŋߓ_�Ԃ����߂�
		float SegmentPoint = Segment_Segment_MinLength(objAStart, objAEnd, objBStart, objBEnd);

		isHit = SegmentPoint <= (objAColliderData->radius + objBColliderData->radius);
	}
	else if (aKind == ColliderData::Kind::Capsule && bKind == ColliderData::Kind::Sphere)
	{
		auto objAColliderData = std::dynamic_pointer_cast<ColliderDataCapsule3D>(_objA->m_colliderData);
		auto objBColliderData = std::dynamic_pointer_cast<ColliderDataSphere3D>(_objB->m_colliderData);

		auto atob = VSub(_objB->m_nextPos, _objA->m_nextPos);
		auto atobLength = VSize(atob);

		auto objAStart = VAdd(_objA->m_nextPos, VGet(0, objAColliderData->size, 0));
		auto objAEnd = VSub(_objA->m_nextPos, VGet(0, objAColliderData->size, 0));

		float SegmentPoint = Segment_Point_MinLength(objAStart, objAEnd, _objB->m_nextPos);

		isHit = SegmentPoint <= (objAColliderData->radius + objBColliderData->radius);
	}
	else if (aKind == ColliderData::Kind::OBB && bKind == ColliderData::Kind::OBB)
	{
		
	}
	



	return isHit;
}

void Physics::FixNextPosition(std::shared_ptr<Collidable> _primary, std::shared_ptr<Collidable> _secondary) const
{
	auto primaryKind = _primary->m_colliderData->GetKind();
	auto secondaryKind = _secondary->m_colliderData->GetKind();

	if (primaryKind == ColliderData::Kind::Sphere && secondaryKind == ColliderData::Kind::Sphere)
	{
		VECTOR primaryToSecondary = VSub(_secondary->m_nextPos, _primary->m_nextPos);
		VECTOR primaryToSecondaryN = VNorm(primaryToSecondary);

		auto primaryColliderData = std::dynamic_pointer_cast<ColliderDataSphere3D>(_primary->m_colliderData);
		auto secondaryColliderData = std::dynamic_pointer_cast<ColliderDataSphere3D>(_secondary->m_colliderData);
		float awayDist = primaryColliderData->radius + secondaryColliderData->radius + 0.0001f;
		VECTOR primaryToNewSecndaryPos = VScale(primaryToSecondaryN, awayDist);
		VECTOR fixedPos = VAdd(_primary->m_nextPos, primaryToNewSecndaryPos);
		_secondary->m_nextPos = fixedPos;
	}
	else if (primaryKind == ColliderData::Kind::Capsule && secondaryKind == ColliderData::Kind::Capsule)
	{
		auto primaryColliderData = std::dynamic_pointer_cast<ColliderDataCapsule3D>(_primary->m_colliderData);
		auto secondaryColliderData = std::dynamic_pointer_cast<ColliderDataCapsule3D>(_secondary->m_colliderData);

		auto secondaryToPrimary = VSub(_secondary->m_nextPos, _primary->m_nextPos);
		auto secondaryToPrimaryLength = VSize(secondaryToPrimary);

		auto _primaryStart = VAdd(_primary->m_nextPos, VGet(0, primaryColliderData->size, 0));
		auto _primaryEnd = VSub(_primary->m_nextPos, VGet(0, primaryColliderData->size, 0));

		auto _secondaryStart = VAdd(_secondary->m_nextPos, VGet(0, secondaryColliderData->size, 0));
		auto _secondaryEnd = VSub(_secondary->m_nextPos, VGet(0, secondaryColliderData->size, 0));

		float SegmentPoint = Segment_Segment_MinLength(_primaryStart, _primaryEnd, _secondaryStart, _secondaryEnd);

		float overlap = (primaryColliderData->radius + secondaryColliderData->radius) - SegmentPoint;

		auto correctionDirecition = VSub(_secondaryStart, _primaryStart);
		correctionDirecition = VNorm(correctionDirecition);

		VECTOR push = VScale(correctionDirecition, overlap);
		VECTOR correctionB = VScale(push, 0.5f);
		
		
		_secondary->m_nextPos = VAdd(_secondary->m_nextPos, correctionB);

	}
	else if (primaryKind == ColliderData::Kind::Capsule && secondaryKind == ColliderData::Kind::Sphere)
	{
		auto primaryColliderData = std::dynamic_pointer_cast<ColliderDataCapsule3D>(_primary->m_colliderData);
		auto secondaryColliderData = std::dynamic_pointer_cast<ColliderDataSphere3D>(_secondary->m_colliderData);

		auto _primaryStart = VAdd(_primary->m_nextPos, VGet(0, primaryColliderData->size, 0));
		auto _primaryEnd = VSub(_primary->m_nextPos, VGet(0, primaryColliderData->size, 0));

		float segmantPoint = Segment_Point_MinLength(_primaryStart, _primaryEnd, _secondary->m_nextPos);
		float overlap = (primaryColliderData->radius + secondaryColliderData->radius) - segmantPoint;

		auto correctionDirection = VSub(_secondary->m_nextPos, _primary->m_nextPos);
		correctionDirection = VNorm(correctionDirection);

		VECTOR push = VScale(correctionDirection, overlap);
		VECTOR correntionB = VScale(push, 0.5f);

		_secondary->m_nextPos = VAdd(_secondary->m_nextPos, correntionB);


	}
	else if (primaryKind == ColliderData::Kind::OBB && secondaryKind == ColliderData::Kind::OBB)
	{
		
	}
	
	else
	{
		assert(0 && "������Ă��Ȃ������蔻��ł�");
	}


}

void Physics::FixPosition()
{
	for (auto& item : m_collidables)
	{
#ifdef _DEBUG
		DebugDraw3D::DrawLine3D(item->m_righdbody.GetPosition(), item->m_nextPos, AfterFixInfoColor);

		if (item->m_colliderData->GetKind() == ColliderData::Kind::Sphere)
		{
			auto itemCircleData = std::dynamic_pointer_cast<ColliderDataSphere3D>(item->m_colliderData);
			DebugDraw3D::DrawSphere(item->m_nextPos, itemCircleData->radius, AfterFixInfoColor);
		}
		else if (item->m_colliderData->GetKind() == ColliderData::Kind::Capsule)
		{
			auto itemCapsuleData = std::dynamic_pointer_cast<ColliderDataCapsule3D>(item->m_colliderData);
			DebugDraw3D::DrawCapsule(item->m_nextPos, itemCapsuleData->start, itemCapsuleData->end, itemCapsuleData->size, itemCapsuleData->radius, AfterFixInfoColor);
		}
#endif // _DEBUG

		VECTOR toFixedPos = VSub(item->m_nextPos, item->m_righdbody.GetPosition());
		item->m_righdbody.SetVelocity(toFixedPos);

		item->m_righdbody.SetPosition(item->m_nextPos);
	}
}


void Physics::OnCollideInfo::OnCollide()
{
	owner.get()->OnCollide(colider);
}



