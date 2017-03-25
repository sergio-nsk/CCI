#pragma once

#include <deque>
#include <string>
#include <memory>

class PersonImpl
{
	std::deque<int> friends;
	int personID;
	std::string info;
public:
	const std::string &getInfo() const
    {
        return info;
    }
	void setInfo(std::string &info)
    {
		this->info = info;
	}
	const std::deque<int> &getFriends()
    {
		return friends;
	}
	int getID() const
    {
        return personID;
    }
	void addFriend(int id)
    {
        friends.push_back(id);
    }
	PersonImpl(int id) : personID(id)
    {
	}
};

using Person = std::shared_ptr<PersonImpl>;
