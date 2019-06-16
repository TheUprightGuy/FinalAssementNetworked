#include "bullet.h"

CBullet::CBullet(GLuint _program, glm::vec3 _placement, glm::vec3 _direction)
	: CObject::CObject(PHONGLIGHTING, "Resources/Rayman.jpg", MESH_SPHERE),
	m_direction(_direction)
{
	CObject::Scale(glm::vec3(1.0, 1.0, 1.0));
	CObject::Translate(_placement);
}

void CBullet::Process()
{
	CObject::Translate(CObject::GetPos() + (m_direction * 2.0f));
}
