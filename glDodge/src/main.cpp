#include <GL/glew.h>
#include <GLFW/glfw3.h>

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
	}	

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	std::cout << "GL_VERSION: " << glGetString(GL_VERSION) << "\n";
	std::cout << "GL_VENDOR: " << glGetString(GL_VENDOR) << "\n";
	std::cout << "GL_RENDERER: " << glGetString(GL_RENDERER) << "\n";
	std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n";

	while (!glfwWindowShouldClose(window)) //draw loop
	{

		glfwSwapBuffers(window);
		glfwPollEvents();
	};

	glfwTerminate();

	return 0;
}