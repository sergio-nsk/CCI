#include <iostream>
#include <random>
#include <unordered_set>

void showInfo(const std::unordered_set<int> &hash)
{
    std::cout << "hash.bucket_count():     " << hash.bucket_count() << std::endl;
    std::cout << "hash.size():             " << hash.size() << std::endl;
    std::cout << "hash.load_factor():      " << hash.load_factor() << std::endl;
}

void fillHash(std::unordered_set<int> &hash, int n)
{
    std::random_device seed;
    std::mt19937 engine(seed());
    std::uniform_int_distribution<> uniformDist(0, 1000);

    for (int i = 0; i < n; ++i)
        hash.insert(uniformDist(engine));
}

int main()
{
    std::unordered_set<int> hash;
    std::cout << "hash.max_bucket_count(): " << hash.max_bucket_count() << std::endl;
    std::cout << "hash.max_load_factor():  " << hash.max_load_factor() << std::endl;

    showInfo(hash);

    hash.insert(500);
    std::cout << "hash.bucket(500):        " << hash.bucket(500) << std::endl;

    std::cout << "Add at least 100 random elements\n";
    fillHash(hash, 100);
    showInfo(hash);
    std::cout << "hash.bucket(500):        " << hash.bucket(500) << std::endl;

    std::cout << "Rserve at least 500 buckets\n";
    hash.rehash(500);
    showInfo(hash);
    std::cout << "hash.bucket(500):        " << hash.bucket(500) << std::endl;
}
