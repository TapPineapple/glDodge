#pragma once

#include <vector>
#include <memory>
#include <map>

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Texture.h"
#include "Shader.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"

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
		Cube(int texID, glm::vec3 _pos, glm::vec3 size); //note that rotation isn't yet implemented...
		~Cube();

		void Render() override;
		void TranslateTo(glm::vec3 pos);
		void TranslateBy(glm::vec3 pos);

		void SetColor(glm::vec4 color);

		glm::vec3 m_Translate; //what's editable by the user
	private:
		int m_TexID;
		glm::vec4 m_ColorShift;

		glm::mat4 m_Model;
		glm::mat4 m_View;

		std::unique_ptr<VertexArray> m_VertexArr; //abstracted vertex array class
		std::unique_ptr<VertexBuffer> m_VertexBuf; //abstracted vertex buffer class
		
	};

	class Plane : public Entity
	{
	public:

		
		//************************************
		// Method:    Plane
		// FullName:  game::Plane::Plane
		// Access:    public 
		// Returns:   
		// Qualifier:
		// Parameter: int texID
		// Parameter: glm::vec3 pos
		// Parameter: glm::vec3 size
		//************************************
		Plane(int texID, glm::vec3 _pos, glm::vec2 size); //note that rotation isn't yet implemented...
		~Plane();

		void Render() override;
		void SetColor(glm::vec4 color);

		glm::vec3 m_Translate; //what's editable by the user
	private:
		int m_TexID;
		glm::vec4 m_ColorShift;

		glm::mat4 m_Model;
		glm::mat4 m_View;

		std::unique_ptr<VertexArray> m_VertexArr; //abstracted vertex array class
		std::unique_ptr<VertexBuffer> m_VertexBuf; //abstracted vertex buffer class
		std::unique_ptr<IndexBuffer> m_IndexBuf;

	};

}
