#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"modules/ShaderClass/ShaderClass.h"
#include"modules/VAO/VAO.h"
#include"modules/VBO/VBO.h"
#include"modules/EBO/EBO.h"
#include"modules/Texture/Texture.h"
#include"modules/Camera/Camera.h"

// Initialize variables.
const unsigned int window_height = 800;
const unsigned int window_width = 800;
const unsigned int glfw_major_version = 3;
const unsigned int glfw_minor_version = 3;


// Vertices coordinates.
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f
};

// Indices for vertices order.
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
};

int main() 
{
	glfwInit();

	// Tell GLFW what version of OpenGL we are using. Example: 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, glfw_major_version);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, glfw_minor_version);
	
	// Tell GLFW we are using the CORE profile which means we 
	// will be using only the modern functions.
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(window_width, window_height, "OpenGLStudy", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window :c..\n";
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	gladLoadGL();
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
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// Texture
	Texture brickTex("src/textures/brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	brickTex.texUnit(shaderProgram, "tex0", 0);

	// Variables to rotate the pyramid.
	float rotation = 0.0f;
	double prevTime = glfwGetTime();

	// Enables the Depth Buffer.
	glEnable(GL_DEPTH_TEST);

	// Creates camera object
	Camera camera(window_width, window_width, glm::vec3(0.0f, 0.0f, 2.0f));

	// Main while loop.
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background.
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

		// Clean the back buffer and assign the new color to it.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderProgram.Activate();

		camera.Inputs(window);
		camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "cameraMatrix");

		brickTex.Bind();
		VAO1.Bind();

		// Draw the triangle using the GL_TRIANGLES primitive.
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

		// Swap the back buffer with the front buffer.
		glfwSwapBuffers(window);

		// Handle all GLFW events.
		glfwPollEvents();
	}

	// Tear down all object and windows before terminating the program.
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	brickTex.Delete();
	shaderProgram.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}