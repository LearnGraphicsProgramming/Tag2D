#include "Entity.h"

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include "Logger.h"

namespace Tag2D
{
	Entity::Entity()
	{}

	Entity::~Entity() {}

	void Entity::OnStart() {}

	void Entity::OnUpdate()
	{

	}

	void Entity::OnClose()
	{
		log_info("Entity::OnClose");
	}
}
