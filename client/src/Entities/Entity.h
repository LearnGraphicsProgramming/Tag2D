#ifndef ENTITY_H
#define ENTITY_H

#include "Entities/BaseEntity.h"
#include <vector>
#include <memory>

namespace Tag2D
{
	class BaseEntity;
	class Entity : public BaseEntity
	{
	public:
		Entity();
		~Entity();

		void OnStart() override;
		void OnUpdate() override;
		void OnClose() override;

		void SetVertices(const std::initializer_list<float>& initializer_list);

	private:
		unsigned int m_VertexBufferObject;
		unsigned int m_VertexArrayObject;
		std::vector<float> m_Vertices;
	};
}

#endif // ENTITY_H