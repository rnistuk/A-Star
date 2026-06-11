#pragma once
#include "Node.h"

#include <memory>
#include <list>

class Graph {
    int n_map_width{16};
    int n_map_height{16};

    std::vector<std::shared_ptr<Node>> nodes;
    std::shared_ptr<Node> node_start;
    std::shared_ptr<Node> node_end;
    void reset_nodes();

public:
    explicit Graph(int width = 16, int height = 16);

    std::shared_ptr<Node> node_on_point(int x, int y);

    std::shared_ptr<Node> get_start_node() const { return this->node_start; };

    std::shared_ptr<Node> get_end_node() const { return this->node_end; };

    std::vector<std::shared_ptr<Node>> get_nodes();

    void solve_astar(bool best_path = true);

    void set_start_node(const std::shared_ptr<Node> &n);

    void set_end_node(const std::shared_ptr<Node> &n);
};
