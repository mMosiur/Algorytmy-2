#include <iostream>
#include <list>
#include <vector>

typedef unsigned short ushort;
typedef unsigned int uint;

struct Node;

struct Edge {
    Node* from;
    Node* to;
    uint flow;
    uint backward_flow;
    Edge(Node& from, Node& to, uint flow) : from(&from), to(&to), flow(flow), backward_flow(0) {}
};

struct Node {
    int index = INT32_MAX;
    std::list<Edge*> edges_in;
    std::list<Edge*> edges_out;
};

class Festival {
    Node source;
    std::vector<Node> nodes;
    uint nof_guests;
    uint nof_dishes;
    Node target;
    std::list<Edge> edges;
    std::list<Edge*> path;

    Node& get_guest(uint n) {
        if(n >= nof_guests) throw;
        return nodes[n];
    }

    Node& get_dish(uint n) {
        if(n >= nof_dishes) throw;
        n += nof_guests;
        return nodes[n];
    }

    Edge* create_edge(Node& from, Node& to, uint flow = 1) {
        edges.emplace_back(from, to, flow);
        Edge* edge = &edges.back();
        from.edges_out.push_back(edge);
        to.edges_in.push_back(edge);
        return edge;
    }

    bool path_to_target(Node* node, std::vector<bool>& visited) {
        for(auto edge : node->edges_out) {
            if(edge->flow == 0) continue;
            if(edge->to == &target) {
                path.push_back(edge);
                return true;
            }
            if(visited[edge->to->index]) continue;
            visited[edge->to->index] = true;
            path.push_back(edge);
            if(path_to_target(edge->to, visited)) return true;
            path.pop_back();
        }
        for(auto edge : node->edges_in) {
            if(edge->backward_flow == 0) continue;
            if(edge->from == &source) continue;
            if(visited[edge->from->index]) continue;
            visited[edge->from->index] = true;
            path.push_back(edge);
            if(path_to_target(edge->from, visited)) return true;
            path.pop_back();
        }
        return false;
    }

    bool find_path() {
        path.clear();
        std::vector<bool> visited(nodes.size(), false);
        Node* pos = &source;
        return path_to_target(&source, visited);
    }

public:
    Festival(uint nof_guests, uint nof_dishes, uint nof_meals)
        : nof_guests(nof_guests), nof_dishes(nof_dishes), nodes(nof_guests + nof_dishes) {
        source.index = -1;
        for(uint d = 0; d < nof_dishes; d++) {
            get_dish(d).index = nof_guests + d;
            create_edge(get_dish(d), target, nof_meals);
        }
        for(uint g = 0; g < nof_guests; g++) {
            get_guest(g).index = g;
            for(uint d = 0; d < nof_dishes; d++) {
                char c;
                std::cin >> c;
                if(c == 'x') create_edge(get_guest(g), get_dish(d));
            }
            create_edge(source, get_guest(g));
        }
    }

    uint max_content_guests() {
        while(find_path()) {
            uint min_flow = UINT32_MAX;
            Node* position = &source;
            for(auto& edge : path) {
                Node* other = (edge->from == position ? edge->to : edge->from);
                if(position->index > other->index) { // Backward
                    if(edge->backward_flow < min_flow) min_flow = edge->backward_flow;
                } else {
                    if(edge->flow < min_flow) min_flow = edge->flow;
                }
                position = other;
            }
            position = &source;
            for(auto& edge : path) {
                Node* other = (edge->from == position ? edge->to : edge->from);
                if(position->index > other->index) { // Backward
                    edge->backward_flow -= min_flow;
                    edge->flow += min_flow;
                } else {
                    edge->flow -= min_flow;
                    edge->backward_flow += min_flow;
                }
                position = other;
            }
        }
        uint result = 0;
        for(auto& edge : target.edges_in) {
            result += edge->backward_flow;
        }
        return result;
    }
};

int main() {
    uint n; // Liczba uczestników fesstiwalu
    uint m; // Liczba ró¿nych potraw na festiwalu
    uint l; // Liczba zestawów degustacyjnych ka¿dej z potraw

    std::cin >> n >> m >> l;

    Festival festival(n, m, l);

    std::cout << festival.max_content_guests() << std::endl;

    return 0;
}