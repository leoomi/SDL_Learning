#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>

enum KeyPressSurfaces{
	KEY_PRESS_SUFACES_DEFAULT,
	KEY_PRESS_SUFACES_UP,
	KEY_PRESS_SUFACES_DOWN,
	KEY_PRESS_SUFACES_LEFT,
	KEY_PRESS_SUFACES_RIGHT,
	KEY_PRESS_SUFACES_TOTAL
};

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;

bool init();
bool loadMedia();
void close();
SDL_Surface* loadSurface(std::string path);
SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SUFACES_TOTAL];
SDL_Surface* gCurrentSurface = NULL;

int main (int argc, char* args[]){

	if(!init()){
		printf("Failed to initialize");
	}
	else{
		if(!loadMedia()){
			printf("Failed to load media!\n");
		}
		else{
			bool quit = false;
			SDL_Event e;
			gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SUFACES_DEFAULT];

			while(!quit){
				while(SDL_PollEvent(&e) != 0){
					if(e.type == SDL_QUIT){
						quit = true;
					}

					else if(e.type == SDL_KEYDOWN){
						switch(e.key.keysym.sym){
							case SDLK_UP:
							gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SUFACES_UP];
							break;

							case SDLK_DOWN:
							gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SUFACES_DOWN];
							break;

							case SDLK_LEFT:
							gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SUFACES_LEFT];
							break;

							case SDLK_RIGHT:
							gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SUFACES_RIGHT];
							break;

							default:
							gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SUFACES_DEFAULT];
							break;
						}
					}
				}

				SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, NULL);
				SDL_UpdateWindowSurface(gWindow);
			}
		}
	}

	close();

	return 0;
}

bool init(){
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}

	else {
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,
				SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
				SDL_WINDOW_SHOWN);
		if (gWindow == NULL) {
			printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else{
			gScreenSurface = SDL_GetWindowSurface(gWindow);
		}
	}

	return success;
}

bool loadMedia(){
	bool success = true;

	gKeyPressSurfaces[KEY_PRESS_SUFACES_DEFAULT] = SDL_LoadBMP("press.bmp");
	if(gKeyPressSurfaces[KEY_PRESS_SUFACES_DEFAULT] == NULL){
		printf("Unable to load default image! SDL Error: %s\n" , "x.bmp",SDL_GetError());
		success = false;
	}

	gKeyPressSurfaces[KEY_PRESS_SUFACES_UP] = SDL_LoadBMP("up.bmp");
	if(gKeyPressSurfaces[KEY_PRESS_SUFACES_UP] == NULL){
		printf("Unable to load up image! SDL Error: %s\n" , "x.bmp",SDL_GetError());
		success = false;
	}

	gKeyPressSurfaces[KEY_PRESS_SUFACES_DOWN] = SDL_LoadBMP("down.bmp");
	if(gKeyPressSurfaces[KEY_PRESS_SUFACES_DOWN] == NULL){
		printf("Unable to load down image! SDL Error: %s\n" , "x.bmp",SDL_GetError());
		success = false;
	}

	gKeyPressSurfaces[KEY_PRESS_SUFACES_LEFT] = SDL_LoadBMP("left.bmp");
	if(gKeyPressSurfaces[KEY_PRESS_SUFACES_LEFT] == NULL){
		printf("Unable to load left image! SDL Error: %s\n" , "x.bmp",SDL_GetError());
		success = false;
	}

	gKeyPressSurfaces[KEY_PRESS_SUFACES_RIGHT] = SDL_LoadBMP("right.bmp");
	if(gKeyPressSurfaces[KEY_PRESS_SUFACES_RIGHT] == NULL){
		printf("Unable to load right image! SDL Error: %s\n" , "x.bmp",SDL_GetError());
		success = false;
	}

	return success;
}

void close(){

	SDL_FreeSurface(gCurrentSurface);
	gCurrentSurface = NULL;

	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	SDL_Quit();
}

SDL_Surface* loadSurface(std::string path){
	SDL_Surface* temp = SDL_LoadBMP(path.c_str());
	if(temp == NULL){
		printf("Unable do load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
	}

	return temp;
}
