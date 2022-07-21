#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include"modules/ShaderClass/ShaderClass.h"
#include"modules/VAO/VAO.h"
#include"modules/VBO/VBO.h"
#include"modules/EBO/EBO.h"


// Vertices coordinates.
GLfloat vertices[] =
{ //               COORDINATES                  /     COLORS           //
	-0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f, // Lower left corner
	 0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f, // Lower right corner
	 0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f,     1.0f, 0.6f,  0.32f, // Upper corner
	-0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.9f, 0.45f, 0.17f, // Inner left
	 0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.9f, 0.45f, 0.17f, // Inner right
	 0.0f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f  // Inner down
};

// Indices for vertices order.
GLuint indices[] =
{
	0, 3, 5, // Lower left triangle
	3, 2, 4, // Lower right triangle
	5, 4, 1 // Upper triangle
};

int main() 
{
	// Initialize variables.
	int window_height = 800;
	int window_width = 800;
	int glfw_major_version = 3;
	int glfw_minor_version = 3;

	glfwInit();

	// Tell GLFW what version of OpenGL we are using. Example: 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, glfw_major_version);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, glfw_minor_version);
	
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

	// Generates Shader object using shaders defualt.vert and default.frag.
	Shader shaderProgram("src/shaders/default.vert", "src/shaders/default.frag");

	// Generates Vertex Array Object and binds it.
	VAO VAO1;
	VAO1.Bind();

	// Generates Vertex Buffer Object and links it to vertices.
	VBO VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices.
	EBO EBO1(indices, sizeof(indices));

	// Links VBO attributes such as coordinates and colors to VAO.
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// Gets ID of uniform called "scale".
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	// Main while loop.
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background.
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

		// Clean the back buffer and assign the new color to it.
		glClear(GL_COLOR_BUFFER_BIT);

		shaderProgram.Activate();
		glUniform1f(uniID, 0.5f);
		VAO1.Bind();

		// Draw the triangle using the GL_TRIANGLES primitive.
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		// Swap the back buffer with the front buffer.
		glfwSwapBuffers(window);

		// Handle all GLFW events.
		glfwPollEvents();
	}

	// Tear down all object and windows before terminating the program.
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}