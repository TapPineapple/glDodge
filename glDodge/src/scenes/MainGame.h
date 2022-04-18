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
		const float m_ScoreRate = 10.0f;
		const float	c_Acceleration = 0.1f;
		const float c_LevelTransportSpeed = 10.0f;
		 
		float m_Score;

		glm::vec4 m_CubeColor;

		std::vector<std::unique_ptr<Cube>> m_floor; 
		std::vector<std::unique_ptr<Cube>> m_cubes;

		std::unique_ptr<Plane> m_background;

		int m_drawCount;
		float m_SceneSpeed;
		float m_Acceleration;
		float m_MaxHozizontalSpeed;
		float m_SceneTranslate;
	};
}