#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

int main() 
{
	// Initialize variables.
	int window_height = 800;
	int window_width = 800;

	// Initialize GLFW.
	glfwInit();

	// Tell GLFW what version of OpenGL we are using. Example: 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	
	// Tell GLFW we are using the CORE profile which means we 
	// will be using only the modern functions.
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create GLFWwindow object.
	GLFWwindow* window = glfwCreateWindow(window_width, window_height, "OpenGLStudy", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window :c..\n";
		glfwTerminate();
		return -1;
	}

	// Add the window into the current context.
	glfwMakeContextCurrent(window);

	// Load GLAD so it configures OpenGL.
	gladLoadGL();

	// Specify the viewport of OpenGL in the window.
	glViewport(0, 0, window_width, window_height);

	// Specify the color of the background.
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	// Clean the back buffer and assign it the new color.
	glClear(GL_COLOR_BUFFER_BIT);
	// Swap the back buffer with the front buffer.
	glfwSwapBuffers(window);


	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
	}

	// Tear down window and GLFW before terminating the program.
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}