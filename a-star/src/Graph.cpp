#include "Graph.h"

#include <cfloat>
#include <cmath>

Graph::Graph(int width, int height) : n_map_width(width), n_map_height(height) {
    this->nodes.resize(static_cast<size_t>(this->n_map_width) * this->n_map_height);
    int i{0};
    for(auto &n : nodes) {
        n = std::make_shared<Node>();
        n->x = i % this->n_map_width;
        n->y = i / this->n_map_height;
        ++i;
    }

    for (const auto &n : nodes) {
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

std::vector<std::shared_ptr<Node>> Graph::get_nodes() { return this->nodes; }

void Graph::set_start_node(const std::shared_ptr<Node> &n) {
    if (nullptr != this->node_start) {
        this->node_start->node_type = empty;
    }
    n->node_type = start;
    this->node_start = n;
}

void Graph::set_end_node(const std::shared_ptr<Node> &n) {
    if (nullptr != this->node_end) {
        this->node_end->node_type = empty;
    }
    n->node_type = end;
    this->node_end = n;
}

void Graph::reset_nodes() const {
    for (const auto& n : this->nodes) {
        n->visited = false;
        n->global_goal = FLT_MAX;
        n->local_goal = FLT_MAX;
        n->parent = nullptr;
    }
}

void Graph::solve_astar(bool best_path) {
    auto distance = [] (const std::shared_ptr<Node>& a, const std::shared_ptr<Node>& b)
    {
        const auto dx = a->x - b->x;
        const auto dy = a->y - b->y;
        return sqrt(dx*dx + dy*dy);
    };
    auto heuristic = [distance] (const std::shared_ptr<Node>& a, const std::shared_ptr<Node>& b){
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
        not_tested.sort([](const std::shared_ptr<Node>& lhs, const std::shared_ptr<Node>& rhs){
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
        for (const auto&  nn : node_current->neighbours) {
            if (!nn->visited && nn->node_type != obstacle) {
                not_tested.push_back(nn);
            }
            double possibly_lower_goal = node_current->local_goal + distance(node_current, nn);
            if (possibly_lower_goal < nn->local_goal) {
                nn->parent = node_current;
                nn->local_goal = possibly_lower_goal;
                nn->global_goal = heuristic(nn, node_end) + nn->local_goal;
            }
        }
    }
}
