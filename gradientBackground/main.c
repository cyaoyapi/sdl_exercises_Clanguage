/*
	This program draw a grandient background.
*/
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>

void pause();

int main(int argc, char *argv[]){

	SDL_Surface *screen = NULL, *lines[256] = {NULL};
	SDL_Rect position;
	int i = 0;

	// SDL Initialization
	if(SDL_Init(SDL_INIT_VIDEO) == -1){
		fprintf(stderr, "Error -> SDL initialization failed : %s\n",SDL_GetError());
		exit(EXIT_FAILURE);
	}

	screen = SDL_SetVideoMode(650, 256, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);	// Loading video mode
	if(screen == NULL){
		fprintf(stderr, "Error -> Video mode loading failed : %s",SDL_GetError());
		exit(EXIT_FAILURE);
	}

    SDL_WM_SetCaption("Grandient Background", NULL); // Window title

    // Drawing 256 rectangles
    position.x = 0;
    for(i = 255; i >= 0; i--){
        lines[i] = SDL_CreateRGBSurface(SDL_HWSURFACE, 650, 1, 32, 0, 0, 0, 0);
        position.y = i;
        SDL_FillRect(lines[i], NULL, SDL_MapRGB(screen->format, i, i, i));
        SDL_BlitSurface(lines[i], NULL, screen, &position);
    }

    SDL_Flip(screen); // Update the screen
	pause();

	// Free the memory
	for(i = 0; i < 256; i++){
        SDL_FreeSurface(lines[i]);
    }
	SDL_Quit();

    return EXIT_SUCCESS;
}


/*
Pause the program until the user clicks
the CLOSE button in the window.
*/
void pause(){
    int continuer = 1;
    SDL_Event event;
    while (continuer){
        SDL_WaitEvent(&event);
        switch(event.type){
            case SDL_QUIT:
                continuer = 0;
        }
    }
}
