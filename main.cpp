#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//structure to represente a process
struct Process {
    string ID; //
    int at; //arrival time: time in which the process got there
    int bt; //burst time: processing time on the cpu
    int ct; //completion time: time that the process finishes. ct = at + bt
    int tat; //turn around time: total time execution of a process. tat = ct - at
    int wt; //waiting time: time that the process waits to be executed. wt = tat - bt
};
//method that takes each process and executes it
void fcfsSchduling(vector<Process>& processes) {
    int n = processes.size(); // Tamaño del arreglo de procesos
    int totalWaitingTime = 0, totalTurnAroundTime = 0;

    // Ordenamos los procesos por tiempo de llegada
    sort(processes.begin(), processes.end(), [](Process a, Process b) {
        return a.arrivalTime < b.arrivalTime;
    });

    // Calculamos los tiempos de finalización, retorno y espera del primer proceso
    processes[0].completionTime = processes[0].arrivalTime + processes[0].burstTime;
    processes[0].turnAroundTime = processes[0].completionTime - processes[0].arrivalTime;
    processes[0].waitingTime = 0;

    // Calculamos los tiempos de finalización, retorno y espera de los demás procesos
    for (int i = 1; i < n; i++){
        processes[i].completionTime = max(processes[i-1].completionTime, processes[i-1].arrivalTime) + processes[i].burstTime;
        processes[i].turnAroundTime = processes[i].completionTime - processes[i].arrivalTime;
        processes[i].waitingTime = processes[i].turnAroundTime - processes[i].burstTime;

        // Calcular sumas totales
        totalWaitingTime += processes[i].waitingTime;
        totalTurnAroundTime += processes[i].turnAroundTime;
    }

    // Mostramos los resultados
    cout << "Proceso\tLlegada\tEjecución\tFinalización\tRetorno\tEspera\n";
    for(const auto& p : processes){
        cout << p.id << "\t" << p.arrivalTime << "\t" << p.burstTime
             << "\t\t" << p.completionTime << "\t\t" << p.turnAroundTime
             << "\t" << p.waitingTime << endl;
    }

    // Calculamos y mostramos los tiempos promedio
    cout << "\nTiempo promedio de espera: " << (float)totalWaitingTime / n << " unidades" << endl;
    cout << "Tiempo promedio de retorno: " << (float)totalTurnAroundTime / n << " unidades" << endl;
}

int main() {
    vector<Process> processes = {
            {"P1", 0, 5},
            {"P2", 1, 3},
            {"P3", 2, 8},
            {"P4", 3, 6}
    };

    // Ejecutar la planificación FCFS
    fcfsSheduling(processes);

    return 0;
}
