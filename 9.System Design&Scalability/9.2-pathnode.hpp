#pragma once

#include "9.2-person.hpp"
#include <memory>

class PathNodeImpl : public std::enable_shared_from_this<PathNodeImpl>
{
public:
    using PathNode = std::shared_ptr<PathNodeImpl>;

private:
    Person person;
    PathNode previousNode;

public:
    PathNodeImpl(Person p, PathNode previous)
    {
        person = p;
        previousNode = previous;
    }

    Person getPerson()
    {
        return person;
    }

    std::deque<Person> collapse(bool startsWithRoot)
    {
        std::deque<Person> path;
        PathNode node = shared_from_this();
        while (node)
        {
            if (startsWithRoot)
                path.emplace_back(node->person);
            else
                path.emplace_front(node->person);
            node = node->previousNode;
        }
        return path;
    }
};

using PathNode = PathNodeImpl::PathNode;
