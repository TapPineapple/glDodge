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
	class GameOver : public Scene
	{
	public:
		GameOver();
		~GameOver();

		void OnUpdate(SceneManager& sm, float deltaTime = 0) override;
		void OnRender() override;
		void OnDebugRender() override;

	private:

		//game logic
		std::unique_ptr<Plane> gameOverbg;
		std::unique_ptr<Text> scoreText;
		std::unique_ptr<Text> leaderboardText;

		std::vector<std::unique_ptr<Text>> lbPlaces;

	};
}