#pragma once
#include <iostream>

class SceneManager;

namespace game
{
	class Scene
	{
	public:
		Scene() {}
		virtual ~Scene() {}

		virtual void OnUpdate(SceneManager& sm, float deltaTime = 0) {}
		virtual void OnRender() {}
		virtual void OnDebugRender() {}
	private:
	};

}