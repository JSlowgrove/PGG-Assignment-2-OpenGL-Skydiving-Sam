#include "UI.h"

/**************************************************************************************************************/

/*Constructs the UI object*/
UI::UI(std::string vertexShaderFileName, std::string fragmentShaderFileName,
	std::unordered_map<std::string, Shader*> &shaders)
{
	initialiseShaders(vertexShaderFileName, fragmentShaderFileName, shaders);
	
	// Create the vertex array object for our triangle
	triangleVAO = CreateTriangleVAO();
}

/**************************************************************************************************************/

/*Initialise the shaders.*/
void UI::initialiseShaders(std::string vertexShaderFileName, std::string fragmentShaderFileName,
	std::unordered_map<std::string, Shader*> &shaders)
{
	/*a string for the name of the linked shader*/
	std::string linkedShaderName = vertexShaderFileName + "/" + fragmentShaderFileName;

	/*test if the shader has already been loaded*/
	if (shaders.count(linkedShaderName) == 0)
	{
		/*load the shader*/
		shaders[linkedShaderName] = new Shader(vertexShaderFileName, fragmentShaderFileName);
	}
	else
	{
		/*print out that it is already loaded*/
		std::cout << linkedShaderName << " shader already loaded." << std::endl << std::endl;
	}
	/*initialise the object*/
	shader = shaders[linkedShaderName];
}

/**************************************************************************************************************/

/*Destructs the UI object*/
UI::~UI()
{
	
}

/**************************************************************************************************************/

/*updates the UI*/
void UI::update(float dt)
{
}

/**************************************************************************************************************/

/*draws the UI*/
void UI::draw()
{
	/*disable the depth test to make the 2D appear on top of the 3D*/
	glDisable(GL_DEPTH_TEST);

	// Call our drawing function to draw that triangle!
	DrawVAOTris(triangleVAO, 3);

	/*enable the depth test for the 3D next loop*/
	glEnable(GL_DEPTH_TEST);
}

// This creates a Vertex Array Object for a single triangle
// The VAO stores one or more Vertex Buffer Objects
// The VBOs store the actual vertex data (e.g. one each for positions, colours, texture coords etc)
// The VAO tells the server how to actually interpret and use the VBO data
GLuint UI::CreateTriangleVAO()
{
	// Variable for storing our VAO
	// OpenGL has its own defined datatypes - a 'GLuint' is basically an unsigned int
	GLuint VAO = 0;
	// Creates one VAO
	glGenVertexArrays(1, &VAO);
	// 'Binding' something makes it the current one we are using
	// This is like activating it, so that subsequent function calls will work on this item
	glBindVertexArray(VAO);

	// Simple vertex data for a triangle
	// OpenGL is happy for us to work with 2D coordinates if we want
	float vertices[] = {
		-0.90f, -0.90f,
		0.85f, -0.90f,
		-0.90f, 0.85f
	};

	// Variable for storing a VBO
	GLuint buffer = 0;
	// Create a generic 'buffer'
	glGenBuffers(1, &buffer);
	// Tell OpenGL that we want to activate the buffer and that it's a VBO
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	// With this buffer active, we can now send our data to OpenGL
	// We need to tell it how much data to send
	// We can also tell OpenGL how we intend to use this buffer - here we say GL_STATIC_DRAW because we're only writing it once
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6, vertices, GL_STATIC_DRAW);

	// This tells OpenGL how we link the vertex data to the shader
	// (We will look at this properly in the lectures)
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	// Unbind for neatness, it just makes life easier
	// As a general tip, especially as you're still learning, for each function that needs to do something specific try to return OpenGL in the state you found it in
	// This means you will need to set the states at the beginning of your function and set them back at the end
	// If you don't do this, your function could rely on states being set elsewhere and it's easy to lose track of this as your project grows
	// If you then change the code from elsewhere, your current code could mysteriously stop working properly!
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return VAO;
}

// Draws the VAO
void UI::DrawVAOTris(GLuint VAO, int numVertices)
{
	// Ok, here I like to indent drawing calls - it's just a personal style, you may not like it and that's fine ;)
	// Generally you will need to be activating and deactivating OpenGL states
	// I just find it visually easier if the activations / deactivations happen at different tab depths
	// This can help when things get more complex

	// Activate the shader program
	glUseProgram(shader->getShaderProgram());

	// Activate the VAO
	glBindVertexArray(VAO);
	// Tell OpenGL to draw it
	// Must specify the type of geometry to draw and the number of vertices
	glDrawArrays(GL_TRIANGLES, 0, numVertices);

	// Unbind VAO
	glBindVertexArray(0);

	// Technically we can do this, but it makes no real sense because we must always have a valid shader program to draw geometry
	glUseProgram(0);
}