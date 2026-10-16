#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "workload.h"
using namespace std;

vector<int> readNumbers(string line) {
    for (char &c : line) if (c == ',') c = ' ';
    stringstream ss(line);
    vector<int> values;
    int n;
    while (ss >> n) values.push_back(n);
    return values;
}

void workloadMenu() {
    int choice;
    vector<int> pages;
    cout << "\n--- Workload Analyzer ---\n1. Enter requests\n2. Read from text file\nChoose: ";
    cin >> choice;
    cin.ignore(10000, '\n');

    if (choice == 1) {
        string line;
        cout << "Enter page numbers separated by spaces or commas: ";
        getline(cin, line);
        pages = readNumbers(line);
    } else if (choice == 2) {
        string name, line;
        cout << "File name (example: sample_workload.txt): ";
        getline(cin, name);
        ifstream file(name);
        if (!file) { cout << "File not found. Put it in the program folder.\n"; return; }
        while (getline(file, line)) {
            vector<int> row = readNumbers(line);
            pages.insert(pages.end(), row.begin(), row.end());
        }
    } else { cout << "Invalid choice.\n"; return; }

    if (pages.empty()) { cout << "No page requests found.\n"; return; }

    vector<int> uniquePages;
    int repeats = 0;
    for (int page : pages) {
        bool found = false;
        for (int old : uniquePages) if (old == page) found = true;
        if (found) repeats++;
        else uniquePages.push_back(page);
    }

    double percent = (double)repeats / pages.size() * 100;
    cout << "\nWorkload summary\nRequests: " << pages.size()
         << "\nUnique pages: " << uniquePages.size()
         << "\nRepeated requests: " << repeats
         << "\nRepeat percentage: " << percent << "%\n";
    cout << (percent >= 40 ? "Observation: many requests repeat; compare LRU and LFU.\n"
                            : "Observation: compare all policies for this workload.\n");

    ofstream saved("last_workload.txt");
    for (int page : pages) saved << page << " ";
    cout << "Saved workload to last_workload.txt.\n";
}
