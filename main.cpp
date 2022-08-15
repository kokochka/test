#include "raylib.h"
#include <stdlib.h> 

const int scr_width = 600;
const int scr_height = 600;
const int block_size = 20;
const int max_tail = 100;

static bool gameOver = false, pause = false, isEaten = false, allowMove = false;
struct Snake
{
	Vector2 size = { 0 };
	Vector2 position = { 0 };
	Vector2 speed = { 0 };
	Color color;
};

struct Food
{
	Vector2 size = { 0 };
	Vector2 position = { 0 };
	Color color = YELLOW;
	bool isEaten = false;
};
static Food fruit = { 0 };
static Snake snake[max_tail] = { 0 };
static Vector2 snake_pos[max_tail] = { 0 };
static Vector2 offset = { 0 };
static int len_tail = 0, frame_counter = 0, score;
enum GameScreen { MAIN_MENU, GAME_MODE, PAUSE, RULES,GAME_OVER,WIN_GAME, EXIT };

//FUNCTIONS
void InitGame(void);
void UpdateGame(void);
void DrawGame(void);
//FUNC


int main()
{
	InitWindow(scr_width, scr_height, "Snake");
	GameScreen current_screen = MAIN_MENU;
	InitGame();
	SetTargetFPS(100);

	while (!WindowShouldClose())
	{
		switch (current_screen)
		{
		case (MAIN_MENU):
		{
			if (IsKeyPressed(KEY_ENTER)) current_screen = GAME_MODE;
			if (IsKeyPressed(KEY_I)) current_screen = RULES;
		}
		case (GAME_MODE):
		{
			if (IsKeyPressed(KEY_P))
			{
				pause = true; current_screen = PAUSE;
			}
			if (gameOver) current_screen = GAME_OVER;
			if (score == 100) current_screen = WIN_GAME;
		}break;
		case (PAUSE):
		{
			if (IsKeyPressed(KEY_ENTER))
			{
				pause = false;
				current_screen = GAME_MODE;
			}
			if (IsKeyPressed(KEY_I)) current_screen = RULES;
		}break;
		case (RULES):
		{
			if (IsKeyPressed(KEY_ENTER)) current_screen = GAME_MODE;
			if (IsKeyPressed(KEY_I)) current_screen = MAIN_MENU;
		}break;
		case (GAME_OVER):
		{
			gameOver = false;
			if (IsKeyPressed(KEY_ENTER))
			{
				current_screen = MAIN_MENU;
				InitGame();
			}
		}break;
		case (WIN_GAME):
		{
			gameOver = false;
			if (IsKeyPressed(KEY_ENTER))
			{
				current_screen = MAIN_MENU;
				InitGame();
			}
		}break;
		}
		BeginDrawing();
		ClearBackground(BLACK);
		//Draw windows
		switch (current_screen)
		{
		case (MAIN_MENU):
		{
			DrawRectangle(0, 0, scr_width, scr_height, PURPLE);
			DrawText("MAIN MENU", 40, 40, 40, YELLOW);
			DrawText("START GAME", 40, 120, 40, WHITE); DrawText("click ENTER", 330, 130, 20, LIGHTGRAY);
			DrawText("INSTRUCTIONS", 40, 200, 40, WHITE); DrawText("click I", 370, 210, 20, LIGHTGRAY);
			DrawText("EXIT", 40, 280, 40, WHITE); DrawText("click ESCAPE", 150, 290, 20, LIGHTGRAY);
		}break;
		case (GAME_MODE):
		{
			DrawRectangle(0, 0, scr_width, scr_height, BLACK);
			//DRAW SNAKE AND FOOD HERE
			UpdateGame();
			DrawRectangleV(fruit.position, fruit.size, fruit.color);
			for (int i = 0; i < len_tail; i++) DrawRectangleV(snake[i].position, snake[i].size, snake[i].color);
			//DRAW
			DrawText(TextFormat("SCORE: %i", score), 10, 10, 30, PURPLE);
			DrawText("PAUSE", scr_width - 110, 10, 30, PURPLE);
			DrawText("click P", scr_width - 170, 20, 15, LIGHTGRAY);
			
		}break;
		case (PAUSE):
		{
			DrawRectangle(0, 0, scr_width, scr_height, PURPLE);
			DrawText("CONTINUE", 40, 120, 40, WHITE); DrawText("click ENTER", 290, 130, 20, LIGHTGRAY);
			DrawText("INSTRUCTIONS", 40, 200, 40, WHITE); DrawText("click I", 370, 210, 20, LIGHTGRAY);
			DrawText("EXIT", 40, 280, 40, WHITE); DrawText("click ESCAPE", 150, 290, 20, LIGHTGRAY);
		}break;
		case (RULES):
		{
			DrawRectangle(0, 0, scr_width, scr_height, PURPLE);
			DrawText("INSTRUCTIONS", 40, 40, 40, YELLOW);
			DrawText("1. Control with keys 'UP', 'LEFT', 'RIGHT', 'DOWN'", 40, 120, 20, WHITE);
			DrawText("2. You'll fail if snake collides by itself", 40, 160, 20, WHITE);
			DrawText("3. You'll win if snake reaches 100 fruits", 40, 200, 20, WHITE);
			DrawText("4. Just have fun :)", 40, 240, 20, WHITE);
			DrawText("GO TO GAME", 40, scr_height - 100, 30, WHITE); DrawText("click ENTER", 250, scr_height - 95, 20, LIGHTGRAY);
			DrawText("MAIN MENU", 40, scr_height - 60, 30, WHITE); DrawText("click I", 230, scr_height - 55, 20, LIGHTGRAY);
		}break;
		case (GAME_OVER):
		{
			DrawRectangle(0, 0, scr_width, scr_height, BLACK);
			DrawText("GAME OVER", scr_width / 2 - 150, scr_height / 2 - 90, 50, WHITE);
			DrawText(TextFormat("SCORE: %i", score), scr_width / 2 - 90, scr_height / 2 - 20, 40, PURPLE);
			DrawText("GO TO START", scr_width / 2 - 100, scr_height / 2 + 50, 30, WHITE);
			DrawText("click ENTER", scr_width / 2 - 100, scr_height / 2 + 80, 20, LIGHTGRAY);
			DrawText("EXIT", scr_width / 2 - 100, scr_height / 2 + 120, 30, WHITE);
			DrawText("click ESCAPE", scr_width / 2 - 100, scr_height / 2 + 150, 20, LIGHTGRAY);
		}break;
		case (WIN_GAME):
		{
			DrawRectangle(0, 0, scr_width, scr_height, BLACK);
			DrawText("CONGRATULATIONS!", scr_width / 2 - 220, scr_height / 2 - 90, 45, WHITE);
			DrawText(TextFormat("SCORE: %i", score), scr_width / 2 - 90, scr_height / 2 - 20, 40, PURPLE);
			DrawText("GO TO START", scr_width / 2 - 100, scr_height / 2 + 50, 30, WHITE);
			DrawText("click ENTER", scr_width / 2 - 100, scr_height / 2 + 80, 20, LIGHTGRAY);
			DrawText("EXIT", scr_width / 2 - 100, scr_height / 2 + 120, 30, WHITE);
			DrawText("click ESCAPE", scr_width / 2 - 100, scr_height / 2 + 150, 20, LIGHTGRAY);
		}break;
		}
		EndDrawing();
	}
		CloseWindow();
		return 0;
}



