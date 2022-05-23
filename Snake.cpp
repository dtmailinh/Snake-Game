#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

using namespace std;
const int scr_width =  36*24 + 1;
const int scr_height = 24*24 + 1;

void renderframe(SDL_Renderer* renderer, int w_size)
{
	SDL_SetRenderDrawColor(renderer, 95, 76, 11, 255);
	SDL_Rect rect1;
	rect1.w = scr_width;
	rect1.h = w_size;
	rect1.x = 0;
	rect1.y = 0;
	SDL_RenderFillRect(renderer, &rect1);
	SDL_Rect rect2;
	rect2.w = scr_width;
	rect2.h = w_size;
	rect2.x = 0;
	rect2.y = scr_height - 1 - w_size;
	SDL_RenderFillRect(renderer, &rect2);
	SDL_Rect rect3;
	rect3.w = w_size;
	rect3.h = scr_height;
	rect3.x = 0;
	rect3.y = 0;
	SDL_RenderFillRect(renderer, &rect3);
	SDL_Rect rect4;
	rect4.w = w_size;
	rect4.h = scr_height;
	rect4.x = scr_width - 1 - w_size;
	rect4.y = 0;
	SDL_RenderFillRect(renderer, &rect4);
	SDL_RenderPresent(renderer);
}
void renderSnake(SDL_Renderer* renderer, SDL_Rect Snake, int x, int y, int w_size, vector<int> &bodyX, vector<int> &bodyY, int bodyLength) {
	SDL_SetRenderDrawColor(renderer, 0, 200, 0, 255);

	// Gets x and y of all body blocks and renders them
	for (int i = 0; i < bodyLength; i++) {
		Snake.x = bodyX[i];
		Snake.y = bodyY[i];
		SDL_RenderFillRect(renderer, &Snake);
	}
	Snake.x = x;
	Snake.y = y;
	SDL_SetRenderDrawColor(renderer, 0, 150, 0, 255);
	SDL_RenderFillRect(renderer, &Snake);
}

void renderFood(SDL_Renderer*& renderer, SDL_Texture*& appleTexture, SDL_Rect food) {
	
	SDL_Rect desRect;
	desRect.x = food.x;
	desRect.y = food.y;
	desRect.w = 24;
	desRect.h = 24;

	SDL_RenderCopy(renderer, appleTexture, NULL, &desRect);
}

void renderScore(SDL_Renderer* renderer, int bodyLength, int w_size, int ww_size, TTF_Font* font) {
	SDL_Color White = {255,255,255 };

	// Get the font used for displaying text

	if (font == NULL) {
		cout << "Font loading error" << endl;
		return;
	}

	SDL_Surface* score = TTF_RenderText_Solid(font, (string("Score: ") + to_string(bodyLength * 10)).c_str(), White);
	SDL_Texture* scoreMessage = SDL_CreateTextureFromSurface(renderer, score);
	SDL_Rect scoreRect;
	scoreRect.w = 100;
	scoreRect.h = 30;
	scoreRect.x = ((scr_width / 2) - (scoreRect.w / 2));
	scoreRect.y = 0;
	SDL_RenderCopy(renderer, scoreMessage, NULL, &scoreRect);
	SDL_FreeSurface(score);
}

bool checkEatApple(int foodx, int foody, int Snakex, int Snakey) {

	if (Snakex == foodx && Snakey == foody) {
		return true;
	}

	return false;
}

pair<int, int> getNewFood(vector<int>& bodyX, vector<int>& bodyY, int SnakeX, int SnakeY, int w_size, int bodyLength) {
	bool check = true;
	int x = 0;
	int y = 0;

#define rnd(a,b) (rand()%(b-a+1)+a)
	
	do
	{
		check = true;
		x = rnd(1, w_size-2) * w_size;
		y = rnd(1, w_size-2) * w_size;
		for (int i = 0; i < bodyLength; i++) {
			if ((x == bodyX[i] && y == bodyY[i]) || (x == SnakeX && y == SnakeY)) {
				check = false;
			}
		}
	}while (x > scr_width - 2 * w_size || x < w_size || y < w_size || y > scr_height - 2 * w_size || check == false);

	pair<int, int> foodPos;
	foodPos = make_pair(x, y);

	return foodPos;
}

