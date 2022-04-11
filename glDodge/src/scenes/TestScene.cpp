#include "TestScene.h"
#include "gl/glew.h"

void game::TestScene::OnUpdate(SceneManager& sm, float deltaTime /*= 0*/)
{
	/*throw std::logic_error("The method or operation is not implemented.");*/
}

void game::TestScene::OnRender()
{
// 	throw std::logic_error("The method or operation is not implemented.");
	glClearColor(0.3f, 0.3f, 0.0f, 1.0f);
}

void game::TestScene::OnDebugRender()
{
// 	throw std::logic_error("The method or operation is not implemented."
}
