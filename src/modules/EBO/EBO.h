#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include<glad/glad.h>

// Element Buffer Object (EBO): A buffer object that stores the indices on the GPU for indexed drawing.
class EBO
{
public:
	// ID reference of Elements Buffer Object.
	GLuint ID;

	// Constructor that generates a Elements Buffer Object and links it to indices.
	EBO(GLuint* indices, GLsizeiptr size)
	{
		glGenBuffers(1, &ID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
	}

	// Binds the EBO.
	void Bind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID); }

	// Unbinds the EBO. This is to prevent unwanted modifcations.
	void Unbind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

	// Deletes the EBO.
	void Delete() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }
};

#endif