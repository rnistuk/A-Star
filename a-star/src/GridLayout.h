#pragma once

struct GridLayout {
    int node_size{23};
    int node_border{5};

    int to_pos(int x) const {
        return this->node_border + (this->node_size + this->node_border) * x;
    }

    int center(int i) const {
        return this->to_pos(i) + this->node_size / 2;
    }

    bool node_contains_point(int x_node, int y_node, int x_point, int y_point) const {
        int x_r = this->to_pos(x_node);
        int y_r = this->to_pos(y_node);

        return x_r <= x_point && x_r + node_size > x_point
            && y_r <= y_point && y_r + node_size > y_point;
    }
};
