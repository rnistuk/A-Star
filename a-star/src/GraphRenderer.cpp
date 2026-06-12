#include "GraphRenderer.h"

#include <unordered_map>

namespace {
    const std::unordered_map<Node_Type, SDL_Color> node_colors = {
        {empty, {25, 18, 255, 200}},
        {start, {0, 255, 0, 200}},
        {end, {255, 0, 25, 200}},
        {obstacle, {0, 18, 0, 200}}
    };
    const SDL_Color visited_color = {100, 100, 255, 255};
}

void GraphRenderer::draw(SDL_Renderer* renderer, Graph& graph) {
    this->draw_connections(renderer, graph);
    this->draw_nodes(renderer, graph);
    this->draw_path(renderer, graph);
}

std::shared_ptr<Node> GraphRenderer::node_at(Graph &graph, int x_point, int y_point) {
    for (const auto &n : graph.get_nodes()) {
        if (layout.node_contains_point(n->x, n->y, x_point, y_point))
            return n;
    }
    return nullptr;
}

void GraphRenderer::draw_connections(SDL_Renderer* renderer, Graph &graph) {
    SDL_SetRenderDrawColor(renderer, 255, 18, 25, 200);
    for(const auto &n : graph.get_nodes()) {
        for (const auto &nn : n->neighbours) {
            if (nn && nn->node_type!=obstacle && n->node_type!=obstacle)
                SDL_RenderDrawLine(
                    renderer
                    , layout.center(n->x)
                    , layout.center(n->y)
                    , layout.center(nn->x)
                    , layout.center(nn->y));
        }
    }
}

void GraphRenderer::draw_nodes(SDL_Renderer* renderer, Graph& graph) {
   for (const auto& n : graph.get_nodes()) {
        SDL_Color c = node_colors.at(n->node_type);
        if (n->visited && n->node_type == empty)
            c = visited_color;

        SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
        SDL_Rect rct;
        rct.x = layout.to_pos(n->x);
        rct.y = layout.to_pos(n->y);
        rct.h = layout.node_size;
        rct.w = layout.node_size;
        SDL_RenderFillRect(renderer, &rct);
    }
}

void GraphRenderer::draw_path(SDL_Renderer* renderer, const Graph &graph) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 200);
    auto p{ graph.get_end_node() };
    while(p->parent != nullptr) {
        SDL_RenderDrawLine(
                renderer
                , layout.center(p->x)
                , layout.center(p->y)
                , layout.center(p->parent->x)
                , layout.center(p->parent->y));
        p = p->parent;
    }
}
