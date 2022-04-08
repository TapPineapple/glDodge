#include <GL/glew.h>
#include <GLFW/glfw3.h>
<<<<<<< HEAD
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
=======
>>>>>>> 45a181618fd07af3fd48b886d6405003fa832233

#include <iostream>

int main()
{
	GLFWwindow* window;

	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	window = glfwCreateWindow(960, 540, "GlDodge", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return -1;
<<<<<<< HEAD
	}
=======
	}	
>>>>>>> 45a181618fd07af3fd48b886d6405003fa832233

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

<<<<<<< HEAD
	if (glewInit() != GLEW_OK)
	{
		return -1;
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.IniFilename = NULL;
	const char* glsl_version = "#version 440 core";
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
	ImGui::StyleColorsDark();


=======
>>>>>>> 45a181618fd07af3fd48b886d6405003fa832233
	std::cout << "GL_VERSION: " << glGetString(GL_VERSION) << "\n";
	std::cout << "GL_VENDOR: " << glGetString(GL_VENDOR) << "\n";
	std::cout << "GL_RENDERER: " << glGetString(GL_RENDERER) << "\n";
	std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n";

<<<<<<< HEAD

	while (!glfwWindowShouldClose(window)) //draw loop
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::ShowDemoWindow();

		ImGui::Render();
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
=======
	while (!glfwWindowShouldClose(window)) //draw loop
	{

>>>>>>> 45a181618fd07af3fd48b886d6405003fa832233
		glfwSwapBuffers(window);
		glfwPollEvents();
	};

	glfwTerminate();

	return 0;
}