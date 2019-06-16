#include "AI.h"
#include <cstdlib>
#include <time.h>
#include <math.h>



CEnemy::CEnemy()
	: CObject::CObject(PHONGLIGHTING, "Resources/NicCage.png", MESH_CUBE)
{
	srand(time(NULL));
}

void CEnemy::Seek(glm::vec3 _target, float _maxSpeed, float _maxForce)
{
	glm::vec3 pos = CObject::GetPos();
	glm::vec3 desired = _target - pos;
	glm::vec3 accel = glm::vec3(0.0, 0.0, 0.0); //This gets reset everytime
	static glm::vec3 velocity = glm::vec3(0.0, 0.0, 0.0); //This is a constant value. It will be happening

	float maxspeed = _maxSpeed;
	float maxforce = _maxForce;

	desired = glm::normalize(desired);
	desired *= maxspeed;

	glm::vec3 steer = desired - velocity;
	steer *= maxforce;

	accel += steer;

	velocity += accel;

	pos += velocity;

	CObject::Translate(pos);
}

void CEnemy::Pursue(glm::vec3 _target, glm::vec3 _targetVelocity)
{
	glm::vec3 targetVelocity;
	if (_targetVelocity != glm::vec3())
	{
		targetVelocity = glm::normalize(_targetVelocity);
	}
	float targetLength = glm::length(CObject::GetPos() -_target);

	if (targetLength > 10.0f)
	{
		targetLength = 10.0f; //This is because it looks kinda weird if its trying to guess that far ahead
	}
	Seek(_target + (targetVelocity * targetLength), 0.3f, 0.1f);
}

void CEnemy::Arrive(glm::vec3 _target)
{
	glm::vec3 pos = CObject::GetPos();
	glm::vec3 desired = _target - pos;

	float maxspeed = 0.5f;

	if (glm::length(desired) < 20.0f) //If less than a distance of 1.5
	{
		float setspeed = glm::length(desired)/5 * 0.1f; //Okay so this is cheating a little, but figuring the max speed is 0.2 times the max distance,
													//We can multiply the distance by 0.2 from the outer rim to create a gradual decrease in speed
		if (glm::length(desired) < 0.2f) //We will just stop it at a certain distance
		{
			Seek(_target, 0.0f, 0.1f);
		}
		Seek(_target, setspeed, 0.1f);
		
	}
	else
	{
		Seek(_target, maxspeed, 0.1f);
	}
}

void CEnemy::Wander()
{

	static glm::vec3 targetVelocity = glm::vec3(0.0f, 0.0f, 7.0f);
	targetVelocity = glm::normalize(targetVelocity);
	targetVelocity *= 7;
	glm::vec3 circleOrigin = CObject::GetPos() + targetVelocity;

	glm::vec3 TargetPos;
	
	while (true)
	{
		int radius = 3; //Circle radius
		int randomAngle = rand() % 360 + 1;
		TargetPos.x = circleOrigin.x + radius * std::cos(randomAngle);
		TargetPos.z = circleOrigin.z + radius * std::sin(randomAngle);
		TargetPos.y = 1.0f;

		//Its 37 because thats how far its searching ahead
		if ((TargetPos.x > 30.0f || TargetPos.x < -30.0f) || (TargetPos.z > 30.0f || TargetPos.z < -30.0f)) //I'm a genius pogchamp
		{
			continue;
		}
		break;
	}
	Seek(TargetPos,0.3f, 0.1f);

	targetVelocity = TargetPos - CObject::GetPos();
}

