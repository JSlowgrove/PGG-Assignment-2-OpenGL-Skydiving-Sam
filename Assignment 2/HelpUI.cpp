#include "HelpUI.h"

/**************************************************************************************************************/

/*Constructs the HelpUI object*/
HelpUI::HelpUI(std::string vertexShaderFileName, std::string fragmentShaderFileName,
	std::unordered_map<std::string, Shader*> &shaders)
	: UI(vertexShaderFileName, fragmentShaderFileName, shaders)
{
	/*load in the help image*/
	help = new UIObject(5.0f, 5.0f, 190.0f, 190.0f);
}

/**************************************************************************************************************/

/*Constructs the HelpUI object*/
HelpUI::HelpUI(std::unordered_map<std::string, Shader*> &shaders)
	: UI(shaders)
{
	/*Loads the image as a surface*/
	SDL_Surface* image = IMG_Load("img/help.png");

	/*Error Check - If unable to load image then end program*/
	if (!image)
	{
		std::cout << "Unable to load image from: img/help.png" << std::endl;
	}

	/*initialise the help image*/
	help = new UIObject(5.0f, 5.0f, 190.0f, 190.0f, image);

	/*free the surfaces*/
	SDL_FreeSurface(image);
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