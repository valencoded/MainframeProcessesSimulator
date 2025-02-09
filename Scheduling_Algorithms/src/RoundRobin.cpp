#include <iostream>
#include <vector>
#include <queue>
#include<algorithm>
using namespace std;

struct Process {
    string ID; //name of the process
    int at; //arrival time: time in which the process got there
    int bt; //burst time: processing time on the cpu
    int ct; //completion time: time that the process finishes. ct = at + bt
    int tat; //turn around time: total time execution of a process. tat = ct - at
    int wt; //waiting time: time that the process waits to be executed. wt = tat - bt
    int remaining_bt; // remaining burst time: remaining time of processing time on the cpu.
};

void roundrobinScheduling(vector<Process>& processes, int qt) {
    int n = processes.size();
    float totalwt = 0, totaltat = 0;

    // We organize the processes by arrival time
    sort(processes.begin(), processes.end(), [](Process a, Process b) {
        return a.at < b.at;
    });

    queue<int> readyQueue;
    int currentTime = 0, completed = 0;
    vector<bool> inQueue(n, false);

    // We initialize remaining bursting times.
    for (int i = 0; i < n; i++) {
        processes[i].remaining_bt = processes[i].bt;
    }

    // we add the first process to the queue
    readyQueue.push(0);
    inQueue[0] = true;


    while (completed < n) {
        //idx: the process thats in the front of the queue
        int idx = readyQueue.front();
        readyQueue.pop();

        if (processes[idx].remaining_bt > qt) {
            currentTime += qt;
            processes[idx].remaining_bt -= qt;
        } else {
            currentTime += processes[idx].remaining_bt;
            processes[idx].remaining_bt = 0;

            // when the process is done being executed we add the times
            processes[idx].ct = currentTime;
            processes[idx].tat = processes[idx].ct - processes[idx].at;
            processes[idx].wt = processes[idx].tat - processes[idx].bt;
            totalwt += processes[idx].wt;
            totaltat += processes[idx].tat;
            completed++;
        }

        // we add new processes to the queue
        for (int i = 0; i < n; i++) {
            if (processes[i].at <= currentTime && processes[i].remaining_bt > 0 && !inQueue[i]) {
                readyQueue.push(i);
                inQueue[i] = true;
            }
        }

        // if the process is not done yet, we add it to the queue.
        if (processes[idx].remaining_bt > 0) {
            readyQueue.push(idx);
        }

        // if the queue is empty we start the other process time.
        if (readyQueue.empty()) {
            for (int i = 0; i < n; i++) {
                if (processes[i].remaining_bt > 0) {
                    readyQueue.push(i);
                    inQueue[i] = true;
                    break;
                }
            }
        }
    }

    //we calculate the average of the wt and tat
    float avgwt = totalwt / n;
    float avgtat = totaltat / n;

    // we show the results
    cout << "Process\tAT\tBT\tCT\tTAT\tWT\n";
    for (const auto& p : processes) {
        cout << p.ID << "\t" << p.at << "\t" << p.bt << "\t" << p.ct << "\t" << p.tat << "\t" << p.wt << endl;
    }

    cout << "Average Waiting Time: " << avgwt << endl;
    cout << "Average Turn around Time: " << avgtat << endl;
}

int main() {
    vector<Process> processes = {
        {"P1", 0, 5},
        {"P2", 1, 3},
        {"P3", 2, 8},
        {"P4", 3, 6}
    };

    int quantumTime = 3;
    roundrobinScheduling(processes, quantumTime);

    return 0;
}
