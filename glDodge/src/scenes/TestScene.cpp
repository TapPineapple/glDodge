#include "TestScene.h"
#include "gl/glew.h"

namespace game
{

	TestScene::TestScene()
	{

	}

	TestScene::~TestScene()
	{

	}

	void TestScene::OnUpdate(SceneManager& sm, float deltaTime /*= 0*/)
	{
		glClearColor(0.3f, 0.5f, 0.0f, 1.0f);
	}

	void TestScene::OnRender()
	{

	}

	void TestScene::OnDebugRender()
	{
	}
}