#include "SceneManager.h"

namespace game
{
	Scene*& game::SceneManager::CreateScene(const std::string& name)
	{
		for (auto index : m_Scenes)
		{
			if (index.first.compare(name))
			{
				m_CurrentScene = index.second();
				return m_CurrentScene;
			}
		}
		std::cout << "[SceneManager Error] Couldn't find specified scene!\n";
		_ASSERT(false);
		return m_CurrentScene;
	}

	Scene*& game::SceneManager::GetCurrent() const
	{
		return m_CurrentScene;
	}
}