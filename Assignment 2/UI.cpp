#include "UI.h"

/**************************************************************************************************************/

/*Constructs the UI object*/
UI::UI(std::string vertexShaderFileName, std::string fragmentShaderFileName,
	std::unordered_map<std::string, Shader*> &shaders)
{
	/*initialise the shaders for the UI*/
	initialiseShaders(vertexShaderFileName, fragmentShaderFileName, shaders);
	
	/*initialise the UIObjects*/
	score = new UIObject(0.0f, 0.0f, 50.0f, 25.0f);
	time = new UIObject(150.0f, 0.0f, 50.0f, 25.0f);
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

	/*draw the UIObjects*/
	score->draw(shader);
	time->draw(shader);

	/*enable the depth test for the 3D next loop*/
	glEnable(GL_DEPTH_TEST);
}