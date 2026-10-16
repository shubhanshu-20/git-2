#include <iostream>
#include <map>
#include <unordered_map>
#include <string>
#include "indexing.h"
using namespace std;
void indexingMenu()
{
    int choice, n;
    cout << "\n--- DBMS Indexing Demo ---\n1. Ordered index demo\n2. Hash index demo\nChoose: ";
    cin >> choice;
    cout << "Number of records: ";
    cin >> n;
    if (n < 0)
    {
        cout << "Invalid number.\n";
        return;
    }
    if (choice == 1)
    {
        map<int, string> index;
        for (int i = 0; i < n; i++)
        {
            int id;
            string name;
            cout << "Enter ID and one-word name: ";
            cin >> id >> name;
            index[id] = name;
        }
        cout << "Records in key order:\n";
        for (auto item : index)
            cout << item.first << " : " << item.second << "\n";
        int id;
        cout << "ID to search: ";
        cin >> id;
        auto it = index.find(id);
        if (it != index.end())
            cout << "Found: " << it->first << " " << it->second << "\n";
        else
            cout << "Record not found.\n";
        cout << "Uses std::map as an ordered-index demonstration, not a custom B-Tree.\n";
    }
    else if (choice == 2)
    {
        unordered_map<int, string> index;
        for (int i = 0; i < n; i++)
        {
            int id;
            string name;
            cout << "Enter ID and one-word name: ";
            cin >> id >> name;
            index[id] = name;
        }
        int id;
        cout << "ID to search: ";
        cin >> id;
        auto it = index.find(id);
        if (it != index.end())
            cout << "Found: " << it->first << " " << it->second << "\n";
        else
            cout << "Record not found.\n";
        cout << "Uses the C++ hash table container.\n";
    }
    else
        cout << "Invalid choice.\n";
}
