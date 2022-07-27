#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<glad/glad.h>

// Vertex Buffer Object (VBO): The buffer object that allocates memory on the GPU and stores all the vertex data there for the GPU to use.
class VBO
{
public:
	// Reference ID of the Vertex Buffer Object.
	GLuint ID;

	// Constructor that generates a Vertex Buffer Object and links it to vertices.
	VBO(GLfloat* vertices, GLsizeiptr size)
	{
		glGenBuffers(1, &ID);
		glBindBuffer(GL_ARRAY_BUFFER, ID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	// Binds the VBO.
	void Bind() { glBindBuffer(GL_ARRAY_BUFFER, ID); }

	// Unbinds the VBO. This is to prevent unwanted modifcations.
	void Unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }

	// Deletes the VBO.
	void Delete() { glDeleteBuffers(1, &ID); }
};

#endif