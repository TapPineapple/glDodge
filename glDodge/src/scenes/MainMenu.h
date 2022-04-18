#pragma once
#include <memory.h>
#include "Scene.h"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Texture.h"
#include "Shader.h"
#include "VertexBufferLayout.h"

#include "SceneManager.h"
#include "Entity.h"

namespace game
{
	class MainMenu : public Scene
	{
	public:
		MainMenu();
		~MainMenu();

		void OnUpdate(SceneManager& sm, float deltaTime = 0) override;
		void OnRender() override;
		void OnDebugRender() override;

	private:

		//game logic
		std::unique_ptr<Plane> mm;
	};
}