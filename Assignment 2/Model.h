#include <iostream>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>
#include <unordered_map>
#include "glew.h"
#include "Shader.h"
#include "Object.h"

/**
@brief Creates a Model from an object and a shader.
@author Jamie Slowgrove
*/
class Model
{
private:
	/**The Shader for the Model*/
	Shader* shader;
	/**The object for the Model*/
	Object* obj;
	/**The Position of the Model*/
	glm::vec3 position;
	/**The matrix for the Model*/
	glm::mat4 matrix;

	/**
	Initialise the object for the Model.
	@param std::string The name of the obj file.
	@param std::unordered_map<std::string, Object*> A reference to the loaded Object files
	*/
	void initialiseVAO(std::string objFileName, std::unordered_map<std::string, Object*> &objects);

	/**
	Initialise the shaders.
	@param std::string The name of the vertex shader file.
	@param std::string The name of the fragment shader file.
	@param std::unordered_map<std::string, Shader*> A reference to the loaded Shader files
	*/
	void initialiseShaders(std::string vertexShaderFileName, std::string fragmentShaderFileName, 
		std::unordered_map<std::string, Shader*> &shaders);

public:
	/**
	Constructs a Model Object.
	Creates a Model Object using the shader file locations, the obj file location and OpenGL.
	@param std::string The name of the vertex shader file.
	@param std::string The name of the fragment shader file.
	@param std::string The name of the obj file.
	@param std::unordered_map<std::string, Object*> A reference to the loaded Object files
	@param std::unordered_map<std::string, Shader*> A reference to the loaded Shader files
	*/
	Model(std::string vertexShaderFileName, std::string fragmentShaderFileName, std::string objFileName,
		std::unordered_map<std::string, Object*> &objects, std::unordered_map<std::string, Shader*> &shaders);

	/**
	Destructs a Model Object.
	Destructs the Model Object deleting the Model Object from memory.
	*/
	~Model();

	/// Currently just updates rotation to make the model rotate
	void update(float deltaTs);

	/**
	Draw the Model to the screen.
	@param glm::mat4 A reference to the camera view matrix.
	@param glm::mat4 A reference to the camera projection matrix.
	*/
	void draw(glm::mat4 &viewMatrix, glm::mat4 &projMatrix);

	/**
	Setter # Sets the position of the Model.
	@param glm::vec3 The new position.
	*/
	void setPosition(glm::vec3 position);

	/**
	Setter # Sets the position of the Model.
	@param float The X position.
	@param float The Y position.
	@param float The Z position.
	*/
	void setPosition(float x, float y, float z);

	/**
	Rotate the Model along the X axis.
	@param float The rotation angle (Euler angle [Radians]).
	*/
	void rotateX(float angle);
	
	/**
	Rotate the Model along the Y axis.
	@param float The rotation angle (Euler angle [Radians]).
	*/
	void rotateY(float angle);

	/**
	Rotate the Model along the Z axis.
	@param float The rotation angle (Euler angle [Radians]).
	*/
	void rotateZ(float angle);

	/**
	Scale the Model.
	@param glm::vec3 The new scale of the Model.
	*/
	void scale(glm::vec3 scaleVector);
};
