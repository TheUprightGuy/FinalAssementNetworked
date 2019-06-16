#ifndef __AI_H__
#define __AI_H__

#include "utils.h"
#include "object.h"


class CEnemy : public CObject
{
public:
	CEnemy ();
	~CEnemy ();

	void Process();

	void Seek(glm::vec3 _target, float _maxSpeed, float _maxForce);
	void Pursue(glm::vec3 _target, glm::vec3 _targetVelocity);
	void Arrive(glm::vec3 _target);
	void Wander();
private:
};


#endif
