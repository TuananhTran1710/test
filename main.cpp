#include "game_map.h"
#include "BaseObject.h"
#include "CommonFunc.h"



BaseObject g_background;

bool Init() {
	bool success = 1; 
	int ret = SDL_Init(SDL_INIT_VIDEO);
	if (ret < 0) return 0;
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	g_window = SDL_CreateWindow("test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (g_window == NULL) success = 0;
	else {
		g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
		if (g_screen == NULL) success = 0;
		else {
			SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);
			int imgFlag = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlag) && imgFlag)) {
				success = 0;
			}
		}
	}
	return success;
}

bool LoadBackground() {
	bool ret = g_background.LoadImg("img/background.png",g_screen);
	if (ret == 0) {
		return 0;
	}
	return 1;
}

void close() {
	g_background.Free();
	SDL_DestroyRenderer(g_screen);
	g_screen = NULL; 
	SDL_DestroyWindow(g_window);
	g_window = NULL; 
	IMG_Quit();
	SDL_Quit();
}

int main(int argv, char* arg[]) {
	if (!Init()) return -1;
	if (!LoadBackground()) return -1;

	GameMap game_map;
	//char c[] = "map/map01.dat";
	//std:: cout << c;
	//std:: string s = "map/map01.dat";
	
	game_map.LoadMap("map/map01.dat");
	game_map.LoadTiles(g_screen);

	bool quit = 0;
	while (!quit) {
		while (SDL_PollEvent(&g_event) != 0) {
			if (g_event.type == SDL_QUIT) {
				quit = 1;
			}
		}
		SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);
		SDL_RenderClear(g_screen); 
		g_background.Render(g_screen, NULL);

		game_map.DrawMap(g_screen);
		SDL_RenderPresent(g_screen);
	}
	close();
	
	return 0;
}



