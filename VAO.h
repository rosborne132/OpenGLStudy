#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include<glad/glad.h>
#include"VBO.h"

class VAO
{
public:
	// ID reference for the Vertex Array Object.
	GLuint ID;

	// Constructor that generates a VAO ID.
	VAO();

	// Links a VBO to the VAO using a certain layout.
	void LinkVBO(VBO& VBO, GLuint layout);
	
	// Bind the VAO so OpenGL knows to use it.
	void Bind();
	
	// Unbinds the VAO. This is to prevent unwanted modifcations.
	void Unbind();
	
	// Deletes the VAO.
	void Delete();
};
#endif