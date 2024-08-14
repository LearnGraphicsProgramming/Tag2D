#ifndef ENTITY_H
#define ENTITY_H

#include "BaseEntity.h"
#include "Window.h"
#include <vector>
#include <memory>

namespace Tag2D
{
	class Entity : BaseEntity
	{
	public:
		Entity(std::shared_ptr<Window> window);
		~Entity();

		void OnStart() override;
		void OnUpdate() override;
		void OnClose() override;

		std::vector<float> m_Vertices;

	private:
		unsigned int m_VertexBufferObject;
		unsigned int m_VertexArrayObject;
	};
}

#endif // ENTITY_H