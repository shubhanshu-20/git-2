#include <iostream>
#include <vector>
#include <string>
#include "file_allocation.h"
using namespace std;
void fileAllocationMenu() {
    int n; cout << "\n--- OS File Allocation ---\nNumber of files: "; cin >> n;
    if(n<0){cout<<"Invalid number.\n";return;}
    vector<string> names(n); vector<int> blocks(n);
    for(int i=0;i<n;i++){cout<<"File name: ";cin>>names[i];cout<<"Number of data blocks: ";cin>>blocks[i];if(blocks[i]<0)blocks[i]=0;}
    int next=0;
    cout<<"\nLinked allocation\n";
    for(int i=0;i<n;i++){
        cout<<names[i]<<": ";
        for(int j=0;j<blocks[i];j++){if(j)cout<<" -> ";cout<<next++;}
        if(blocks[i]==0)cout<<"(empty)";
        cout<<"\n";
    }
    next=0;
    cout<<"\nIndexed allocation\n";
    for(int i=0;i<n;i++){
        cout<<names[i]<<" index block "<<next++<<" -> ";
        for(int j=0;j<blocks[i];j++){if(j)cout<<", ";cout<<next++;}
        if(blocks[i]==0)cout<<"(no data blocks)";
        cout<<"\n";
    }
    cout<<"These are illustrative block numbers; no physical disk is changed.\n";
}
