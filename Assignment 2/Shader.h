#pragma once

#include <iostream>
#include <glm.hpp>
#include "glew.h"
#include "FileLoader.h"

/**
@brief Creates a Shader for use with a OpenGL.
Creates a Shader from an text file, this can then be used with a OpenGL.
*/
class Shader
{
private:
	/**The Shader program of the Shader Object*/
	GLuint shaderProgram;
	/**The Uniform locations for the shader program*/
	GLint shaderModelMatrixLocation, shaderViewMatrixLocation, shaderProjectionMatrixLocation;

	/**
	A function to test if the shader compiled successfully.
	@param GLint The shader to test.
	@returns bool If the shader compiled successfully.
	*/
	bool Shader::CheckShaderCompiled(GLint shader);

	/**
	Initialise a shader.
	@param std::string The location of the shader file.
	@param char The type of the shader.
	*/
	void initaliseShader(std::string shaderFileLocation, char shaderType);

public:
	/**
	Constructs a Shader Object.
	Creates a Shader Object using an shader file location and OpenGL.
	@param std::string The location of the vertex shader file.
	@param std::string The location of the fragment shader file.
	*/
	Shader(std::string vertexShaderFileLocation, std::string fragmentShaderFileLocation);

	/**
	Destructs a Shader Object.
	Destructs the Shader Object deleting the Shader Object from memory.
	*/
	~Shader();

	/**
	Getter # Returns the shader program.
	@returns GLuint The shader program.
	*/
	GLuint getShaderProgram();

	/**
	Getter # Returns the shader model matrix location.
	@returns GLint The shader model matrix location.
	*/
	GLint getModelMatrixLocation();

	/**
	Getter # Returns the shader view matrix location.
	@returns GLint The shader view matrix location.
	*/
	GLint getViewMatrixLocation();

	/**
	Getter # Returns the shader projection matrix location.
	@returns GLint The shader projection matrix location.
	*/
	GLint getShaderProjectionMatrixLocation();
};