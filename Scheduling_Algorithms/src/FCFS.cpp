#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct Process{
    string ID; //name of the process
    int at; //arrival time: time in which the process got there
    int bt; //burst time: processing time on the cpu
    int tat; //turn around time: total time execution of a process. tat = bt + wt
    int wt; //waiting time: time that the process waits to be executed. wt = st - at
    int st; //service time: time that the process starts its execution. st = accumulated bt
};
//method that takes each process and executes it
void sjfScheduling(vector<Process>& processes) {
    int n = processes.size(); // size of the processes array
    float totalwt = 0, totaltat = 0, avgwt = 0, avgtat = 0;

    // we sort the processes acording to their arrival time
    sort(processes.begin(), processes.end(), [](Process a, Process b) {
        return a.at < b.at;
    });

    // we calculate the tat, st and wt of the first process
    processes[0].wt = 0;
    processes[0].st = 0;
    processes[0].tat = processes[0].bt + processes[0].wt;

    int accumulatedbt = 0;

    // we calculate the ct, wt and tat of all the other processes
    for(int i = 1; i < n; i++) {
        accumulatedbt += processes[i-1].bt;
        processes[i].st = accumulatedbt;
        processes[i].wt = processes[i].st - processes[i].at;
        processes[i].tat = processes[i].bt + processes[i].wt;

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

    cout << "Process\tAt\tBt\tSt\tTat\tWt\n";
    for(const auto& p : processes){
        cout << p.ID << "\t" << p.at << "\t" << p.bt << "\t\t" << p.st << "\t\t" << p.tat << "\t" << p.wt << endl;
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