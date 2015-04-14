#include "Object.h"

/**************************************************************************************************************/

/*Constructs an Object.*/
Object::Object(std::string objFileName)
{
	/*Initialise the vertex buffer object*/
	InitialiseVAO(objFileName);
}

/**************************************************************************************************************/

/*Destructs an Object.*/
Object::~Object()
{
}

/**************************************************************************************************************/

/*Initialise the vertex array object.*/
void Object::InitialiseVAO(std::string objFileName)
{
	/*Creates one VAO*/
	glGenVertexArrays(1, &vertexArrayObject);
	/*initialise the code to bind to the VBO*/
	glBindVertexArray(vertexArrayObject);

	/*load the obj file*/
	std::vector<float> vertices;
	std::vector<float> vertexNormals;
	std::vector<float> vertexTextures;
	FileLoader::loadOBJFile(objFileName, vertices, vertexNormals, vertexTextures);

	/*set the vertices array to the contents of the vector*/
	float* verticesArray = &vertices[0];
	/*set the number of vertices's*/
	numberOfVertices = vertices.size();

	/*Variable for storing a VBO*/
	GLuint positionBuffer = 0;
	/*Create a generic buffer*/
	glGenBuffers(1, &positionBuffer);
	/*Tell OpenGL that we want to activate the buffer and that it's a VBO*/
	glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
	/*Send the data to OpenGL and set it to use GL_STATIC_DRAW (write it once)*/
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numberOfVertices, verticesArray, GL_STATIC_DRAW);

	/*set how the VBO will link to the shader*/
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	/*set the normal array to the contents of the vector*/
	float* normals = &vertexNormals[0];

	/*Variable for storing a VBO*/
	GLuint normalBuffer = 0;
	/*Create a generic 'buffer'*/
	glGenBuffers(1, &normalBuffer);
	/*Tell OpenGL that we want to activate the buffer and that it's a VBO*/
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	/*Send the data to OpenGL and set it to use GL_STATIC_DRAW (write it once)*/
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numberOfVertices, normals, GL_STATIC_DRAW);

	/*set how the VBO will link to the shader*/
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);


	/*unbind the VBO*/
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	/*disable the array*/
	glDisableVertexAttribArray(0);
}

/**************************************************************************************************************/

/*Returns the vertex buffer object.*/
GLuint Object::getVBO()
{
	/*returns the vertex buffer object*/
	return vertexArrayObject;
}

/**************************************************************************************************************/

/*Returns the number of vertices.*/
unsigned int Object::getNumberOfVertices()
{
	/*returns the vertex buffer object*/
	return numberOfVertices;
}