void gameOver(SDL_Renderer* renderer, SDL_Event event, int w_size, int bodyLength, int highscore, TTF_Font* font, Mix_Chunk* gameoversound) {
	SDL_Color Red = { 255, 0, 0 };
	SDL_Color White = { 255, 255, 255 };
	SDL_Color Black = { 0, 0, 0 };
	SDL_Color Blue = { 0, 0, 255 };

	// Get the font used for displaying text
	if (font == NULL) {
		cout << "Font loading error" << endl;
		return;
	}

	SDL_Surface* gameover = TTF_RenderText_Solid(font, "Game Over", Red);
	SDL_Surface* retry = TTF_RenderText_Solid(font, "Press Enter to retry", Blue);
	SDL_Surface* yourscore = TTF_RenderText_Solid(font, (string("Your Score: ") + to_string(bodyLength * 10)).c_str(), Black);
	SDL_Surface* writehighscore = TTF_RenderText_Solid(font, (string("High Score: ") + to_string(highscore)).c_str(), Black);
	SDL_Texture* gameoverMessage = SDL_CreateTextureFromSurface(renderer, gameover);
	SDL_Texture* retryMessage = SDL_CreateTextureFromSurface(renderer, retry);
	SDL_Texture* yourscoreMessage = SDL_CreateTextureFromSurface(renderer, yourscore);
	SDL_Texture* writehighscoreMessage = SDL_CreateTextureFromSurface(renderer, writehighscore);
	SDL_Rect gameoverRect;
	SDL_Rect retryRect;
	SDL_Rect yourscoreRect;
	SDL_Rect highscoreRect;

	gameoverRect.w = 200;
	gameoverRect.h = 100;
	gameoverRect.x = (scr_width / 2) - (gameoverRect.w / 2);
	gameoverRect.y = (scr_height/ 2) - (gameoverRect.h / 2) - 100;

	retryRect.w = 300;
	retryRect.h = 50;
	retryRect.x = (scr_width / 2) - (retryRect.w / 2);
	retryRect.y = ((scr_height / 2) - (retryRect.h / 2) + 200);

	highscoreRect.w = 150;
	highscoreRect.h = 30;
	highscoreRect.x = (scr_width / 2) - (highscoreRect.w / 2);
	highscoreRect.y = (scr_height / 2) - (highscoreRect.h / 2) + 50;

	yourscoreRect.w = 150;
	yourscoreRect.h = 30;
	yourscoreRect.x = (scr_width / 2) - (yourscoreRect.w / 2);
	yourscoreRect.y = (scr_height / 2) - (yourscoreRect.h / 2) + 100;

	SDL_RenderCopy(renderer, gameoverMessage, NULL, &gameoverRect);
	SDL_RenderCopy(renderer, retryMessage, NULL, &retryRect);
	SDL_RenderCopy(renderer, writehighscoreMessage, NULL, &highscoreRect);
	SDL_RenderCopy(renderer, yourscoreMessage, NULL, &yourscoreRect);
	renderframe(renderer, w_size);
	SDL_RenderPresent(renderer);
	Mix_PlayChannel(-1, gameoversound, 0);

	// Show game over screen while space has not been pressed
	while (true) {
		if (SDL_PollEvent(&event)) {

			if (event.type == SDL_QUIT) {
				exit(0);
			}

			if (event.key.keysym.scancode == SDL_SCANCODE_RETURN) {
				SDL_RenderClear(renderer);
				cout << "New game\n";
				SDL_FreeSurface(gameover);
				SDL_FreeSurface(retry);
				SDL_FreeSurface(yourscore);
				SDL_FreeSurface(writehighscore);
				
				return;
			}

		}

	}
	
}

