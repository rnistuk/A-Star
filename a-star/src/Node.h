#pragma once
#include <memory>
#include <vector>

enum Node_Type {empty, start, end, obstacle};

struct Node {
    Node_Type node_type{empty};

    bool visited{false};
    double global_goal{0};
    double local_goal{0};
    int x;
    int y;
    std::vector<std::shared_ptr<Node>> neighbours;
    std::shared_ptr<Node> parent;
};
