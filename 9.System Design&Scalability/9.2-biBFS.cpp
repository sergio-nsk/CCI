#include "9.2-person.hpp"
#include "9.2-BFSData.hpp"
#include <deque>
#include <iostream>

std::deque<Person> mergePaths(BFSData &bfs1, BFSData &bfs2, int connection) ;

// Search one level and return collision, if any.
Person searchLevel(const std::unordered_map<int, Person> &people, BFSData &primary, BFSData &secondary);

std::deque<Person> findPathBiBFS(const std::unordered_map<int, Person> &people, int source, int destination)
{
	BFSData sourceData(people.at(source));
	BFSData destData(people.at(destination));

	while (!sourceData.isFinished() && !destData.isFinished())
	{
		// Search out from source.
		Person collision = searchLevel(people, sourceData, destData);
		if (collision)
			return mergePaths(sourceData, destData, collision->getID());

		// Search out from destination.
		collision = searchLevel(people, destData, sourceData);
		if (collision)
			return mergePaths(sourceData, destData, collision->getID());
	}
	return std::deque<Person>();
}

Person searchLevel(const std::unordered_map<int, Person> &people, BFSData &primary, BFSData &secondary)
{
	// We only want to search one level at a time. Count how many nodes are currently in the primary's
	// level and only do that many nodes. We'll continue to add nodes to the end.
	int count = primary.toVisit.size();
	for (int i = 0; i < count; i++) {
		// Pull out first node.
		PathNode pathNode = primary.toVisit.front();
		primary.toVisit.pop();
		int personId = pathNode->getPerson()->getID();

		// Check if it's already been visited.
		if (secondary.visited.find(personId) != secondary.visited.end())
			return pathNode->getPerson();

		// Add friends to queue.
		Person person = pathNode->getPerson();
		auto friends = person->getFriends();
		for (int friendId : friends)
		{
			if (primary.visited.find(friendId) == primary.visited.end())
			{
				auto f = people.at(friendId);
				auto next = std::make_shared<PathNodeImpl>(f, pathNode);
				primary.visited[friendId] = next;
				primary.toVisit.push(next);
			}
		}
	}
	return nullptr;
}

std::deque<Person> mergePaths(BFSData &bfs1, BFSData &bfs2, int connection)
{
	PathNode end1 = bfs1.visited.at(connection); // end1 -> source
	PathNode end2 = bfs2.visited.at(connection); // end2 -> dest
	auto pathOne = end1->collapse(false); // forward: source -> connection
	auto pathTwo = end2->collapse(true); // reverse: connection -> dest
	pathTwo.pop_front(); // remove connection
	pathOne.insert(pathOne.end(), pathTwo.begin(), pathTwo.end()); // add second path
	return pathOne;
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
    auto path1 = findPathBiBFS(people, i, j);
    printPeople(path1);
}
