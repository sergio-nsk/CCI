#include "9.2-person.hpp"
#include "9.2-pathnode.hpp"
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <iostream>

std::deque<Person> findPathBFS(const std::unordered_map<int, Person> &people, int source, int destination)
{
    std::queue<PathNode> toVisit;
    std::unordered_set<int> visited;
    toVisit.emplace(std::make_shared<PathNodeImpl>(people.at(source), nullptr));
    visited.insert(source);
    while (!toVisit.empty())
    {
        PathNode node = toVisit.front();
        toVisit.pop();
        Person person = node->getPerson();
        if (person->getID() == destination) {
            return node->collapse(false);
        }

        // Search friends.
        std::deque<int> friends = person->getFriends();
        for (int friendId : friends)
        {
            if (visited.find(friendId) == visited.end())
            {
                visited.insert(friendId);
                Person f = people.at(friendId);
                toVisit.emplace(std::make_shared<PathNodeImpl>(f, node));
            }
        }
    }
    return std::deque<Person>();
}

void printPeople(const std::deque<Person> &path)
{
    if (path.empty())
        std::cout << "No path";
    else
        for (auto &p : path)
            std::cout << p->getID() << '\n';
}

int main()
{
    int nPeople = 11;
    std::unordered_map<int, Person> people;
    for (int i = 0; i < nPeople; i++)
    {
        people.emplace(i, std::make_shared<PersonImpl>(i));
    }

    const int edges[][2] = {{1, 4}, {1, 2}, {1, 3}, {3, 2}, {4, 6}, {3, 7}, {6, 9}, {9, 10}, {5, 10}, {2, 5}, {3, 7}};

    for (auto &edge : edges) {
        Person source = people.at(edge[0]);
        source->addFriend(edge[1]);

        Person destination = people.at(edge[1]);
        destination->addFriend(edge[0]);
    }

    int i = 1;
    int j = 10;
    auto path1 = findPathBFS(people, i, j);
    printPeople(path1);
}
