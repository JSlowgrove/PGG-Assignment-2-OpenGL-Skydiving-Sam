#include "Object.h"

/**************************************************************************************************************/

/*Constructs an Object.*/
Object::Object(std::string objFileName)
{
	/*initialise the material*/
	material = "Untextured";

	/*Initialise the vertex buffer object*/
	InitialiseVAO(objFileName);
}

/**************************************************************************************************************/

/*Constructs an Object.*/
Object::Object(std::string objFileName, std::string material)
{
	/*store the material*/
	this->material = "mat/" + material;

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
	numberOfVertices = vertices.size() / 3;

	/*Variable for storing a VBO*/
	GLuint positionBuffer = 0;
	/*Create a generic buffer*/
	glGenBuffers(1, &positionBuffer);
	/*Tell OpenGL that we want to activate the buffer and that it's a VBO*/
	glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
	/*Send the data to OpenGL and set it to use GL_STATIC_DRAW (write it once)*/
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numberOfVertices * 3, verticesArray, GL_STATIC_DRAW);

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
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numberOfVertices * 3, normals, GL_STATIC_DRAW);

	/*set how the VBO will link to the shader*/
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	/*test if the model uses a texture*/
	if (material != "Untextured")
	{
		/*initialise the texture*/
		initialiseTexture(vertexTextures);
	}

	/*unbind the VBO*/
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	/*disable the array*/
	glDisableVertexAttribArray(0);
}

/**************************************************************************************************************/

/*Initialise the texture.*/
void Object::initialiseTexture(std::vector<float> vertexTextures)
{
	/*Loads the image as a surface*/
	SDL_Surface* image = IMG_Load(material.c_str());

	/*Error Check - If unable to load image then end program*/
	if (!image)
	{
		std::cout << "Unable to load image from: " << material << std::endl;
		printf("Image error : %s", IMG_GetError());
	}

	/*check and store the file format*/
	GLenum format;
	if (image->format->BytesPerPixel == 3)
	{
		format = GL_RGB;
	}
	else if (image->format->BytesPerPixel == 4)
	{
		format = GL_RGBA;
	}

	/*set the texture coordinates array to the contents of the vector*/
	float* textureCoordinates = &vertexTextures[0];

	// Create one OpenGL texture
	glGenTextures(1, &textureID);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Give the image to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, format, image->w, image->h, 0, format, GL_UNSIGNED_BYTE, image->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	/*unbind texture*/
	glBindTexture(GL_TEXTURE_2D, 0);

	// Variable for storing a VBO
	GLuint textureBuffer = 0;
	// Create a generic 'buffer'
	glGenBuffers(1, &textureBuffer);
	// Tell OpenGL that we want to activate the buffer and that it's a VBO
	glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
	// With this buffer active, we can now send our data to OpenGL
	// We need to tell it how much data to send
	// We can also tell OpenGL how we intend to use this buffer - here we say GL_STATIC_DRAW because we're only writing it once
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numberOfVertices * 2, textureCoordinates, GL_STATIC_DRAW);

	// This tells OpenGL how we link the vertex data to the shader
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);
}

/**************************************************************************************************************/

/*Returns the vertex array object.*/
GLuint Object::getVAO()
{
	/*returns the vertex array object*/
	return vertexArrayObject;
}

/**************************************************************************************************************/

/*Returns the texture ID.*/
GLuint Object::getTextureID()
{
	/*returns the texture ID*/
	return textureID;
}

/**************************************************************************************************************/

/*Returns the number of vertices.*/
unsigned int Object::getNumberOfVertices()
{
	/*returns the vertex buffer object*/
	return numberOfVertices;
}