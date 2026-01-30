#include "src/Graph.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
// https://www.youtube.com/watch?v=icZj67PTFhc

#define WIDTH 640
#define HEIGHT 480

void
setup(SDL_Window *window, SDL_Renderer *renderer, Graph& graph);

void
draw(SDL_Window *window, SDL_Renderer *renderer, Graph& graph);

int
main (int argc, char *argv[], char *envp[]) {
    if (SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    if (0==SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer)) {
        SDL_Event event;
        bool done = false;
        Graph graph(16,16);

        // Do your set up in the setup function.
        setup(window, renderer, graph);

        bool shift_pressed{false};
        bool ctrl_pressed{false};

        while (!done) {
            draw(window, renderer, graph);

            SDL_RenderPresent(renderer);

            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    done = SDL_TRUE;
                }
                if (event.type == SDL_MOUSEBUTTONUP) {
                    SDL_Point p;
                    p.x = event.button.x;
                    p.y = event.button.y;
                    auto n = graph.node_on_point(p);
                    if (n!= nullptr) {
                        if (shift_pressed) {
                            graph.set_start_node(n);
                        } else if(ctrl_pressed) {
                            graph.set_end_node(n);
                        } else {
                            n->node_type = (n->node_type == empty ? obstacle : empty);
                        }
                    }
                }
                if (event.type == SDL_KEYDOWN) {
                    std::cout << event.key.keysym.scancode << "\n";
                    if (event.key.keysym.scancode==225) {
                        shift_pressed = true;
                    }
                    if (event.key.keysym.scancode==224) {
                        ctrl_pressed = true;
                    }
                }
                if (event.type == SDL_KEYUP) {
                    if (event.key.keysym.scancode==225) {
                        shift_pressed = false;
                    }
                    if (event.key.keysym.scancode==224) {
                        ctrl_pressed = false;
                    }
                }

                graph.solve_astar();
            }
        }
    }

    // Clean up and quit SDL2
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

// draw and setup could be encapsulated in a class
void
setup([[maybe_unused]] SDL_Window *window, [[maybe_unused]] SDL_Renderer *renderer, [[maybe_unused]] Graph& graph) {
    // scene setup goes here
    std::cout << "setup done\n";
}

void
draw([[maybe_unused]] SDL_Window *window, SDL_Renderer *renderer, Graph& graph) {
    SDL_SetRenderDrawColor(renderer, 25, 188, 255, 200);
    SDL_RenderClear(renderer);
    graph.draw(renderer);
}
