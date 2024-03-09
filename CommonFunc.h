
#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include <string>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <fstream>

static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event; 

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640; 
const int SCREEN_BPP = 32;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175; 
const int COLOR_KEY_B = 180; 

#define TILE_SIZE 64 

#define MAX_MAP_X 400 
#define MAX_MAP_Y 10 
typedef struct Map {
	int start_x, start_y;
	int max_x, max_y;
	int tile[MAX_MAP_Y][MAX_MAP_X];
	char* file_name;
};


#endif