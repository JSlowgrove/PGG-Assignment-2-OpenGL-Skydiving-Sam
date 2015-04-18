#include "GameUI.h"

/**************************************************************************************************************/

/*Constructs the GameUI object*/
GameUI::GameUI(std::string vertexShaderFileName, std::string fragmentShaderFileName,
	std::unordered_map<std::string, Shader*> &shaders) 
	: UI(vertexShaderFileName, fragmentShaderFileName, shaders)
{
	/*initialise the GameUI Objects*/
	score = new UIObject(0.0f, 0.0f, 50.0f, 25.0f);
	height = new UIObject(150.0f, 0.0f, 50.0f, 25.0f);
}


/**************************************************************************************************************/

/*Constructs the GameUI object*/
GameUI::GameUI(std::string textureName, std::unordered_map<std::string, Shader*> &shaders)
	: UI(textureName, shaders)
{
	/*initialise the GameUI Objects*/
	score = new UIObject(0.0f, 0.0f, 50.0f, 25.0f);
	height = new UIObject(150.0f, 0.0f, 50.0f, 25.0f);
}

/**************************************************************************************************************/

/*Destructs the GameUI object*/
GameUI::~GameUI()
{
	/*delete pointers*/
	delete height;
	delete score;
}

/**************************************************************************************************************/

/*updates the GameUI*/
void GameUI::update(float dt)
{
}

/**************************************************************************************************************/

/*draws the GameUI*/
void GameUI::draw()
{
	/*disable the depth test to make the 2D appear on top of the 3D*/
	glDisable(GL_DEPTH_TEST);

	/*draw the UIObjects*/
	score->draw(shader);
	height->draw(shader);

	/*enable the depth test for the 3D next loop*/
	glEnable(GL_DEPTH_TEST);
}