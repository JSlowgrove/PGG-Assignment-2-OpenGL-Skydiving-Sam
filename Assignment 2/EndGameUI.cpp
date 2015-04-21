#include "EndGameUI.h"

/**************************************************************************************************************/

/*Constructs the EndGameUI object*/
EndGameUI::EndGameUI(std::string vertexShaderFileName, std::string fragmentShaderFileName,
	std::unordered_map<std::string, Shader*> &shaders)
	: UI(vertexShaderFileName, fragmentShaderFileName, shaders)
{
	/*load in the EndGame image*/
	endGame = new UIObject(25.0f, 25.0f, 150.0f, 150.0f);
}

/**************************************************************************************************************/

/*Constructs the EndGameUI object*/
EndGameUI::EndGameUI(std::string textureName, std::unordered_map<std::string, Shader*> &shaders)
	: UI(textureName, shaders)
{
	/*load in the EndGame image*/
	endGame = new UIObject(25.0f, 25.0f, 150.0f, 150.0f);
}

/**************************************************************************************************************/

/*Destructs the EndGameUI object*/
EndGameUI::~EndGameUI()
{
}

/**************************************************************************************************************/

/*updates the EndGameUI*/
void EndGameUI::update(float dt)
{
}

/**************************************************************************************************************/

/*draws the EndGameUI*/
void EndGameUI::draw()
{
	/*disable the depth test to make the 2D appear on top of the 3D*/
	glDisable(GL_DEPTH_TEST);

	/*draw the credits image*/
	endGame->draw(shader);

	/*enable the depth test for the 3D next loop*/
	glEnable(GL_DEPTH_TEST);
}