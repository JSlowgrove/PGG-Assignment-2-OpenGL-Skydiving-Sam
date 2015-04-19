#include "HelpUI.h"

/**************************************************************************************************************/

/*Constructs the HelpUI object*/
HelpUI::HelpUI(std::string vertexShaderFileName, std::string fragmentShaderFileName,
	std::unordered_map<std::string, Shader*> &shaders)
	: UI(vertexShaderFileName, fragmentShaderFileName, shaders)
{
	/*load in the help image*/
	help = new UIObject(25.0f, 25.0f, 150.0f, 150.0f);
}

/**************************************************************************************************************/

/*Constructs the HelpUI object*/
HelpUI::HelpUI(std::string textureName, std::unordered_map<std::string, Shader*> &shaders)
	: UI(textureName, shaders)
{
	/*load in the help image*/
	help = new UIObject(25.0f, 25.0f, 150.0f, 150.0f);
}

/**************************************************************************************************************/

/*Destructs the HelpUI object*/
HelpUI::~HelpUI()
{
}

/**************************************************************************************************************/

/*updates the HelpUI*/
void HelpUI::update(float dt)
{
}

/**************************************************************************************************************/

/*draws the HelpUI*/
void HelpUI::draw()
{
	/*disable the depth test to make the 2D appear on top of the 3D*/
	glDisable(GL_DEPTH_TEST);

	/*draw the help image*/
	help->draw(shader);

	/*enable the depth test for the 3D next loop*/
	glEnable(GL_DEPTH_TEST);
}