void InitGame(void)
{
	pause = false; gameOver = false;
	len_tail = 1; score = 0;
	offset.x = scr_width % block_size;
	offset.y = scr_height % block_size;

	for (int i = 0; i < max_tail; i++)
	{
		snake[i].position.x = offset.x / 2; snake[i].position.y = offset.y / 2;
		snake[i].size.x = block_size; snake[i].size.y = block_size;
		snake[i].speed.x = block_size; snake[i].speed.y = 0;
		snake[i].color = WHITE;
	}
	for (int i = 0; i < max_tail; i++)
	{
		snake_pos[i] = { offset.x, offset.y };
	}

	fruit.size = { block_size, block_size };
	fruit.color = YELLOW;
	fruit.isEaten = true;

};

void UpdateGame(void)
{
	if (!gameOver)
	{
		if (!pause)
		{
			// Player control
			
			if (IsKeyPressed(KEY_RIGHT) && (snake[0].speed.x == 0) && allowMove)
			{
				snake[0].speed = { block_size/4, 0 };
				allowMove = false;
			}
			if (IsKeyPressed(KEY_LEFT) && (snake[0].speed.x == 0) && allowMove)
			{
				snake[0].speed = { -block_size/4, 0 };
				allowMove = false;
			}
			if (IsKeyPressed(KEY_UP) && (snake[0].speed.y == 0) && allowMove)
			{
				snake[0].speed = { 0, -block_size/4 };
				allowMove = false;
			}
			if (IsKeyPressed(KEY_DOWN) && (snake[0].speed.y == 0) && allowMove)
			{
				snake[0].speed = { 0, block_size/4 };
				allowMove = false;
			}

			// Snake movement
			for (int i = 0; i < len_tail; i++)
			{
				snake_pos[i] = snake[i].position;
			}
				if ((frame_counter % 5) == 0)
				{
					for (int i = 0; i < len_tail; i++)
					{
						if (i == 0)
						{
							snake[0].position.x += snake[0].speed.x;
							snake[0].position.y += snake[0].speed.y;
							allowMove = true;
						}
						else snake[i].position = snake_pos[i - 1];
					}
				}

				// Wall behaviour
				if ((snake[0].position.x) > (scr_width - 20)) { snake[0].position.x = 0; };
				if ((snake[0].position.y) > (scr_height - 20)) { snake[0].position.y = 30; }
				if (snake[0].position.x < 0) { snake[0].position.x = scr_width - 20;}
				if (snake[0].position.y < 30) { snake[0].position.y = scr_height - 20; }
				
				

				// Collision with yourself
				for (int i = 1; i < len_tail; i++)
				{
					if ((snake[0].position.x == snake[i].position.x) && (snake[0].position.y == snake[i].position.y)) gameOver = true;
				}
			
			// Fruit position calculation
			if (fruit.isEaten)
			{
				fruit.position.x = rand() % (scr_width - 2*block_size)+20;
				fruit.position.y = rand() % (scr_height - 2*block_size)+20;
				for (int i = 0; i < len_tail; i++)
				{
					if ((fruit.position.x == snake[i].position.x) && (fruit.position.y == snake[i].position.y))
					{
						fruit.position.x = rand() % (scr_width - 2*block_size)+20;
						fruit.position.y = rand() % (scr_height - 2*block_size)+50;
					}
				}
				fruit.isEaten = false;
			}

			// Collision
			if ((snake[0].position.x < (fruit.position.x + fruit.size.x) && (snake[0].position.x + snake[0].size.x) > fruit.position.x) &&
				(snake[0].position.y < (fruit.position.y + fruit.size.y) && (snake[0].position.y + snake[0].size.y) > fruit.position.y))
			{
				snake_pos[len_tail] = snake[len_tail - 1].position;
				len_tail += 1;
				score += 1;
				fruit.isEaten = true;
			}
			frame_counter++;
		}
	}
};



