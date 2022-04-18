#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

#include "SceneManager.h"
#include "Scene.h"

#include "scenes/TestScene.h"
#include "scenes/MainGame.h"

game::EntHandle e_GameHandle{};

void APIENTRY GLDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:
		std::cout << "[OpenGL Debug HIGH] " << message << "\n";
		__debugbreak();
		break;
	case GL_DEBUG_SEVERITY_MEDIUM:
		std::cout << "[OpenGL Debug MEDIUM] " << message << "\n";
		break;
	case GL_DEBUG_SEVERITY_LOW:
		std::cout << "[OpenGL Debug LOW] " << message << "\n";
		break;
	case GL_DEBUG_SEVERITY_NOTIFICATION:
		//std::cout << "[OpenGL Debug NOTIFICATION] " << message << "\n";
		break;
	}
}

int main()
{
	GLFWwindow* window;

	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(920, 540, "GlDodge", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK)
	{
		return -1;
	}

	//init debug callback
	glDebugMessageCallback(GLDebugCallback, nullptr);
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	
	//init imgui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.IniFilename = NULL;
	const char* glsl_version = "#version 440 core";
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
	ImGui::StyleColorsDark();

	//debug stuff
	std::cout << "GL_VERSION: " << glGetString(GL_VERSION) << "\n";
	std::cout << "GL_VENDOR: " << glGetString(GL_VENDOR) << "\n";
	std::cout << "GL_RENDERER: " << glGetString(GL_RENDERER) << "\n";
	std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n";

	
	e_GameHandle.m_CubeShader = std::make_unique<Shader>("res/shaders/cube.shader");
	e_GameHandle.m_PlaneShader = std::make_unique<Shader>("res/shaders/plane.shader");
	e_GameHandle.m_DefaultProjection = glm::perspective(glm::radians(60.0f), 960.0f / 540.0f, 0.1f, 100.0f);
	e_GameHandle.m_Default2DProjection = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);

	game::SceneManager sm{};
	sm.RegisterScene<game::TestScene>("TestScene");
	sm.RegisterScene<game::MainGame>("MainGame");

	sm.SetScene("MainGame");
	

	float deltaTime = 0.0f;	// Time between current frame and last frame
	float lastFrame = 0.0f; // Time of last frame
	
	while (!glfwWindowShouldClose(window)) //draw loop
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		sm.m_CurrentScene->OnUpdate(sm, deltaTime);
		sm.m_CurrentScene->OnRender();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		sm.m_CurrentScene->OnDebugRender();
		//ImGui::ShowStyleEditor();

		ImGui::Render();
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window);
		glfwPollEvents();
	};

	glfwTerminate();

	return 0;
}