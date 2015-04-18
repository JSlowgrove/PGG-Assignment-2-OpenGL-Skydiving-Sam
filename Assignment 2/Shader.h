#pragma once

#include <iostream>
#include <glm.hpp>
#include "glew.h"
#include "FileLoader.h"

/**
@brief Creates a Shader for use with OpenGL.
Creates a Shader from an text file, this can then be used with OpenGL.
@author Jamie Slowgrove
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
	@param shader The shader to test.
	@returns If the shader compiled successfully.
	*/
	bool Shader::CheckShaderCompiled(GLint shader);

	/**
	Initialise a shader.
	@param shaderFileName The name of the shader file.
	@param shaderType The type of the shader.
	*/
	void initaliseShader(std::string shaderFileName, char shaderType);

public:
	/**
	Constructs a Shader Object.
	Creates a Shader Object using an shader file location and OpenGL.
	@param vertexShaderFileName The name of the vertex shader file.
	@param fragmentShaderFileName The name of the fragment shader file.
	*/
	Shader(std::string vertexShaderFileName, std::string fragmentShaderFileName);

	/**
	Destructs a Shader Object.
	Destructs the Shader Object deleting the Shader Object from memory.
	*/
	~Shader();

	/**
	Getter # Returns the shader program.
	@returns The shader program.
	*/
	GLuint getShaderProgram();

	/**
	Getter # Returns the shader model matrix location.
	@returns The shader model matrix location.
	*/
	GLint getModelMatrixLocation();

	/**
	Getter # Returns the shader view matrix location.
	@returns The shader view matrix location.
	*/
	GLint getViewMatrixLocation();

	/**
	Getter # Returns the shader projection matrix location.
	@returns The shader projection matrix location.
	*/
	GLint getShaderProjectionMatrixLocation();
};