void youWin(SDL_Renderer* renderer, SDL_Event event, int w_size, int bodyLength, TTF_Font* font) {
	SDL_Color Red = { 255, 0, 0 };
	SDL_Color White = { 255, 255, 255 };
	SDL_Color Black = { 0, 0, 0 };
	SDL_Color Yellow = { 255, 255, 0 };
	SDL_Color Blue = { 0, 0, 255 };

	// Get the font used for displaying text
	if (font == NULL) {
		cout << "Font loading error" << endl;
		return;
	}

	SDL_Surface* gameover = TTF_RenderText_Solid(font, "You win!", Red);
	SDL_Surface* retry = TTF_RenderText_Solid(font, "Press Enter to play again", Blue);
	SDL_Surface* score = TTF_RenderText_Solid(font, (string("Score: ") + to_string(bodyLength * 10)).c_str(), Black);
	SDL_Texture* gameoverMessage = SDL_CreateTextureFromSurface(renderer, gameover);
	SDL_Texture* retryMessage = SDL_CreateTextureFromSurface(renderer, retry);
	SDL_Texture* scoreMessage = SDL_CreateTextureFromSurface(renderer, score);
	SDL_Rect gameoverRect;
	SDL_Rect retryRect;
	SDL_Rect scoreRect;
	gameoverRect.w = 200;
	gameoverRect.h = 100;
	gameoverRect.x = (scr_width / 2) - (gameoverRect.w / 2);
	gameoverRect.y = (scr_height / 2) - (gameoverRect.h / 2) - 50;
	retryRect.w = 300;
	retryRect.h = 50;
	retryRect.x = (scr_width / 2) - ((retryRect.w / 2));
	retryRect.y = ((scr_height / 2) - ((retryRect.h / 2)) + 150);
	scoreRect.w = 100;
	scoreRect.h = 30;
	scoreRect.x = (scr_width / 2) - (scoreRect.w / 2);
	scoreRect.y = 20;
	SDL_RenderCopy(renderer, gameoverMessage, NULL, &gameoverRect);
	SDL_RenderCopy(renderer, retryMessage, NULL, &retryRect);
	SDL_RenderCopy(renderer, scoreMessage, NULL, &scoreRect);
	renderframe(renderer, w_size);
	// Show victory screen while space has not been pressed
	while (true) {
		SDL_RenderPresent(renderer);

		if (SDL_PollEvent(&event)) {

			if (event.type == SDL_QUIT) {
				exit(0);
			}

			if (event.key.keysym.scancode == SDL_SCANCODE_RETURN) {
				return;
			}

		}

	}

}

