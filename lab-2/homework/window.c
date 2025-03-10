/* window.c */
#include <raylib.h>

int main()
{
	InitWindow(800, 600, "hello from Raylib");

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground((Color) { 255, 0, 255, 255 });
		EndDrawing();
	}

	CloseWindow();
	return 0;
}