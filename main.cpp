#include <iostream>
#include "workload.h"
#include "cache.h"
#include "indexing.h"
#include "os_module.h"
#include "file_allocation.h"
using namespace std;
int main()
{
    int choice;
    do
    {
        cout << "\n=== Smart Cache Optimization System ===\n";
        cout << "1. Workload Analyzer\n2. Cache Module (DBMS)\n3. DBMS Indexing\n";
        cout << "4. OS Disk Scheduling\n5. OS File Allocation\n0. Exit\nChoose: ";
        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
        switch (choice)
        {
        case 1:
            workloadMenu();
            break;
        case 2:
            cacheMenu();
            break;
        case 3:
            indexingMenu();
            break;
        case 4:
            osMenu();
            break;
        case 5:
            fileAllocationMenu();
            break;
        case 0:
            cout << "Goodbye.\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 0);
    return 0;
}
