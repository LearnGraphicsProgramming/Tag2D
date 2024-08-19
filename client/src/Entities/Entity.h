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
	};
}

#endif // ENTITY_H