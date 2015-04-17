#include "LoadingScreen.h"

/**************************************************************************************************************/

/*Constructs the LoadingScreen object*/
LoadingScreen::LoadingScreen(std::string vertexShaderFileName, std::string fragmentShaderFileName,
	std::unordered_map<std::string, Shader*> &shaders)
	: UI(vertexShaderFileName, fragmentShaderFileName, shaders)
{
	/*initialise the loading text*/
	loadingText = new UIObject(150.0f, 175.0f, 50.0f, 25.0f);
	/*initialise the loading image*/
	loadingImage = new UIObject(50.0f, 50.0f, 100.0f, 100.0f);
}

/**************************************************************************************************************/

/*Destructs the LoadingScreen object*/
LoadingScreen::~LoadingScreen()
{
}

/**************************************************************************************************************/

/*updates the LoadingScreen*/
void LoadingScreen::update(float dt)
{
}

/**************************************************************************************************************/

/*draws the LoadingScreen*/
void LoadingScreen::draw()
{
	/*disable the depth test to make the 2D appear on top of the 3D*/
	glDisable(GL_DEPTH_TEST);

	/*draw the loading image*/
	loadingImage->draw(shader);

	/*draw the loading text*/
	loadingText->draw(shader);

	/*enable the depth test for the 3D next loop*/
	glEnable(GL_DEPTH_TEST);
}