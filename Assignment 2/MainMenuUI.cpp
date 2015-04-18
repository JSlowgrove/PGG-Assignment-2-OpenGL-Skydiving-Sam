#include "MainMenuUI.h"

/**************************************************************************************************************/

/*Constructs the MainMenuUI object*/
MainMenuUI::MainMenuUI(std::string vertexShaderFileName, std::string fragmentShaderFileName,
	std::unordered_map<std::string, Shader*> &shaders)
	: UI(vertexShaderFileName, fragmentShaderFileName, shaders)
{
	/*load in the title image*/
	title = new UIObject(50.0f, 25.0f, 100.0f, 50.0f);
	/*load in the buttons*/
	play = new UIObject(75.0f, 100.0f, 50.0f, 20.0f);
	credits = new UIObject(75.0f, 125.0f, 50.0f, 20.0f);
	quit = new UIObject(75.0f, 150.0f, 50.0f, 20.0f);
}

/**************************************************************************************************************/

/*Destructs the MainMenuUI object*/
MainMenuUI::~MainMenuUI()
{
}

/**************************************************************************************************************/

/*updates the MainMenuUI*/
void MainMenuUI::update(float dt)
{
}

/**************************************************************************************************************/

/*draws the MainMenuUI*/
void MainMenuUI::draw()
{
	/*disable the depth test to make the 2D appear on top of the 3D*/
	glDisable(GL_DEPTH_TEST);

	/*draw the title*/
	title->draw(shader);

	/*draw the buttons*/
	play->draw(shader);
	credits->draw(shader);
	quit->draw(shader);

	/*enable the depth test for the 3D next loop*/
	glEnable(GL_DEPTH_TEST);
}