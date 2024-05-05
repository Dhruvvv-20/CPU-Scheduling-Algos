#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int priority;
    int completionTime;
};

bool compareArrivalTime(const Process &a, const Process &b) {
    return a.arrivalTime < b.arrivalTime;
}

struct ComparePriority {
    bool operator()(const Process &a, const Process &b) {
        return a.priority > b.priority;
    }
};

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    for (int i = 0; i < n; ++i) {
        processes[i].id = i + 1;
        cout << "Enter arrival time for Process " << i + 1 << ": ";
        cin >> processes[i].arrivalTime;
        cout << "Enter burst time for Process " << i + 1 << ": ";
        cin >> processes[i].burstTime;
        cout << "Enter priority for Process " << i + 1 << ": ";
        cin >> processes[i].priority;
    }

    sort(processes.begin(), processes.end(), compareArrivalTime);

    int currentTime = 0;
    double totalWaitingTime = 0;
    double schedulingLength = 0;

    cout << "P\tAT\tBT\tCT\tTAT\tWT\t\n";

    priority_queue<Process, vector<Process>, ComparePriority> pq;
    int idx = 0;
    vector<int> gantt;

    while (idx < n || !pq.empty()) {
        while (idx < n && processes[idx].arrivalTime <= currentTime) {
            pq.push(processes[idx]);
            idx++;
        }

        if (!pq.empty()) {
            Process currentProcess = pq.top();
            pq.pop();

            currentTime += currentProcess.burstTime;
            currentProcess.completionTime = currentTime;

            int waitingTime = currentProcess.completionTime - currentProcess.arrivalTime - currentProcess.burstTime;
            totalWaitingTime += waitingTime;
            schedulingLength += currentProcess.burstTime;

            cout << currentProcess.id << "\t" << currentProcess.arrivalTime << "\t"
                 << currentProcess.burstTime << "\t" << currentProcess.completionTime << "\t"
                 << currentProcess.completionTime - currentProcess.arrivalTime << "\t"
                 << waitingTime << "\t";
            cout <<endl;
            cout <<endl;

            // Add Gantt chart
            for (int i = 0; i < currentProcess.burstTime; ++i) {
                gantt.push_back(currentProcess.id);
            }
        } else {
            currentTime = processes[idx].arrivalTime;
        }
    }

    // Print Gantt chart
    int nexttime = 0;
    cout << "Gantt Chart" << endl;
    for (int id : gantt) {
        cout << "P" << id << " " << nexttime << "|"<<"";
    }
    cout << endl;

    double throughput = n / schedulingLength;
    double averageWaitingTime = totalWaitingTime / n;

    cout << "\nAverage Waiting Time: " << averageWaitingTime << endl;
    cout << "Scheduling Length: " << schedulingLength << " time units" << endl;
    cout << "Throughput: " << throughput << " processes per unit of time" << endl;

    return 0;
} 
