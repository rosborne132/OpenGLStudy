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

	// Gets ID of uniform called "scale".
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	// Texture
	Texture brickTex("src/textures/brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	brickTex.texUnit(shaderProgram, "tex0", 0);

	// Variables to rotate the pyramid.
	float rotation = 0.0f;
	double prevTime = glfwGetTime();

	// Enables the Depth Buffer.
	glEnable(GL_DEPTH_TEST);

	// Main while loop.
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background.
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

		// Clean the back buffer and assign the new color to it.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderProgram.Activate();

		// Simple timer to rotate pyramid.
		double crntTime = glfwGetTime();
		if (crntTime - prevTime >= 1 / 60)
		{
			rotation += 0.05f;
			prevTime = crntTime;
		}

		// Initializes matrices.
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);

		// Assigns different transformations to each matrix.
		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
		proj = glm::perspective(glm::radians(45.0f), (float)window_width / window_height, 0.1f, 100.0f);

		// Outputs the matrices into the Vertex Shader.
		int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		int projLoc = glGetUniformLocation(shaderProgram.ID, "proj");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

		// Assigns a value to the uniform.This must always be done after activating the Shader Program.
		glUniform1f(uniID, 0.5f);

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