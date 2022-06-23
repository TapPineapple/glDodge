#include "Entity.h"

extern game::EntHandle e_GameHandle;

namespace game
{
	Cube::Cube(int texID, glm::vec3 _pos, glm::vec3 size)
		: m_TexID(texID), m_Model(glm::mat4(1.0f)), m_View(glm::mat4(1.0f)), m_Translate(_pos)
	{
		
		glm::vec3 pos(0.0f);
		float vertices[] = {

			//x             //y             //z              /texture pos
			pos.x,          pos.y,          pos.z,           0.0f, 0.0f,
			pos.x + size.x, pos.y,          pos.z,           1.0f, 0.0f,
			pos.x + size.x, pos.y + size.y, pos.z,           1.0f, 1.0f,
			pos.x + size.x, pos.y + size.y, pos.z,           1.0f, 1.0f,
			pos.x,          pos.y + size.y, pos.z,           0.0f, 1.0f,
			pos.x,          pos.y,          pos.z,           0.0f, 0.0f,
												
			pos.x,          pos.y,          pos.z + size.z,  0.0f, 0.0f,
			pos.x + size.x, pos.y,          pos.z + size.z,  1.0f, 0.0f,
			pos.x + size.x, pos.y + size.y, pos.z + size.z,  1.0f, 1.0f,
			pos.x + size.x, pos.y + size.y, pos.z + size.z,  1.0f, 1.0f,
			pos.x,          pos.y + size.y, pos.z + size.z,  0.0f, 1.0f,
			pos.x,          pos.y,          pos.z + size.z,  0.0f, 0.0f,
												
			pos.x,          pos.y + size.y, pos.z + size.z,  1.0f, 0.0f,
			pos.x,          pos.y + size.y, pos.z,           1.0f, 1.0f,
			pos.x,          pos.y,          pos.z,           0.0f, 1.0f,
			pos.x,          pos.y,          pos.z,           0.0f, 1.0f,
			pos.x,          pos.y,          pos.z + size.z,  0.0f, 0.0f,
			pos.x,          pos.y + size.y, pos.z + size.z,  1.0f, 0.0f,
												
			pos.x + size.x, pos.y + size.y, pos.z + size.z,  1.0f, 0.0f,
			pos.x + size.x, pos.y + size.y, pos.z,           1.0f, 1.0f,
			pos.x + size.x, pos.y,          pos.z,           0.0f, 1.0f,
			pos.x + size.x, pos.y,          pos.z,           0.0f, 1.0f,
			pos.x + size.x, pos.y,          pos.z + size.z,  0.0f, 0.0f,
			pos.x + size.x, pos.y + size.y, pos.z + size.z,  1.0f, 0.0f,
												
			pos.x,          pos.y,          pos.z,           0.0f, 1.0f,
			pos.x + size.x, pos.y,          pos.z,           1.0f, 1.0f,
			pos.x + size.x, pos.y,          pos.z + size.z,  1.0f, 0.0f,
			pos.x + size.x, pos.y,          pos.z + size.z,  1.0f, 0.0f,
			pos.x,          pos.y,          pos.z + size.z,  0.0f, 0.0f,
			pos.x,          pos.y,          pos.z,           0.0f, 1.0f,
												
			pos.x,          pos.y + size.y, pos.z,           0.0f, 1.0f,
			pos.x + size.x, pos.y + size.y, pos.z,           1.0f, 1.0f,
			pos.x + size.x, pos.y + size.y, pos.z + size.z,  1.0f, 0.0f,
			pos.x + size.x, pos.y + size.y, pos.z + size.z,  1.0f, 0.0f,
			pos.x,          pos.y + size.y, pos.z + size.z,  0.0f, 0.0f,
			pos.x,          pos.y + size.y, pos.z,           0.0f, 1.0f
		};
		
		m_VertexArr = std::make_unique<VertexArray>();
		m_VertexBuf = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));

		VertexBufferLayout layout{};
		m_VertexArr->Bind();
		layout.Push<float>(3); //vec3 position
		layout.Push<float>(2); //tex coords
		m_VertexArr->AddBuffer(*m_VertexBuf, layout);

		e_GameHandle.m_EntArry.push_back(this); //this might have to turn into a map later so that when the deconstructor is called it gets removed from the array
		
	}

	Cube::~Cube()
	{
		for (int i = 0; i < e_GameHandle.m_EntArry.size(); i++)
		{
			if (e_GameHandle.m_EntArry[i] == this)
				e_GameHandle.m_EntArry.erase(e_GameHandle.m_EntArry.begin() + i); //idk if this works
		}

	}

	void Cube::Render()
	{
		e_GameHandle.m_TexMap[m_TexID]->Bind(); //bind texture
		e_GameHandle.m_CubeShader->Bind(); //bind shader

		//m_Model = glm::rotate(m_Model, 0, glm::vec3(0.5f, 1.0f, 0.0f));
		m_View = glm::translate(glm::mat4(1.0f), m_Translate);

		e_GameHandle.m_CubeShader->SetUniformMat4f("model", m_Model);
		e_GameHandle.m_CubeShader->SetUniformMat4f("view", m_View);
		e_GameHandle.m_CubeShader->SetUniformMat4f("projection", e_GameHandle.m_DefaultProjection);

		e_GameHandle.m_CubeShader->SetUniform4f("u_Color", m_ColorShift);

		m_VertexArr->Bind();
		glDrawArrays(GL_TRIANGLES, 0, 36);

	}

	void Cube::TranslateTo(glm::vec3 pos)
	{
		m_Translate = pos;
	}

	void Cube::TranslateBy(glm::vec3 pos)
	{
		m_Translate += pos;
	}

	void Cube::SetTex(int texID)
	{
		m_TexID = texID;
	}

	void Cube::SetColor(glm::vec4 color)
	{
		m_ColorShift = color;
	}

	/*---------------------------------------------------*/

	Plane::Plane(int texID, glm::vec3 _pos, glm::vec2 size)
		: m_TexID(texID), m_Translate(_pos)
	{
		glm::vec3 pos = glm::vec3(0.0f);
		float vertices[16] =
		{
			pos.x,          pos.y,          0.0f, 0.0f, //0
			pos.x + size.x, pos.y,          1.0f, 0.0f, //1
			pos.x + size.x, pos.y + size.y, 1.0f, 1.0f,//2
			pos.x,          pos.y + size.y, 0.0f, 1.0f //3

		};
		unsigned int indices[6] =
		{
			0, 1, 2,
			2, 3, 0
		};

		m_VertexArr = std::make_unique<VertexArray>();
		m_VertexBuf = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));
		m_IndexBuf = std::make_unique<IndexBuffer>(indices, sizeof(indices));

		VertexBufferLayout layout{};
		m_VertexArr->Bind();
		layout.Push<float>(2); //vec2 position
		layout.Push<float>(2); //tex coords
		m_VertexArr->AddBuffer(*m_VertexBuf, layout);

		//e_GameHandle.m_EntArry.push_back(this); 
	}

	Plane::~Plane()
	{
		for (int i = 0; i < e_GameHandle.m_EntArry.size(); i++)
		{ 
			//removes entity from global entity list when it's destructor is called
			if (e_GameHandle.m_EntArry[i] == this)
				e_GameHandle.m_EntArry.erase(e_GameHandle.m_EntArry.begin() + i);
		}
	}

	void Plane::Render()
	{
		e_GameHandle.m_TexMap[m_TexID]->Bind(); //bind texture
		e_GameHandle.m_PlaneShader->Bind(); //bind shader

		m_Model = glm::translate(glm::mat4(1.0f), m_Translate);
		m_View = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

		e_GameHandle.m_PlaneShader->SetUniformMat4f("model", m_Model);
		e_GameHandle.m_PlaneShader->SetUniformMat4f("view", m_View);
		e_GameHandle.m_PlaneShader->SetUniformMat4f("projection", e_GameHandle.m_Default2DProjection);

		e_GameHandle.m_PlaneShader->SetUniform4f("u_Color", m_ColorShift);


		m_VertexArr->Bind();
		m_IndexBuf->Bind();

		glDrawElements(GL_TRIANGLES, m_IndexBuf->GetCount(), GL_UNSIGNED_INT, nullptr);
	}

	void Plane::SetTex(int texID)
	{
		m_TexID = texID;
	}

	void Plane::SetColor(glm::vec4 color)
	{
		m_ColorShift = color;
	}

}

