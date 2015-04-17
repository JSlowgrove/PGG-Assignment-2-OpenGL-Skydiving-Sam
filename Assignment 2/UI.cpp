#include "UI.h"

/**************************************************************************************************************/

/*Constructs the UI object*/
UI::UI(std::string vertexShaderFileName, std::string fragmentShaderFileName,
	std::unordered_map<std::string, Shader*> &shaders)
{
	/*initialise the shaders for the UI*/
	initialiseShaders(vertexShaderFileName, fragmentShaderFileName, shaders);
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
