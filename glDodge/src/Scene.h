#pragma once
#include <iostream>
#include "EntHandle.h"

namespace game
{
	class SceneManager;

	class Scene
	{
	public:
		Scene() {}
		virtual ~Scene() {}

		virtual void OnUpdate(SceneManager& sm, float deltaTime) {}
		virtual void OnRender() {}
		virtual void OnDebugRender() {}

	};

}