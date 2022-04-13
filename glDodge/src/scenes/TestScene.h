#pragma once
#include <memory.h>
#include "Scene.h"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Texture.h"
#include "Shader.h"
#include "VertexBufferLayout.h"

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
		std::unique_ptr<VertexArray> va;
		std::unique_ptr<VertexBuffer> vb;
		std::unique_ptr<Shader> shader;
		std::unique_ptr<Texture> texture;

		float fov = 45.0f;
		glm::vec3 translate;

	};
}