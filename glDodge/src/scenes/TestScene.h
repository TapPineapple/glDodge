#pragma once
#include "Scene.h"

namespace game
{
	class TestScene : public Scene
	{

	public:
		void OnUpdate(SceneManager& sm, float deltaTime = 0) override;


		void OnRender() override;


		void OnDebugRender() override;

	};
}