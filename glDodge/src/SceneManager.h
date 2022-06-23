#pragma once
#include <functional>
#include <iostream>
#include <vector>

#include "EntHandle.h"
#include "Scene.h"

namespace game
{
	class SceneManager
	{
	public:
		~SceneManager()
		{
			delete m_CurrentScene;
		}

		template<typename T> //makes func a template
		void RegisterScene(const std::string& name)
		{
			std::cout << "[*] Registering Scene: " << name << "\n"; //Debug
			m_Scenes.push_back(std::make_pair(name, []() { return new T(); })); //Pushes the pair <string><lambda> to back of vector.
		}
		
		void SetScene(const std::string& name)
		{
			for (auto index : m_Scenes) //Loop through all elements in m_Scenes
			{
				if (index.first.compare(name) == 0) //if the name passed by the func == the string in the pair.
				{
					delete m_CurrentScene; //de-alloc current scene and call the destructor
					m_CurrentScene = index.second(); //call the lambda of the matching string
				}
			}
		}

		Scene* m_CurrentScene = nullptr; //publicly accessible if needed
	private:
		std::vector<std::pair<std::string, std::function<Scene*()>>> m_Scenes; //vector array of pairs. Each pair contains a string and function pointer
	};

}