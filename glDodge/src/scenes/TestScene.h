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
	class TestScene : public Scene
	{
	public:
		TestScene();
		~TestScene();

		void OnUpdate(SceneManager& sm, float deltaTime = 0) override;
		void OnRender() override;
		void OnDebugRender() override;

	private:

		//game logic
		glm::vec3 translate1;
		glm::vec3 translate2;

		
		std::unique_ptr<Cube> Cube1;
		std::unique_ptr<Cube> Cube2;
	};
}