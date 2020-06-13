#pragma once
#include <memory>
#include <vector>
#include <SDL2/SDL.h>

enum Node_Type {empty, start, end, obstacle};
struct Node {
    int node_size{23};
    int node_border{5};

    Node_Type node_type{empty};

    bool visited{false};
    float global_goal{0};
    float local_goal{0};
    int x;
    int y;
    std::vector<std::shared_ptr<Node>> neighbours;
    std::shared_ptr<Node> parent;

public:
    int to_pos(int x) {
        return this->node_border + (this->node_size + this->node_border) * x;
    }

    bool contains_point(const SDL_Point& p) {
        SDL_Rect r;
        r.x = this->x * (this->node_size + this->node_border) + this->node_border;
        r.y = this->y * (this->node_size + this->node_border) + this->node_border;
        r.w = r.h = node_size;
        return SDL_PointInRect(&p, &r);
    }

    void draw(SDL_Renderer *renderer) {
        if (this->node_type==empty) {
            SDL_SetRenderDrawColor(renderer, 25, 18, 255, 200);
        } else if (this->node_type==start) {
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 200);
        } else if (this->node_type==end) {
            SDL_SetRenderDrawColor(renderer, 255, 0, 25, 200);
        } else if (this->node_type==obstacle){
            SDL_SetRenderDrawColor(renderer, 0, 18, 0, 200);
        }

        if (this->visited && this->node_type == empty) {
            SDL_SetRenderDrawColor(renderer, 100, 100, 255, 255);
        }


        SDL_Rect rct;
        rct.x = to_pos(this->x);
        rct.y = to_pos(this->y);
        rct.h = node_size;
        rct.w = node_size;
        SDL_RenderFillRect(renderer, &rct);
    }
};
