#include "Graph.h"

#include <cfloat>

Graph::Graph(int width, int height) : n_map_width(width), n_map_height(height) {
    this->nodes.resize(static_cast<unsigned long>(this->n_map_width * this->n_map_height));
    int i{0};
    for(auto &n : nodes) {
        n = std::make_shared<Node>();
        n->x = i % this->n_map_width;
        n->y = i / this->n_map_height;
        ++i;
    }

    for (auto &n : nodes) {
        // set North-West-South and East neighbors.
        if (n->x>0) {
            n->neighbours.push_back(this->nodes[ n->y * this->n_map_width + n->x - 1]);
        }
        if (n->x < this->n_map_width - 1) {
            n->neighbours.push_back(this->nodes[ n->y * this->n_map_width + n->x + 1]);
        }
        if (n->y > 0) {
            n->neighbours.push_back(this->nodes[(n->y-1) * this->n_map_width + n->x]);
        }
        if (n->y < this->n_map_height - 1) {
            n->neighbours.push_back(this->nodes[(n->y+1) * this->n_map_width + n->x]);
        }

        // set diagonal neighbors
        if (n->x > 0 && n->y > 0) {
            n->neighbours.push_back(this->nodes[ (n->y - 1) * this->n_map_width + n->x - 1]);
        }
        if (n->x < this->n_map_width - 1 && n->y < this->n_map_height - 1 ) {
            n->neighbours.push_back(this->nodes[ (n->y + 1) * this->n_map_width + n->x + 1]);
        }
        if (n->x > 0 && n->y < this->n_map_height - 1) {
            n->neighbours.push_back(this->nodes[ (n->y + 1) * this->n_map_width + n->x - 1]);
        }

        if (n->x < this->n_map_width - 1 && n->y > 0 ) {
            n->neighbours.push_back(this->nodes[ (n->y - 1) * this->n_map_width + n->x + 1]);
        }
    }

    this->set_start_node(this->nodes.front());
    this->set_end_node(this->nodes.back());
}

std::vector<std::shared_ptr<Node>>
Graph::get_nodes() {return this->nodes;}

std::shared_ptr<Node>
Graph::node_on_point(const SDL_Point &p) {
    for (auto &n : this->nodes) {
        if (n->contains_point(p)) {
            return n;
        }
    }
    return nullptr;
}

void
Graph::set_start_node(const std::shared_ptr<Node> &n) {
    if (nullptr != this->node_start) {
        this->node_start->node_type = empty;
    }
    n->node_type = start;
    this->node_start = n;
};

void
Graph::set_end_node(const std::shared_ptr<Node> &n) {
    if (nullptr != this->node_end) {
        this->node_end->node_type = empty;
    }
    n->node_type = end;
    this->node_end = n;
};

void Graph::reset_nodes() {
    for (auto n : this->nodes) {
        n->visited = false;
        n->global_goal = FLT_MAX;
        n->local_goal = FLT_MAX;
        n->parent = nullptr;
    }
}


void
Graph::solve_astar(bool best_path) {
    auto distance = [] (const std::shared_ptr<Node> a, const std::shared_ptr<Node> b)
    {
        float dx = a->x - b->x;
        float dy = a->y - b->y;
        return sqrt(dx*dx + dy*dy);
    };
    auto heuristic = [distance] (const std::shared_ptr<Node> a, const std::shared_ptr<Node> b){
        return distance(a,b);
    };

    this->reset_nodes();

    auto node_current = node_start;
    node_start->local_goal = 0.0f;
    node_start->global_goal = heuristic(node_start, node_end);

    std::list<std::shared_ptr<Node>> not_tested;
    not_tested.push_back(node_start);

    while(!not_tested.empty()) {
        if (!best_path && node_current == node_end) {
            return;
        }
        not_tested.sort([](std::shared_ptr<Node> lhs, std::shared_ptr<Node> rhs){
            return lhs->global_goal < rhs->global_goal;
        });

        while (!not_tested.empty() && not_tested.front()->visited) {
            not_tested.pop_front();
        }

        if (not_tested.empty()) {
            break;
        }

        node_current = not_tested.front();
        node_current->visited = true;
        for (auto  nn : node_current->neighbours) {
            if (!nn->visited && nn->node_type != obstacle) {
                not_tested.push_back(nn);
            }
            float possibly_lower_goal = node_current->local_goal + distance(node_current, nn);
            if (possibly_lower_goal < nn->local_goal) {
                nn->parent = node_current;
                nn->local_goal = possibly_lower_goal;
                nn->global_goal = nn->local_goal + heuristic(nn, node_end);
            }
        }
    }
}

void
Graph::draw_connections(SDL_Renderer *renderer) {
    auto to_pos = [&](int x){return this->get_nodes()[0]->to_pos(x) + this->get_nodes()[0]->node_size/2;};
    SDL_SetRenderDrawColor(renderer, 255, 18, 25, 200);
    for(const auto &n : this->get_nodes()) {
        for (const auto &nn : n->neighbours) {
            if (nn && nn->node_type!=obstacle && n->node_type!=obstacle)
                SDL_RenderDrawLine(renderer, to_pos(n->x), to_pos(n->y), to_pos(nn->x), to_pos(nn->y));
        }
    }

}

void
Graph::draw_path(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 200);
    auto p{node_end};
    int size_adjust{p->node_size + p->node_border};
    while(p->parent != nullptr) {
        SDL_RenderDrawLine(
                renderer,
                p->x * size_adjust + size_adjust/2, p->y * size_adjust + size_adjust/2,
                p->parent->x * size_adjust + size_adjust/2, p->parent->y * size_adjust + size_adjust/2
        );
        p = p->parent;
    }
}

void
Graph::draw_nodes(SDL_Renderer *renderer) {
    for (auto n : this->nodes) {
        n->draw(renderer);
    }
}

void
Graph::draw(SDL_Renderer *renderer) {
    this->draw_connections(renderer);
    this->draw_nodes(renderer);
    this->draw_path(renderer);
}
