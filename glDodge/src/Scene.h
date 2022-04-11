#pragma once
#include <iostream>

namespace game
{
	class Scene
	{
	public:
		
		virtual ~Scene() {}

		virtual void OnRender() {}
		virtual void OnUpdate() {}
		virtual void OnDebugRender() {}
	private:
		SceneManager m_SceneManager;
	};

}