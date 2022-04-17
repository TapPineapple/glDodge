#pragma once
#include <memory.h>
#include <random>
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
	class MainGame : public Scene
	{
	public:
		MainGame();
		~MainGame();

		void OnUpdate(SceneManager& sm, float deltaTime = 0) override;
		void OnRender() override;
		void OnDebugRender() override;

	private:
		const int c_CubeCount = 100;
		const float c_FloorSize = 50.0f;
		 

		glm::vec4 m_CubeColor;

		std::unique_ptr<Cube> testCube;
		glm::vec3 translate1;

		std::vector<std::unique_ptr<Cube>> m_floor; 
		std::vector<std::unique_ptr<Cube>> m_cubes;
		int m_drawCount;
		float m_SceneSpeed = 30.0f;
		float m_SceneTranslate;
	};
}