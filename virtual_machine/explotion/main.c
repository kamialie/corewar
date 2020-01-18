#include<math.h>
#include"SDL.h"
SDL_Window *w;
SDL_Surface*s;
SDL_Event e;
SDL_Rect p;
int i,n, r = 0;
double q[256];
main(){
	SDL_Init(SDL_INIT_VIDEO);
	w = SDL_CreateWindow("Corewar", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1000, 1000, SDL_WINDOW_SHOWN);
	s = SDL_GetWindowSurface(w);
	for(; e.type-SDL_QUIT; n=-~n%64) { // speed rather limit of animation
		for(i=256*!n; i ; q[--i]=rand()%65536*9.5874e-5); {
			SDL_FillRect(s,0,i=0); // clear view
			for(; i < 256 ; i++) {
				p.x = 560 + cos(q[i]) * q[i-1] * n / 10; // first number currects the position (middle), division controls the size
				p.y = 560 + sin(q[i]) * q[i-1] * n / 10; // first number currects the position (middle), division controls the size
				p.w = 2; // width of all little particles 
				p.h = 1; // height of all little particles
				SDL_FillRect(s,&p,0xFFFFFF << r++);// for colorful effect replace color with 0xFFFFFF << r++, original - -n*67372030
			}
		}
		SDL_UpdateWindowSurface(w);
		SDL_Delay(50);
		SDL_PollEvent(&e);
	}
}
/*int	main() {
	int n = 0;
	printf("%d %d\n", n, !n);
	return (0);
}*/
//gcc main.c -I ../../my_git/corewar/virtual_machine/include/SDL2/ -l SDL2 -L ../../my_git/corewar/virtual_machine/lib/
