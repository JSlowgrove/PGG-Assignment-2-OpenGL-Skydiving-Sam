#include "CreditsUI.h"

/**************************************************************************************************************/

/*Constructs the CreditsUI object*/
CreditsUI::CreditsUI(std::string vertexShaderFileName, std::string fragmentShaderFileName,
	std::unordered_map<std::string, Shader*> &shaders)
	: UI(vertexShaderFileName, fragmentShaderFileName, shaders)
{
	/*load in the credits image*/
	credits = new UIObject(5.0f, 5.0f, 190.0f, 190.0f);
}

/**************************************************************************************************************/

/*Constructs the CreditsUI object*/
CreditsUI::CreditsUI(std::unordered_map<std::string, Shader*> &shaders)
	: UI(shaders)
{
	/*Loads the image as a surface*/
	SDL_Surface* image = IMG_Load("img/credits.png");

	/*Error Check - If unable to load image then end program*/
	if (!image)
	{
		std::cout << "Unable to load image from: img/credits.png" << std::endl;
	}

	/*initialise the credits image*/
	credits = new UIObject(5.0f, 5.0f, 190.0f, 190.0f, image);

	/*free the surfaces*/
	SDL_FreeSurface(image);
}

/**************************************************************************************************************/

/*Destructs the CreditsUI object*/
CreditsUI::~CreditsUI()
{
	/*delete pointers*/
	delete credits;
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