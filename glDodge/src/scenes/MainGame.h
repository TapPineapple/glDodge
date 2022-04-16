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
	class MainGame : public Scene
	{
	public:
		MainGame();
		~MainGame();

		void OnUpdate(SceneManager& sm, float deltaTime = 0) override;
		void OnRender() override;
		void OnDebugRender() override;

	private:
		std::unique_ptr<Cube> floor1;
		std::unique_ptr<Cube> floor2;
		std::unique_ptr<Cube> floor3;
		std::vector<std::unique_ptr<Cube>> floor; //2d vector
		glm::vec3 translate1;

		int m_drawCount;
		float m_SceneTranslate;

	};
}