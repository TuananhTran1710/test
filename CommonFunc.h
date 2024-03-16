
#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include <string>
#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <fstream>
#include <chrono>
#include <thread>

static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event; 

const int FRAME_PER_SECOND = 24;  //fps 


const int SCREEN_WIDTH = 880;
const int SCREEN_HEIGHT = 690;
const int SCREEN_BPP = 32;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175; 
const int COLOR_KEY_B = 180; 

const int COLOR_R = 96;
const int COLOR_G = 102;
const int COLOR_B = 253; 


#define TILE_SIZE 45

#define MAX_MAP_X 15
#define MAX_MAP_Y 15

#define BLANK_TILE 0 //  gi� tr? ?ng voi � kh�ng ?i ???c


typedef struct Map {
	int start_x, start_y;
	int max_x, max_y;
	int tile[MAX_MAP_Y][MAX_MAP_X];
	char* file_name;
};


typedef struct Input {
	int left, right, up, down; 
};


#endif