#pragma once

#include "Graph.h"
#include "GridLayout.h"

# include <SDL2/SDL.h>

class GraphRenderer {
    GridLayout layout;
public:
    void draw(SDL_Renderer* renderer, Graph& graph);
    std::shared_ptr<Node> node_at(Graph &graph, int x_point, int y_point);
private:
    void draw_connections(SDL_Renderer*, Graph &);
    void draw_path(SDL_Renderer*, Graph&);
    void draw_nodes(SDL_Renderer*, Graph&);
};
