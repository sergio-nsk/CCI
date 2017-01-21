#include <deque>
#include <memory>
#include <unordered_set>

template<typename T>
struct WeakPtrHash : public std::unary_function<std::weak_ptr<T>, size_t>
{
    size_t operator()(const std::weak_ptr<T>& wp) const
    {
        auto sp = wp.lock();
        return std::hash<decltype(sp)>()(sp);
    }
};

template<typename T>
struct WeakPtrEqual : public std::unary_function<std::weak_ptr<T>, bool>
{
    bool operator()(const std::weak_ptr<T>& left, const std::weak_ptr<T>& right) const
    {
        return !left.owner_before(right) && !right.owner_before(left);
    }
};

template <typename State>
class Graph
{
public:
    class Node
    {
    public:
        virtual ~Node() {}

        bool isAdjacentFor(const std::shared_ptr<Node> &other) const
        {
            return childs.find(other) != childs.end();
        }

        void addChild(const std::shared_ptr<Node> &other)
        {
            childs.insert(other);
        }

        const std::unordered_set<std::weak_ptr<Node>, WeakPtrHash<Node>, WeakPtrEqual<Node>> &getAdjacent() const
        {
            return childs;
        }

        State state;

    private:
        std::unordered_set<std::weak_ptr<Node>, WeakPtrHash<Node>, WeakPtrEqual<Node>> childs;
    };

    bool matrix(size_t i, size_t j) const
    {
        if (i == j)
            return false;

        const auto &s = nodes[i];
        const auto &d = nodes[j];
        return s->isAdjacentFor(d);
    }

    void addNode()
    {
        nodes.push_back(std::make_shared<Node>());
    }

    std::shared_ptr<Node> &operator[] (size_t i)
    {
        return nodes[i];
    }

    const std::deque<std::shared_ptr<Node>> &getNodes() const
    {
        return nodes;
    }

private:
    std::deque<std::shared_ptr<Node>> nodes;
};

template <typename State>
using Node = std::shared_ptr<typename Graph<State>::Node>;


template <typename State>
Graph<State> getExampleGraph()
{
    Graph<State> graph;
    for (int i = 0; i < 7; ++i)
        graph.addNode();
    graph[0]->addChild(graph[1]);
    graph[1]->addChild(graph[2]);
    graph[2]->addChild(graph[0]);
    graph[2]->addChild(graph[3]);
    graph[3]->addChild(graph[2]);
    graph[4]->addChild(graph[6]);
    graph[5]->addChild(graph[4]);
    graph[6]->addChild(graph[5]);
    return graph;
}

template <typename State>
Graph<State> getExampleGraph2()
{
    Graph<State> graph;
    for (int i = 0; i < 4; ++i)
        graph.addNode();
    graph[0]->addChild(graph[1]);
    graph[1]->addChild(graph[2]);
    graph[2]->addChild(graph[0]);
    graph[3]->addChild(graph[2]);
    return graph;
}

template <typename State>
Graph<State> getExampleGraph3()
{
    Graph<State> graph;
    for (int i = 0; i < 6; ++i)
        graph.addNode();
    graph[0]->addChild(graph[1]);
    graph[0]->addChild(graph[4]);
    graph[0]->addChild(graph[5]);
    graph[1]->addChild(graph[3]);
    graph[1]->addChild(graph[4]);
    graph[2]->addChild(graph[1]);
    graph[3]->addChild(graph[2]);
    graph[3]->addChild(graph[4]);
    return graph;
}
