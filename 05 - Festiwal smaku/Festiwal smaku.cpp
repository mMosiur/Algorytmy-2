#include <iostream>
#include <list>
#include <vector>
#include <queue>

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
    std::list<Edge*> edges;

    std::list<Edge*> edges_out() {
        std::list<Edge*> result;
        for(auto& edge : edges) {
            if(edge->from == this && edge->flow > 0) result.push_back(edge);
            else if(edge->to == this && edge->backward_flow > 0) result.push_back(edge);
        }
        return result;
    }

    std::list<Edge*> edges_in() {
        std::list<Edge*> result;
        for(auto& edge : edges) {
            if(edge->to == this && edge->flow > 0) result.push_back(edge);
            else if(edge->from == this && edge->backward_flow > 0) result.push_back(edge);
        }
        return result;
    }
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
        from.edges.push_back(edge);
        to.edges.push_back(edge);
        return edge;
    }

    bool find_path() {
        path.clear();
        std::queue<Node*> queue;
        std::vector<bool> visited(nodes.size(), false);
        std::vector<std::pair<Node*, Edge*>> parent(nodes.size(), { nullptr, nullptr });
        queue.push(&source);
        while(!queue.empty()) {
            Node* position = queue.front();
            queue.pop();
            for(auto& edge : position->edges_out()) {
                Node* other = (edge->from == position ? edge->to : edge->from);
                if(other == &source) continue;
                if(other == &target) {
                    path.push_front(edge);
                    do {
                        uint i = position->index;
                        path.push_front(parent[i].second);
                        position = parent[i].first;
                    } while(position != &source);
                    return true;
                }
                uint i = other->index;
                if(visited[i]) continue;
                visited[i] = true;
                parent[i] = { position, edge };
                queue.push(other);
            }
        }
        return false;
    }

public:
    Festival(uint nof_guests, uint nof_dishes, uint nof_meals)
        : nof_guests(nof_guests), nof_dishes(nof_dishes), nodes(nof_guests + nof_dishes) {
        source.index = -1;
        for(uint g = 0; g < nof_guests; g++) {
            get_guest(g).index = g;
            create_edge(source, get_guest(g));
            for(uint d = 0; d < nof_dishes; d++) {
                char c;
                std::cin >> c;
                if(c == 'x') create_edge(get_guest(g), get_dish(d));
            }
        }
        for(uint d = 0; d < nof_dishes; d++) {
            get_dish(d).index = nof_guests + d;
            create_edge(get_dish(d), target, nof_meals);
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
        for(auto& edge : target.edges) {
            result += edge->backward_flow;
        }
        return result;
    }
};

int main() {
    uint n; // Liczba uczestnik�w fesstiwalu
    uint m; // Liczba r�nych potraw na festiwalu
    uint l; // Liczba zestaw�w degustacyjnych ka�dej z potraw

    std::cin >> n >> m >> l;

    Festival festival(n, m, l);

    std::cout << festival.max_content_guests() << std::endl;

    return 0;
}