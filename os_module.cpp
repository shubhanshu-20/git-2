#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include "os_module.h"
using namespace std;

int movement(vector<int> order, int head) {
    int total=0, current=head;
    for (int track:order) { total += abs(track-current); current=track; }
    return total;
}
vector<int> sstf(vector<int> req, int head) {
    vector<int> order; int current=head;
    while (!req.empty()) {
        int best=0;
        for (int i=1;i<(int)req.size();i++)
            if (abs(req[i]-current)<abs(req[best]-current)) best=i;
        current=req[best]; order.push_back(current); req.erase(req.begin()+best);
    }
    return order;
}
vector<int> scanOrder(vector<int> req, int head, int maxTrack, bool up, string mode) {
    vector<int> left,right,out;
    for (int x:req) { if(x<head) left.push_back(x); else if(x>head) right.push_back(x); else out.push_back(x); }
    sort(left.begin(),left.end()); sort(right.begin(),right.end());
    if(up) {
        out.insert(out.end(),right.begin(),right.end());
        if(mode=="SCAN"&&!right.empty()) out.push_back(maxTrack);
        if(mode=="C-SCAN"&&!right.empty()){out.push_back(maxTrack);if(!left.empty())out.push_back(0);}
        if(mode=="C-SCAN"||mode=="C-LOOK") out.insert(out.end(),left.begin(),left.end());
        else { reverse(left.begin(),left.end()); out.insert(out.end(),left.begin(),left.end()); }
    } else {
        reverse(left.begin(),left.end()); out.insert(out.end(),left.begin(),left.end());
        if(mode=="SCAN"&&!left.empty()) out.push_back(0);
        if(mode=="C-SCAN"&&!left.empty()){out.push_back(0);if(!right.empty())out.push_back(maxTrack);}
        if(mode=="C-SCAN"||mode=="C-LOOK"){reverse(right.begin(),right.end());out.insert(out.end(),right.begin(),right.end());}
        else out.insert(out.end(),right.begin(),right.end());
    }
    return out;
}
void show(string name, vector<int> order, int head) {
    cout << name << " order: ";
    for(int i=0;i<(int)order.size();i++){if(i)cout<<" -> ";cout<<order[i];}
    cout << "\nHead movement: " << movement(order,head) << "\n\n";
}
void osMenu() {
    int n,head,maxTrack; vector<int> req;
    cout << "\n--- OS Disk Scheduling ---\nNumber of requests: "; cin >> n;
    if(n<0){cout<<"Invalid number.\n";return;}
    cout << "Enter requests: ";
    for(int i=0;i<n;i++){int x;cin>>x;req.push_back(x);}
    cout << "Initial head: ";cin>>head; cout<<"Maximum track: ";cin>>maxTrack;
    if(maxTrack<1||head<0||head>maxTrack){cout<<"Invalid disk range.\n";return;}
    for(int x:req) if(x<0||x>maxTrack){cout<<"Request outside disk range.\n";return;}
    char dir;cout<<"Direction (U/D): ";cin>>dir;bool up=dir=='U'||dir=='u';
    show("FCFS",req,head); show("SSTF",sstf(req,head),head);
    show("SCAN",scanOrder(req,head,maxTrack,up,"SCAN"),head);
    show("C-SCAN",scanOrder(req,head,maxTrack,up,"C-SCAN"),head);
    show("LOOK",scanOrder(req,head,maxTrack,up,"LOOK"),head);
    show("C-LOOK",scanOrder(req,head,maxTrack,up,"C-LOOK"),head);
}
