#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <unordered_map>
#include <algorithm>
#include "cache.h"
using namespace std;

struct Result
{
    int hits = 0, misses = 0;
};

vector<int> getPages()
{
    vector<int> pages;
    ifstream file("last_workload.txt");
    int value;
    while (file >> value)
        pages.push_back(value);
    if (!pages.empty())
    {
        cout << "Loaded last_workload.txt.\n";
        return pages;
    }
    int n;
    cout << "Number of page requests: ";
    cin >> n;
    if (n < 0)
        return pages;
    cout << "Enter page numbers: ";
    for (int i = 0; i < n; i++)
    {
        cin >> value;
        pages.push_back(value);
    }
    return pages;
}

Result fifo(const vector<int> &pages, int cap)
{
    Result r;
    list<int> cache;
    for (int p : pages)
    {
        if (find(cache.begin(), cache.end(), p) != cache.end())
            r.hits++;
        else
        {
            r.misses++;
            if (cap > 0)
            {
                if ((int)cache.size() == cap)
                    cache.pop_front();
                cache.push_back(p);
            }
        }
    }
    return r;
}
Result lru(const vector<int> &pages, int cap)
{
    Result r;
    list<int> cache;
    for (int p : pages)
    {
        auto it = find(cache.begin(), cache.end(), p);
        if (it != cache.end())
        {
            r.hits++;
            cache.erase(it);
            cache.push_back(p);
        }
        else
        {
            r.misses++;
            if (cap > 0)
            {
                if ((int)cache.size() == cap)
                    cache.pop_front();
                cache.push_back(p);
            }
        }
    }
    return r;
}
Result lfu(const vector<int> &pages, int cap)
{
    Result r;
    struct Info
    {
        int count, last;
    };
    unordered_map<int, Info> cache;
    int clock = 0;
    for (int p : pages)
    {
        clock++;
        auto it = cache.find(p);
        if (it != cache.end())
        {
            r.hits++;
            it->second.count++;
            it->second.last = clock;
        }
        else
        {
            r.misses++;
            if (cap <= 0)
                continue;
            if ((int)cache.size() == cap)
            {
                auto victim = cache.begin();
                for (auto cur = cache.begin(); cur != cache.end(); cur++)
                    if (cur->second.count < victim->second.count ||
                        (cur->second.count == victim->second.count && cur->second.last < victim->second.last))
                        victim = cur;
                cache.erase(victim);
            }
            cache[p] = {1, clock};
        }
    }
    return r;
}
void printResult(string name, Result r, int total)
{
    double ratio = total ? (double)r.hits / total * 100 : 0;
    cout << name << " | Hits: " << r.hits << " | Misses: " << r.misses
         << " | Hit ratio: " << ratio << "%\n";
}
void cacheMenu()
{
    cout << "\n--- DBMS Cache Module ---\n";
    vector<int> pages = getPages();
    if (pages.empty())
    {
        cout << "No workload. Use Workload Analyzer first.\n";
        return;
    }
    int cap;
    cout << "Cache capacity: ";
    cin >> cap;
    if (cap < 0)
    {
        cout << "Capacity cannot be negative.\n";
        return;
    }
    Result a = fifo(pages, cap), b = lru(pages, cap), c = lfu(pages, cap);
    cout << "\nCache comparison\n";
    printResult("FIFO", a, pages.size());
    printResult("LRU ", b, pages.size());
    printResult("LFU ", c, pages.size());
    cout << "Compare hit ratios for this workload; ties are possible.\n";
}
