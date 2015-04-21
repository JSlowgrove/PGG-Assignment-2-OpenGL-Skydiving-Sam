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

/*Constructs the MainMenuUI object*/
MainMenuUI::MainMenuUI(std::unordered_map<std::string, Shader*> &shaders)
	: UI(shaders)
{
	/*Loads the image as a surface*/
	SDL_Surface* image = IMG_Load("img/title.png");

	/*Error Check - If unable to load image then end program*/
	if (!image)
	{
		std::cout << "Unable to load image from: img/title.png" << std::endl;
	}

	/*initialise the title image*/
	title = new UIObject(50.0f, 25.0f, 100.0f, 50.0f, image);


	/*Loads the image as a surface*/
	image = IMG_Load("img/button.png");

	/*Error Check - If unable to load image then end program*/
	if (!image)
	{
		std::cout << "Unable to load image from: img/button.png" << std::endl;
	}

	/*load in the buttons*/
	play = new UIObject(75.0f, 100.0f, 50.0f, 20.0f, image);
	credits = new UIObject(75.0f, 125.0f, 50.0f, 20.0f, image);
	quit = new UIObject(75.0f, 150.0f, 50.0f, 20.0f, image);


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
	SDL_Surface *text = TTF_RenderText_Blended(font, "Play", fontColour);

	/*initialise the loading text*/
	playText = new UIObject(75.0f, 100.0f, 50.0f, 20.0f, text);

	/*create surface*/
	text = TTF_RenderText_Blended(font, "Credits", fontColour);

	/*initialise the loading text*/
	creditsText = new UIObject(75.0f, 125.0f, 50.0f, 20.0f, text);

	/*create surface*/
	text = TTF_RenderText_Blended(font, "Quit", fontColour);

	/*initialise the loading text*/
	quitText = new UIObject(75.0f, 150.0f, 50.0f, 20.0f, text);
	
	/*delete font*/
	TTF_CloseFont(font);
	font = NULL;

	/*free the surfaces*/
	SDL_FreeSurface(image);
	SDL_FreeSurface(text);
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

	/*draw the text*/
	playText->draw(shader);
	creditsText->draw(shader);
	quitText->draw(shader);

	/*enable the depth test for the 3D next loop*/
	glEnable(GL_DEPTH_TEST);
}