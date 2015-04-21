#include "CreditsUI.h"

/**************************************************************************************************************/

/*Constructs the CreditsUI object*/
CreditsUI::CreditsUI(std::string vertexShaderFileName, std::string fragmentShaderFileName,
	std::unordered_map<std::string, Shader*> &shaders)
	: UI(vertexShaderFileName, fragmentShaderFileName, shaders)
{
	/*load in the credits image*/
	credits = new UIObject(25.0f, 25.0f, 150.0f, 150.0f);
}

/**************************************************************************************************************/

/*Constructs the CreditsUI object*/
CreditsUI::CreditsUI(std::unordered_map<std::string, Shader*> &shaders)
	: UI(shaders)
{
	/*load in the credits image*/
	credits = new UIObject(25.0f, 25.0f, 150.0f, 150.0f);
}

/**************************************************************************************************************/

/*Destructs the CreditsUI object*/
CreditsUI::~CreditsUI()
{
}

/**************************************************************************************************************/

/*updates the CreditsUI*/
void CreditsUI::update(float dt)
{
}

/**************************************************************************************************************/

/*draws the CreditsUI*/
void CreditsUI::draw()
{
	/*disable the depth test to make the 2D appear on top of the 3D*/
	glDisable(GL_DEPTH_TEST);

	/*draw the credits image*/
	credits->draw(shader);

	/*enable the depth test for the 3D next loop*/
	glEnable(GL_DEPTH_TEST);
}