enum Direction {
	UP, DOWN, LEFT, RIGHT,
};
int keypress(SDL_Event& event, int& dir)
{
	if (event.key.keysym.sym == SDLK_DOWN) {
		if (dir != UP) dir = DOWN;
	}
	if (event.key.keysym.sym == SDLK_UP) {
		if (dir != DOWN) dir = UP;
	}
	if (event.key.keysym.sym == SDLK_LEFT) {
		if (dir != RIGHT) dir = LEFT;
	}
	if (event.key.keysym.sym == SDLK_RIGHT) {
		if (dir != LEFT) dir = RIGHT;
	}
	return dir;
}
int main(int argc, char* argv[]) {

	srand(time(0));

	// Init everything so we have everything
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		cout << "Unable to initialize SDL!Error: " << SDL_GetError() << endl;
	}

	// Init TTF and check for any errors
	if (TTF_Init() < 0) {
		cout << "SDL_TTF could not initialize! Error: " << TTF_GetError() << endl;
	}
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		cout << "SDL_Mixer could not initialize! Error: " << SDL_GetError() << endl;;
	}

	SDL_Surface* tempSurface = SDL_LoadBMP("apple.bmp");
	SDL_Event event;
	TTF_Font* font = TTF_OpenFont((char*)"arial.ttf", 10);
	Mix_Chunk* gameoversound = NULL;
	Mix_Chunk* eatapple = NULL;

	eatapple = Mix_LoadWAV("music/eat_apple_sound.wav");
	if (eatapple == NULL)
	{
		cout << "Failed to load eat music! Error: " << SDL_GetError() << endl;
	}
	gameoversound = Mix_LoadWAV("music/gameover_sound.wav");
	if (gameoversound == NULL)
	{
		cout << "Failed to load gameover music! Error: " << SDL_GetError() << endl;
	} 
	int countframe = 0;
	const int FPS = 10;
	const int DELAY_TIME = 1000 / FPS;
	Uint32 frameStart;
	Uint32 frameTime;

	// size of one block
	int w_size = 24;
	int highscore = 0;

	// This is the Snake rectangle
	SDL_Rect Snake;
	Snake.x = w_size*5 ;
	Snake.y = w_size*4;
	Snake.h = w_size;
	Snake.w = w_size;

	// bodyLength is snake's length, incremented every time the snake eats food
	int bodyLength = 0;

	// Vectors for storage of body block positions
	vector<int> bodyX;
	vector<int> bodyY;

	// Snake position variables
	int x = w_size * 5;
	int y = w_size * 4;
	
	// Food rectangle
	SDL_Rect Apple;
	Apple.w = w_size;
	Apple.h = w_size;
	Apple.x = 0;
	Apple.y = 0;

	pair<int, int> foodPos = getNewFood(bodyX, bodyY, x, y, w_size, bodyLength);
	Apple.x = foodPos.first;
	Apple.y = foodPos.second;

	SDL_Window* window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, scr_width,scr_height, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Texture* appleTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);

	int dir = -1;
	// Main game loop, this constantly runs and keeps everything updated
	int prevX = 0;
	int prevY = 0;

	while (true) {
		
		frameStart = SDL_GetTicks();
		
		// Check win condition, body needs to fill all tiles
		if (bodyLength >= (scr_width/w_size)*(scr_height/w_size) - 1) {
			youWin(renderer, event, w_size, bodyLength, font);
			x = w_size * 5;
			y = w_size * 4;
			dir = -1;
			bodyX.clear();
			bodyY.clear();
			bodyLength = 0;
			foodPos = getNewFood(bodyX, bodyY, x, y, w_size, bodyLength);
			Apple.x = foodPos.first;
			Apple.y = foodPos.second;
		}

		// Controls
		if (SDL_PollEvent(&event)) {

			// Simply exit the program when told to
			if (event.type == SDL_QUIT) {
				exit(0);
			}

			// If a key is pressed
			if (event.type == SDL_KEYDOWN ) {
				keypress(event, dir);
			}
		}

		// The previous position of the Snake block
		prevX = x;
		prevY = y;

		if (dir == UP) {
			y -= w_size ;
		}
		else if (dir == LEFT) {
			x -= w_size;
		}
		else if (dir == RIGHT) {
			x += w_size;
		}
		else if (dir == DOWN) {
			y += w_size;
		}

		// Collision detection, has played collided with food?
		if (checkEatApple(Apple.x, Apple.y, x, y)) {
			Mix_PlayChannel(-1, eatapple, 0);
			// random new food after it has been eaten
			foodPos = getNewFood(bodyX, bodyY, x, y, w_size, bodyLength);
			Apple.x = foodPos.first;
			Apple.y = foodPos.second;
			bodyLength++;
		}

		// Update body size and position
		if (bodyX.size() < bodyLength) {
			bodyX.push_back(prevX);
			bodyY.push_back(prevY);
		}

		//Loop through every body block, move all blocks to the nearest block in front
		//This updates the blocks from end (farthest from Snake block) to the start (nearest to Snake block)
		for (int i = 0; i < bodyLength; i++) {

			if (i > 0) {
				bodyX[i - 1] = bodyX[i];
				bodyY[i - 1] = bodyY[i];
			}

		}

		if (bodyLength > 0) {
			bodyX[bodyLength - 1] = prevX;
			bodyY[bodyLength - 1] = prevY;
		}

		// Game over if Snake has collided with a body block, also reset everything
		for (int i = 0; i < bodyLength; i++) {

			if (x == bodyX[i] && y == bodyY[i]) {
				highscore = (bodyLength * 10 > highscore) ? bodyLength * 10 : highscore;
				SDL_Delay(1000);
				cout << "Snake has collided with a body block\n";
				gameOver(renderer, event, w_size, bodyLength, highscore, font, gameoversound);

				x = w_size * 5;
				y = w_size * 4;
				dir = -1;
				bodyX.clear();
				bodyY.clear();
				bodyLength = 0;

				foodPos = getNewFood(bodyX, bodyY, x, y, w_size, bodyLength);
				Apple.x = foodPos.first;
				Apple.y = foodPos.second;
			}

		}

		// Game over if Snake out of bounds, also resets the game state
		if (x < w_size || y < w_size || x > scr_width - 2*w_size || y > scr_height - 2*w_size) {
			highscore = (bodyLength * 10 > highscore) ? bodyLength * 10 : highscore;
			SDL_Delay(1000);
			gameOver(renderer, event, w_size, bodyLength, highscore, font, gameoversound);
			x = w_size * 5;
			y = w_size * 4;
			dir = -1;
			bodyX.clear();
			bodyY.clear();
			bodyLength = 0;
			
			foodPos = getNewFood(bodyX, bodyY, x, y, w_size, bodyLength);
			Apple.x = foodPos.first;
			Apple.y = foodPos.second;
		}

		// Render everything
		renderframe(renderer, w_size);
		renderSnake(renderer, Snake, x, y, w_size, bodyX, bodyY, bodyLength);
		renderScore(renderer, bodyLength, w_size, w_size, font);
		renderFood(renderer, appleTexture, Apple);
		/*SDL_Log("Nowtime: %d", frameStart);
		SDL_Log("Frame :%d", countframe++);*/
		SDL_RenderPresent(renderer);
		SDL_SetRenderDrawColor(renderer, 243, 226, 169, 0);
		SDL_RenderClear(renderer);
	
		frameTime = SDL_GetTicks() - frameStart;
		if (frameTime < DELAY_TIME)
		{
			SDL_Delay(DELAY_TIME - frameTime);
		}
		
	}

	SDL_DestroyWindow(window);

	TTF_Quit();

	SDL_Quit();

	return 0;

}
