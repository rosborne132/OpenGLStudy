#include"shaderClass.h"

// Reads a text file and outputs a string with everything in the text file
std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}


/**
 * Creates shader by doing the following: 
 * Creating a shader and getting the reference. 
 * Attach Shader source to the Shader Object. 
 * Compile the Shader into machine code.
 *
 * @param shaderType The OpenGL shader type.
 * @param shaderSrc The source code of the shader.
 * @return A newly created shader.
 */
GLuint createShader(int shaderType, const char* shaderSrc) {
	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &shaderSrc, NULL);
	glCompileShader(shader);

	return shader;
}

// Constructor that build the Shader Program from 2 different shaders
Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	// Read vertexFile and fragmentFile and store the strings
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	// Convert the shader source strings into character arrays
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	// Creating shaders.
	GLuint vertexShader = createShader(GL_VERTEX_SHADER, vertexSource);
	GLuint fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentSource);

	// Create Shader Program Object and get its reference
	ID = glCreateProgram();
	// Attach the Vertex and Fragment Shaders to the Shader Program
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	// Wrap-up/Link all the shaders together into the Shader Program
	glLinkProgram(ID);

	// Delete the now useless Vertex and Fragment Shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

// Activates the Shader Program
void Shader::Activate()
{
	glUseProgram(ID);
}

// Deletes the Shader Program
void Shader::Delete()
{
	glDeleteProgram(ID);
}