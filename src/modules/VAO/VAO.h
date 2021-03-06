#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include<glad/glad.h>
#include"../VBO/VBO.h"

class VAO
{
public:
	// ID reference for the Vertex Array Object.
	GLuint ID;

	// Constructor that generates a VAO ID.
	VAO();

	// Links a VBO to the VAO using a certain layout.
	void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);

	// Bind the VAO so OpenGL knows to use it.
	void Bind();
	
	// Unbinds the VAO. This is to prevent unwanted modifcations.
	void Unbind();
	
	// Deletes the VAO.
	void Delete();
};
#endif