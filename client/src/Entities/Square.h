#ifndef SQUARE_ENTITY_H
#define SQUARE_ENTITY_H

#include "Entities/BaseEntity.h"

namespace Tag2D
{
	class Square : public BaseEntity
	{
	public:
		Square();
		~Square();
	
	private:
		void OnStart() override;
		void OnUpdate() override;
		void OnClose() override;
	};
}


#endif // SQUARE_ENTITY_H