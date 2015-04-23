#include "GameUI.h"

/**************************************************************************************************************/

/*Constructs the GameUI object*/
GameUI::GameUI(std::string vertexShaderFileName, std::string fragmentShaderFileName,
	std::unordered_map<std::string, Shader*> &shaders, float scoreValue, float heightValue)
	: UI(vertexShaderFileName, fragmentShaderFileName, shaders)
{
	/*initialise the variables*/
	this->scoreValue = scoreValue;
	this->heightValue = heightValue;

	/*initialise the GameUI Objects*/
	score = new UIObject(0.0f, 0.0f, 50.0f, 25.0f);
	height = new UIObject(150.0f, 0.0f, 50.0f, 25.0f);
	helpInfo = new UIObject(25.0f, 175.0f, 150.0f, 25.0f);
}


/**************************************************************************************************************/

/*Constructs the GameUI object*/
GameUI::GameUI(std::unordered_map<std::string, Shader*> &shaders, float scoreValue, float heightValue)
	: UI(shaders)
{
	/*initialise the variables*/
	this->scoreValue = scoreValue;
	this->heightValue = heightValue;

	/*Loads the image as a surface*/
	SDL_Surface* image = IMG_Load("img/button.png");

	/*Error Check - If unable to load image then end program*/
	if (!image)
	{
		std::cout << "Unable to load image from: img/button.png" << std::endl;
	}

	/*initialise the GameUI Objects*/
	score = new UIObject(0.0f, 0.0f, 50.0f, 25.0f, image);
	height = new UIObject(150.0f, 0.0f, 50.0f, 25.0f, image);
	
	/*free the surfaces*/
	SDL_FreeSurface(image);

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
	SDL_Surface *text = TTF_RenderText_Blended(font, "Hit ESCAPE to return to the main menu. Hit ENTER for help.", fontColour);

	/*initialise the GameUI text*/
	helpInfo = new UIObject(25.0f, 180.0f, 150.0f, 20.0f, text);
	
	/*free the surfaces*/
	SDL_FreeSurface(text);
	
	/*The text to display*/
	std::string textContent = "Score: " + std::to_string((int)scoreValue);

	/*create surface*/
	text = TTF_RenderText_Blended(font, textContent.c_str(), fontColour);
	
	/*display the score*/
	scoreText = new UIObject(0.0f, 0.0f, 50.0f, 25.0f, text);

	/*The text to display*/
	textContent = std::to_string((int)heightValue) + " feet";

	/*create surface*/
	text = TTF_RenderText_Blended(font, textContent.c_str(), fontColour);

	/*display the height*/
	heightText = new UIObject(150.0f, 0.0f, 50.0f, 25.0f, text);

	/*delete font*/
	TTF_CloseFont(font);
	font = NULL;

	/*free the surfaces*/
	SDL_FreeSurface(text);
}

/**************************************************************************************************************/

/*Destructs the GameUI object*/
GameUI::~GameUI()
{
	/*delete pointers*/
	delete height;
	delete score;
	delete helpInfo;
	delete scoreText;
	delete heightText;
}

/**************************************************************************************************************/

/*updates the GameUI*/
void GameUI::update(float dt)
{
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
	std::string textContent = "Score: " + std::to_string((int)scoreValue);

	/*create surface*/
	SDL_Surface *text = TTF_RenderText_Blended(font, textContent.c_str(), fontColour);
	
	/*update the score*/
	delete scoreText;
	scoreText = new UIObject(0.0f, 0.0f, 50.0f, 25.0f, text);

	/*The text to display*/
	textContent = std::to_string((int)heightValue) + " feet";

	/*free the surfaces*/
	SDL_FreeSurface(text);

	/*create surface*/
	text = TTF_RenderText_Blended(font, textContent.c_str(), fontColour);

	/*display the height*/
	delete heightText;
	heightText = new UIObject(150.0f, 0.0f, 50.0f, 25.0f, text);

	/*delete font*/
	TTF_CloseFont(font);
	font = NULL;

	/*free the surfaces*/
	SDL_FreeSurface(text);
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
	helpInfo->draw(shader);
	scoreText->draw(shader);
	heightText->draw(shader);

	/*enable the depth test for the 3D next loop*/
	glEnable(GL_DEPTH_TEST);
}

/**************************************************************************************************************/

/*updates the score and height in the GameUI*/
void GameUI::updateValues(float scoreValue, float heightValue)
{
	/*initialise the variables*/
	this->scoreValue = scoreValue;
	this->heightValue = heightValue;
}