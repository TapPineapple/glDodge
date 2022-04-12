#pragma once
#include <iostream>

namespace game
{
	class SceneManager;

	class Scene
	{
	public:
		Scene() {}
		virtual ~Scene() {}

		virtual void OnUpdate(SceneManager& sm, float deltaTime = 0) {}
		virtual void OnRender() {}
		virtual void OnDebugRender() {}
	};

}