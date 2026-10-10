#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <vector>
#include <iostream>
#include <string>

#include "Bot.h"
#include "Text.h"
#include "GameState.h"


using namespace std;

struct Resources
{
	std::vector<SDL_Texture*> textures;
	SDL_Texture* texIdle;
	SDL_Texture* texBall;
	SDL_Texture* texBot;
	TTF_Font* font;

	SDL_Texture* loadTexture(SDL_Renderer *renderer, const std::string& filepath)
	{
		SDL_Texture* tex = IMG_LoadTexture(renderer, filepath.c_str());

		SDL_SetTextureScaleMode(tex, SDL_SCALEMODE_NEAREST); 
		// this changes the texture scale mode to nearest so pixels don't blend into each other

		textures.push_back(tex);
		return tex;
	}

	void load(SDLState& state)
	{
		texBall = loadTexture(state.renderer, "data/ball.png");
		texIdle = loadTexture(state.renderer, "data/player.png");
		texBot = loadTexture(state.renderer, "data/player.png");
		
		font = TTF_OpenFont("data/font.ttf", 24);		
	}

	void unload()
	{
		for (SDL_Texture* tex : textures)
		{
			SDL_DestroyTexture(tex);
		}
	}
};

bool init(SDLState& state);
void cleanup(SDLState& state);
void resetSet(Ball& ball, Player& player, Bot& bot);
void drawMiddle(SDLState& state);

int main(int argc, char* argv[])
{
	// declare state
	SDLState state = SDLState(); 
	
	if (init(state) == false)
		return 1;
	
	// load game assets
	Resources res;
	res.load(state);

	//setup game data and game objects
	const bool* keys = SDL_GetKeyboardState(nullptr); // returns array of bools and we can index into it using SDL key codes
	uint64_t prevTime = SDL_GetTicks(); // gets the time in ms since the SDL was init
	GameState currentState = GameState::START_SCREEN;
	
	Player player = Player();
	player.texture = res.texIdle;
	
	Ball ball = Ball();
	ball.texture = res.texBall;
	
	Bot bot = Bot();
	bot.texture = res.texBot;
	
	Text text = Text();
	text.font = res.font;

	int playerScore = 0 , botScore = 0;
	
	SDL_Event event{ 0 };

	// start game loop
	bool running = true;
	while (running)
	{	
		uint64_t nowTime = SDL_GetTicks(); // gets the time in ms since the SDL was init
		float deltaTime = (nowTime - prevTime) / 1000.0f; // in seconds
		
		// check & handle events
		
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_EVENT_QUIT:
				{
					running = false;
					break;
				}
				case SDL_EVENT_WINDOW_RESIZED:
				{
					state.width = event.window.data1;
					state.height = event.window.data2;
					break;
				}
				
			}
			if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE)
			{
				running = false;
				break;
			}
			if (currentState == GameState::START_SCREEN)
			{
				// Wait for the player to press Spacebar to start
				if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_SPACE)
				{
					currentState = GameState::PLAYING;

					// Reset ball and paddles 
					ball.resetPosition();
					player.resetPosition();
					bot.resetPosition();
				}
			}
		}
		

		if (currentState == GameState::PLAYING)
		{
			// handle player movement
			player.move(keys, deltaTime, state);

			//handle ball movement
			int moveResult = ball.move(player, deltaTime, state, bot); // 1 -> bot won , -1 -> player won

			if (moveResult == 1)
			{
				botScore++;
				ball.resetPosition();
				player.resetPosition();
				bot.resetPosition();
				std::cout << ball.getXVelocity() << "--" << ball.getYVelocity() << "\n";
			}
			else if (moveResult == -1)
			{
				playerScore++;
				ball.resetPosition();
				player.resetPosition();
				bot.resetPosition();
				std::cout << ball.getXVelocity() << "--" << ball.getYVelocity() << "\n";
			}

			//handle bot movement
			bot.move(deltaTime, state, ball);
		}
		

		
		// Perform drawing commands - this makes the entire back buffer clear white
		SDL_SetRenderDrawColor(state.renderer, 196, 219, 122, 255);
		SDL_RenderClear(state.renderer);
		
		if (currentState == GameState::START_SCREEN)
		{
			text.startScreenText(state);
		}
		
		else if (currentState == GameState::PLAYING)
		{
			//draw ball, player, bot , score text
			player.drawItem(state, deltaTime);
			bot.drawItem(state, deltaTime);
			ball.drawItem(state, deltaTime);
			text.drawText(state, playerScore, botScore);
			drawMiddle(state);
		}
		
		// Swap buffers and present - this swaps the front buffer with the one we just drew and presents it
		SDL_RenderPresent(state.renderer);

		//update time
		prevTime = nowTime;
	}

	res.unload();
	cleanup(state);
	return 0;
}


// functions defs
bool init(SDLState& state)
{
	// init flag
	bool succes = true;

	// init SDL3
	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error initializing SDL3", nullptr);
		succes = false;
	}

	// create window
	state.window = SDL_CreateWindow("SDL3 first project", state.width, state.height, SDL_WINDOW_RESIZABLE);
	if (!state.window)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error creating window", state.window);
		cleanup(state);
		succes = false;
	}

	// create renderer
	state.renderer = SDL_CreateRenderer(state.window, nullptr);
	if (!state.renderer)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error creating renderer", state.window);
		succes = false;
	}

	// loading text
	if (TTF_Init() == false)
	{
		SDL_Log("SDL_ttf could not initialize! SDL_ttf error: %s\n", SDL_GetError());
		succes = false;
	}

	// CONFIGURE LOGICAL PRESENTATION
	SDL_SetRenderLogicalPresentation(state.renderer, state.logW, state.logH, SDL_LOGICAL_PRESENTATION_LETTERBOX); 
	// this pres style retains the 640X320 res regardless of the resizing of the window by introducing black bars
	return succes;
}
void cleanup(SDLState &state)
{
	SDL_DestroyRenderer(state.renderer);
	SDL_DestroyWindow(state.window);
	SDL_Quit();
}
void resetSet(Ball& ball, Player& player, Bot& bot)
{
	ball.resetPosition();
	player.resetPosition();
	bot.resetPosition();

	return;
}
void drawMiddle(SDLState& state) // draws the middle rectangles 
{
	// Set the render color 
	SDL_SetRenderDrawColor(state.renderer, 50, 100, 50, 0);

	// Define the dimensions of dashed rectangles
	float rectWidth = 15.0f;
	float rectHeight = 5.0f;
	float gap = 15.0f;

	// Calculate the true center Y position
	float centerY = (state.logH / 2.0f) - (rectHeight / 2.0f);

	// Loop from the left of the screen to the right
	for (float x = 0; x < state.logW; x += (rectWidth + gap))
	{
		SDL_FRect dashRect = { x, centerY, rectWidth, rectHeight };

		// Draw the individual rectangle
		SDL_RenderFillRect(state.renderer, &dashRect);
	}
}
