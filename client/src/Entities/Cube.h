#ifndef CUBE_ENTITY_H
#define CUBE_ENTITY_H

#include "Entities/BaseEntity.h"

namespace Tag2D
{
	class Cube : public BaseEntity
	{
	public:
		Cube();
		~Cube();
	
	private:
		void OnStart() override;
		void OnUpdate() override;
		void OnClose() override;
	};
}


#endif // CUBE_ENTITY_H