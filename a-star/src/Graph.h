#pragma once
#include "Node.h"
#include <memory>
#include <SDL2/SDL.h>
#include <iostream>
#include <list>

class Graph {
    int n_map_width{16};
    int n_map_height{16};

    std::vector<std::shared_ptr<Node>> nodes;
    std::shared_ptr<Node> node_start;
    std::shared_ptr<Node> node_end;

    void draw_connections(SDL_Renderer *renderer);

    void draw_path(SDL_Renderer *renderer);

    void draw_nodes(SDL_Renderer *renderer);

    void reset_nodes();

public:
    explicit Graph(int width = 16, int height = 16);

    std::vector<std::shared_ptr<Node>> get_nodes();

    std::shared_ptr<Node> node_on_point(const SDL_Point &p);

    void solve_astar(bool best_path = true);

    void draw(SDL_Renderer *renderer);

    void set_start_node(const std::shared_ptr<Node> &n);

    void set_end_node(const std::shared_ptr<Node> &n);
};
