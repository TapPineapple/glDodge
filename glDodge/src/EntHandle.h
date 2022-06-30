#pragma once
#include <memory>
#include <vector>
#include <map>

#include "glm/glm.hpp"
#include "glm/ext/matrix_transform.hpp"

#include <ft2build.h>
#include FT_FREETYPE_H

class Shader; //forward declarations to prevent header recursion
class Texture;

namespace game
{
	struct GlobalScores
	{
		int highScore;
		int lastScore;
		std::map<int, std::string> m_LeaderboardData; //3:40 pm
	};

	class Entity; 

	class EntHandle 
	{
	public:
		std::vector<Entity*> m_EntArry; //array of all ents

		std::unique_ptr<Shader> m_CubeShader; //m_CubeShader = std::make_unique<Shader>("res/shaders/cube.shader"); do this in the other area
		std::unique_ptr<Shader> m_PlaneShader;
		std::unique_ptr<Shader> m_TextShader;
		glm::mat4 m_DefaultProjection;
		glm::mat4 m_Default2DProjection;
		//GLFWwindow* hwind;

		std::map<int, std::unique_ptr<Texture>> m_TexMap; //map of all textures
		void RegisterTexture(std::string path, int texID)
		{
			m_TexMap[texID] = std::make_unique<Texture>(path); //i'm not sure why i did this and I think it's a memory leak lol. No shot i'm going to fix it before I have to present.
		}
	};
}