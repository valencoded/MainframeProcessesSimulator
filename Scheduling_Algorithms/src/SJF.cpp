#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct Process{
    string ID; //name of the process
    int at; //arrival time: time in which the process got there
    int bt; //burst time: processing time on the cpu
    int ct; //completion time: time that the process finishes. ct = at + bt
    int tat; //turn around time: total time execution of a process. tat = ct - at
    int wt; //waiting time: time that the process waits to be executed. wt = tat - bt
};
//method that takes each process and executes it
void sjfScheduling(vector<Process>& processes) {
    int n = processes.size(); // size of the processes array
    float totalwt = 0, totaltat = 0, avgwt = 0, avgtat = 0;

    // we sort the processes acording to their arrival time
    sort(processes.begin(), processes.end(), [](Process a, Process b) {
        return a.at < b.at;
    });
    //we sort the processes according to their burst time, except for the first one (the one that got first)
    sort(processes.begin()+1, processes.end(), [](Process a, Process b) {
        return a.bt < b.bt;
    });

    // we calculate the tat, wt and ct of the first process
    processes[0].wt = 0;
    processes[0].ct = processes[0].bt;
    processes[0].tat = processes[0].ct - processes[0].at;

    // we calculate the ct, wt and tat of all the other processes
    for(int i = 1; i < n; i++) {
        processes[i].ct = processes[i-1].ct + processes[i].bt;
        processes[i].wt = processes[i-1].ct - processes[i].at;
        processes[i].tat = processes[i].ct - processes[i].at;

        //we calculate the total wt and total tat
        totalwt += processes[i].wt;
        totaltat += processes[i].tat;
    }

    //we calculate the average of the wt and tat
    avgwt = totalwt / n;
    avgtat = totaltat / n;

    // we show the results
    for (auto it = processes.begin(); it != processes.end(); ++it) {
        cout << it->ID;
        if (next(it) != processes.end()) {  // Check if it's NOT the last element
            cout << " << ";
        }
    }
    cout << endl;

    cout << "Process\tAt\tBt\tCt\tTat\tWt\n";
    for(const auto& p : processes){
        cout << p.ID << "\t" << p.at << "\t" << p.bt << "\t\t" << p.ct << "\t\t" << p.tat << "\t" << p.wt << endl;
    }
    cout <<"Average waiting time: " << avgwt <<endl;
    cout <<"Average turn around time: " << avgtat <<endl;

}


int main(){
    vector<Process> processes = {
        {"P1", 0, 5},
        {"P2", 1, 3},
        {"P3", 2, 8},
        {"P4", 3, 6}
    };

    // execute the Short Job First Scheduling
    sjfScheduling(processes);

    return 0;
}