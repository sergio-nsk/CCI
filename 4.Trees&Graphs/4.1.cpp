// Route Between Nodes: Given a directed graph, design an algorithm to find out whether is a
// route between to nodes.

#include <queue>
#include <iostream>
#include "graph.hpp"

enum State {Unvisited, Visiting, Visited};

bool routeBetwenNodes(Graph<State> &graph, Node<State> &from, Node<State> &to)
{
    if (from == to)
        return true;

    for (auto &n : graph.getNodes())
        n->state = Unvisited;

    std::queue<Node<State>> queue;

    from->state = Visiting;
    queue.push(from);

    while (!queue.empty())
    {
        Node<State> n = queue.front();
        queue.pop();
        for (auto &c : n->getAdjacent())
        {
            auto v = c.lock();
            if (v->state == Unvisited)
            {
                if (v == to)
                    return true;
                else
                {
                    v->state = Visiting;
                    queue.push(v);
                }
            }
        }
        n->state = Visited;
    }
    return false;
}

bool test(Graph<State> &graph, size_t from, size_t to)
{
    bool result = routeBetwenNodes(graph, graph[from], graph[to]);
    std::cout << to << " is " << (result ? "" : "NOT") << " reachable from " << from << std::endl;
    return result;
}

int main()
{
    auto graph = getExampleGraph<State>();
    test(graph, 0, 0);
    test(graph, 0, 1);
    test(graph, 0, 2);
    test(graph, 0, 3);
    test(graph, 0, 4);
    test(graph, 0, 5);
    test(graph, 0, 6);

    std::cout << std::endl;

    test(graph, 1, 0);
    test(graph, 1, 1);
    test(graph, 1, 2);
    test(graph, 1, 3);
    test(graph, 1, 4);
    test(graph, 1, 5);
    test(graph, 1, 6);

    std::cout << std::endl;

    test(graph, 2, 0);
    test(graph, 2, 1);
    test(graph, 2, 2);
    test(graph, 2, 3);
    test(graph, 2, 4);
    test(graph, 2, 5);
    test(graph, 2, 6);

    std::cout << std::endl;

    test(graph, 3, 0);
    test(graph, 3, 1);
    test(graph, 3, 2);
    test(graph, 3, 3);
    test(graph, 3, 4);
    test(graph, 3, 5);
    test(graph, 3, 6);

    std::cout << std::endl;

    test(graph, 4, 0);
    test(graph, 4, 1);
    test(graph, 4, 2);
    test(graph, 4, 3);
    test(graph, 4, 4);
    test(graph, 4, 5);
    test(graph, 4, 6);

    std::cout << std::endl;

    test(graph, 5, 0);
    test(graph, 5, 1);
    test(graph, 5, 2);
    test(graph, 5, 3);
    test(graph, 5, 4);
    test(graph, 5, 5);
    test(graph, 5, 6);

    std::cout << std::endl;

    test(graph, 6, 0);
    test(graph, 6, 1);
    test(graph, 6, 2);
    test(graph, 6, 3);
    test(graph, 6, 4);
    test(graph, 6, 5);
    test(graph, 6, 6);

    return 0;
}