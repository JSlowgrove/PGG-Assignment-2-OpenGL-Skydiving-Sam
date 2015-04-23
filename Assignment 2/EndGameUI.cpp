#include "EndGameUI.h"

/**************************************************************************************************************/

/*Constructs the EndGameUI object*/
EndGameUI::EndGameUI(std::string vertexShaderFileName, std::string fragmentShaderFileName,
	std::unordered_map<std::string, Shader*> &shaders, float score)
	: UI(vertexShaderFileName, fragmentShaderFileName, shaders)
{
	/*load in the EndGame image*/
	endGame = new UIObject(5.0f, 5.0f, 190.0f, 190.0f);

	/*initialise the score UI object*/
	scoreText = new UIObject(75.0f, 50.0f, 50.0f, 25.0f);
}

/**************************************************************************************************************/

/*Constructs the EndGameUI object*/
EndGameUI::EndGameUI(std::unordered_map<std::string, Shader*> &shaders, float score)
	: UI(shaders)
{
	/*Loads the image as a surface*/
	SDL_Surface* image = IMG_Load("img/endGame.png");

	/*Error Check - If unable to load image then end program*/
	if (!image)
	{
		std::cout << "Unable to load image from: img/endGame.png" << std::endl;
	}

	/*initialise the EndGame image*/
	endGame = new UIObject(5.0f, 5.0f, 190.0f, 190.0f, image);


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

	/*The text to display*/
	std::string textContent = std::to_string((int)score);

	/*create surface*/
	SDL_Surface* text = TTF_RenderText_Blended(font, textContent.c_str(), fontColour);

	/*display the score*/
	scoreText = new UIObject(75.0f, 50.0f, 50.0f, 25.0f, text);

	/*delete font*/
	TTF_CloseFont(font);
	font = NULL;

	/*free the surfaces*/
	SDL_FreeSurface(image);
	SDL_FreeSurface(text);
}

/**************************************************************************************************************/

/*Destructs the EndGameUI object*/
EndGameUI::~EndGameUI()
{
	/*delete pointers*/
	delete endGame;
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

	/*draw the score*/
	scoreText->draw(shader);

	/*enable the depth test for the 3D next loop*/
	glEnable(GL_DEPTH_TEST);
}