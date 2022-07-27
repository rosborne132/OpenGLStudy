#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include<glad/glad.h>
#include"../VBO/VBO.h"

// Vertex Array Object (VAO): An object that stores buffer and vertex attribute state information.
class VAO
{
public:
	// ID reference for the Vertex Array Object.
	GLuint ID;

	// Constructor that generates a VAO ID.
	VAO() { glGenVertexArrays(1, &ID); }

	// Links a VBO to the VAO using a certain layout.
	void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
	{
		VBO.Bind();
		glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
		glEnableVertexAttribArray(layout);
		VBO.Unbind();
	}

	// Bind the VAO so OpenGL knows to use it.
	void Bind() { glBindVertexArray(ID); }
	
	// Unbinds the VAO. This is to prevent unwanted modifcations.
	void Unbind() { glBindVertexArray(0); }
	
	// Deletes the VAO.
	void Delete() { glDeleteVertexArrays(1, &ID); }
};
#endif