#include "raylib.h"
//#include "objects.h"
const int cell_size = 20;
const int scr_width = 600;
const int scr_height = 600;
Vector2 offset = { 0 };
bool gameOver, pause;
int score = 0;

struct Snake
{
	int size, l0, len; //i - number of tail cells; size instead width/height because it'll be square
	int* tail = new int[len];
	Vector2 pos = {0};
	Vector2 speed = {0};
	Color color;


	int TailCount();
	void DrawIt();
	void Move(Snake s)
	{
		if (IsKeyPressed(KEY_RIGHT)) pos.x += 2.0f;
		if (IsKeyPressed(KEY_LEFT)) pos.x -= 2.0f;
		if (IsKeyPressed(KEY_UP)) pos.y -= 2.0f;
		if (IsKeyPressed(KEY_DOWN)) pos.y += 2.0f;
		//-------------------------------------------------
	};
	bool Eat(Snake s, bool isEaten, int score)
	{

		score += 1;
		isEaten = true;
		return isEaten;
	};
	void Collide(Snake s);
};
struct Food
{
	int size, counter; //counter считает кол-во еды на поле, и если ее нет, генерирует новую
	Vector2 pos = { 0 };
	Color color;
	bool isEaten;

	void Draw();
	void IsEaten();
};
int main(Snake&, Food&)
{
	InitWindow(scr_width, scr_height, "Snake");
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);

		EndDrawing();
	}
	CloseWindow();
	return 0;
}
---------------------------------------------------------------------------------------------------------------------
/*
// Collision with yourself
void Collide(Snake snake, )
{for (int i = 1; i < counterTail; i++)
{
	if ((snake[0].position.x == snake[i].position.x) && (snake[0].position.y == snake[i].position.y)) gameOver = true;
}}

// Wall behaviour
if ((snake[0].position.x) > (screenWidth - offset.x)) { snake[0].position.x = 0;}
else if ((snake[0].position.y) > (screenHeight - offset.y)) { snake[0].position.y = 0;}
else if snake[0].position.x < 0 { snake[0].position.x = screenWidth; }
else (snake[0].position.y < 0) { snake[0].position.y = screenHeight; } */
bool IsKeyPressed(int key);	// Check if a key has been pressed once
bool IsMouseButtonPressed(int button); // Check if a mouse button has been pressed once

struct Snake
{
	void DrawIt(Snake snake);
	void Move(Snake snake);
	void Eat(bool isEaten, int score) { if (/*snakes position is the same as food*/) { isEaten = true; score += 1; } };
	void Collide();
};
struct Food
{
	int size, counter; //counter считает кол-во еды на поле, и если ее нет, генерирует новую
	int posX, posY;
	Color color;
	bool isEaten = false;

	void Draw();
	void IsEaten() { if (isEaten == true) {/*clears food */ isEaten = false; Draw(); } else break; };
};