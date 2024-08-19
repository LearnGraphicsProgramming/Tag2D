#ifndef BASE_ENTITY_H
#define BASE_ENTITY_H

#include "ApplicationEvents.h"

#include <memory>
#include <unordered_map>
#include <string>

namespace Tag2D
{
	class Application;

	class BaseEntity
	{
	public:
		virtual ~BaseEntity();

		void SetEntityClassName(const std::string& name);

		void SetVertices(const std::initializer_list<float>& initializer_list);
		void ToString() const;

	protected:
		BaseEntity();
		
		virtual void OnStart() = 0;
		virtual void OnUpdate() = 0;
		virtual void OnClose() = 0;

	private:
		void BindOpenGLBuffer();
		void OnUpdate_Internal();

	protected:
		std::string m_EntityName;

	private:
		uint8_t m_OnStartCallbackID;
		uint8_t m_OnUpdateCallbackID;
		uint8_t m_OnCloseCallbackID;
		std::unordered_map<ApplicationEventType, int> m_CallbackIDs;

		unsigned int m_VertexBufferObject;
		unsigned int m_VertexArrayObject;
		std::vector<float> m_Vertices;
		int m_VerticesNum;

		bool m_EntityHasNoVerticesMessageSent;
	};
}

#endif // BASE_ENTITY_H