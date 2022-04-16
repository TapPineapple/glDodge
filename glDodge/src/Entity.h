#pragma once

#include <vector>
#include <memory>
#include <map>

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Texture.h"
#include "Shader.h"
#include "VertexBufferLayout.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "EntHandle.h"


namespace game
{

	class Entity
	{
	public:
		Entity() {}
		virtual ~Entity() {}
		virtual void Render() {}
	private:
	};

	//example cube creation 
	// std::vector<Entity>entArray; 
	//Cube CubeClass = new CubeClass(int texID, glm::vec3 pos, glm::vec3 size, glm::vec3 rot) //constructor will push_back every ent created

	class Cube : public Entity
	{
	public:

		//************************************
		// Method:    Cube
		// FullName:  game::Cube::Cube
		// Access:    public 
		// Returns:   
		// Qualifier:
		// Parameter: EntHandle & handle
		// Parameter: int texID
		// Parameter: glm::vec3 pos
		// Parameter: glm::vec3 size
		// Parameter: glm::vec3 rot
		//************************************
		Cube(int texID, glm::vec3 pos, glm::vec3 size); //note that rotation isn't yet implemented...
		~Cube();

		void Render() override;
		void Translate(glm::vec3 pos);
		void RelTranslate(glm::vec3 pos);

		glm::vec3 m_Translate;
	private:
		int m_TexID;

		glm::mat4 m_Model;
		glm::mat4 m_View;

		std::unique_ptr<VertexArray> m_VertexArr; //abstracted vertex array class
		std::unique_ptr<VertexBuffer> m_VertexBuf; //abstracted vertex buffer class
		
	};

}
