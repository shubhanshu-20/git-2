# Smart Cache Optimization System — First Milestone

## Modules
- `workload.cpp`: manual or text-file workload input, repeated-page analysis, saves `last_workload.txt`.
- `cache.cpp`: FIFO, LRU and LFU cache simulations with hit/miss ratios.
- `indexing.cpp`: ordered lookup using `std::map` and hash lookup using `std::unordered_map`.
- `os_module.cpp`: FCFS, SSTF, SCAN, C-SCAN, LOOK and C-LOOK disk scheduling.
- `file_allocation.cpp`: linked and indexed file-allocation examples.
- `main.cpp`: menu that connects each module.

## Compile
```bash
g++ -std=c++17 -Wall -Wextra main.cpp workload.cpp cache.cpp indexing.cpp os_module.cpp file_allocation.cpp -o smart_cache
```
Windows: `.\smart_cache.exe`
Linux/macOS: `./smart_cache`

## Try the workload file
Choose Workload Analyzer > Read from text file > enter `sample_workload.txt`.
It writes `last_workload.txt`; the Cache Module reads that file automatically.

## Scope
This is an approximate first 50% milestone, not a claim that exactly half of every proposal feature is finished. The current code does not yet include custom B-Tree/B+ Tree structures, SQL parsing, persistent database records, a combined OS+DBMS scoring engine, or frontend/backend integration.
