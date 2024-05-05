#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int completionTime;
};

bool compareArrivalTime(const Process &a, const Process &b) {
    return a.arrivalTime < b.arrivalTime;
}

int main() {
    int n, quantum;
    vector<int> gant;
    cout << "Enter the number of processes: ";
    cin >> n;
    cout << "Enter the time quantum: ";
    cin >> quantum;

    vector<Process> processes(n);
    for (int i = 0; i < n; ++i) {
        processes[i].id = i + 1;
        cout << "Enter arrival time for Process " << i + 1 << ": ";
        cin >> processes[i].arrivalTime;
        cout << "Enter burst time for Process " << i + 1 << ": ";
        cin >> processes[i].burstTime;
        processes[i].remainingTime = processes[i].burstTime;
    }

    sort(processes.begin(), processes.end(), compareArrivalTime);

    int currentTime = 0;
    double totalWaitingTime = 0;
    double schedulingLength = 0;

    cout << "P\tAT\tBT\tCT\tTAT\tWT\n";

    queue<Process> readyQueue;
    int idx = 0;

    while (idx < n || !readyQueue.empty()) {
        while (idx < n && processes[idx].arrivalTime <= currentTime) {
            readyQueue.push(processes[idx]);
            idx++;
        }

        if (!readyQueue.empty()) {
            Process currentProcess = readyQueue.front();
            readyQueue.pop();

            int executionTime = min(quantum, currentProcess.remainingTime);
            currentTime += executionTime;
            currentProcess.remainingTime -= executionTime;
            
            gant.push_back(idx);

            if (currentProcess.remainingTime == 0) {
                currentProcess.completionTime = currentTime;
                
                int waitingTime = currentProcess.completionTime - currentProcess.arrivalTime - currentProcess.burstTime;
                totalWaitingTime += waitingTime;
                schedulingLength += currentProcess.burstTime;
                
                cout << currentProcess.id << "\t" << currentProcess.arrivalTime << "\t"
                     << currentProcess.burstTime << "\t" << currentProcess.completionTime << "\t"
                     << currentProcess.completionTime - currentProcess.arrivalTime << "\t"
                     << waitingTime << endl;
            } else {
                readyQueue.push(currentProcess);
            }
        } else {
            currentTime = processes[idx].arrivalTime;
        }
    }

    double throughput = n / schedulingLength;
    double averageWaitingTime = totalWaitingTime / n;
    cout << "Gantt Chart"<<endl;
    for (int i = 0; i < gant.size(); i++)
        cout << gant[i] << "|";
    cout << endl;

    cout << "\nAverage Waiting Time: " << averageWaitingTime << endl;
    cout << "Scheduling Length: " << schedulingLength << " time units" << endl;
    cout << "Throughput: " << throughput << " processes per unit of time" << endl;

    return 0;
}
