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

/*Constructs the LoadingScreen object*/
LoadingScreen::LoadingScreen(std::unordered_map<std::string, Shader*> &shaders)
	: UI(shaders)
{
	/*Loads the image as a surface*/
	SDL_Surface* image = IMG_Load("img/loadingImage.png");

	/*Error Check - If unable to load image then end program*/
	if (!image)
	{
		std::cout << "Unable to load image from: img/loadingImage.png" << std::endl;
	}

	/*initialise the loading image*/
	loadingImage = new UIObject(50.0f, 50.0f, 100.0f, 100.0f, image);

	/*initialise font and font colour*/
	TTF_Font* font = TTF_OpenFont("font/Underdog_tt_hinted.ttf", 100);

	/*Error Check - If unable to font image then end program*/
	if (!font)
	{
		std::cout << "Unable to load ttf from: font/Underdog_tt_hinted.ttf" << std::endl;
		printf("TTF error : %s", TTF_GetError());
	}
	
	/*initialises a colour*/
	SDL_Color fontColour = { 255, 255, 255 };
	/*create surface*/
	SDL_Surface *text = TTF_RenderText_Blended(font, "Loading...", fontColour);
	/*delete font*/
	TTF_CloseFont(font);
	font = NULL;

	/*initialise the loading text*/
	loadingText = new UIObject(150.0f, 175.0f, 50.0f, 25.0f, text);

	/*free the surfaces*/
	SDL_FreeSurface(text);
	SDL_FreeSurface(image);
}

/**************************************************************************************************************/

/*Destructs the LoadingScreen object*/
LoadingScreen::~LoadingScreen()
{
	/*delete pointers*/
	delete loadingImage;
	delete loadingText;
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