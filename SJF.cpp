#include <iostream> 
#include <vector> 
#include <algorithm>

using namespace std;


struct Process { int id;
int arrivalTime; 
int burstTime;
int completionTime;
};


bool compareArrivalTime(const Process &a, const Process &b) { 
    return a.arrivalTime < b.arrivalTime;
}


bool compareBurstTime(const Process &a, const Process &b) { 
    return a.burstTime < b.burstTime;
}


int main() { 
    int n;
cout << "Enter the number of processes: "; cin >> n;

vector<Process> processes(n); for (int i = 0; i < n; ++i) {
processes[i].id = i + 1;
 
cout << "Enter arrival time for Process " << i + 1 << ": "; cin >> processes[i].arrivalTime;
cout << "Enter burst time for Process " << i + 1 << ": "; cin >> processes[i].burstTime;
}


sort(processes.begin(), processes.end(), compareArrivalTime);


int currentTime = 0;
double totalWaitingTime = 0; double schedulingLength = 0;

cout << "P\tAT\tBT\tCT\tTAT\tWT\n";


for (int i = 0; i < n; ++i) {
sort(processes.begin() + i, processes.end(), compareBurstTime);
processes[i].completionTime = max(currentTime, processes[i].arrivalTime) + processes[i].burstTime; 
int waitingTime = max(0, currentTime - processes[i].arrivalTime);
totalWaitingTime += waitingTime; 
schedulingLength += processes[i].burstTime;
cout << processes[i].id << "\t" << processes[i].arrivalTime << "\t"
<< processes[i].burstTime << "\t" << processes[i].completionTime << "\t"
<< processes[i].completionTime - processes[i].arrivalTime << "\t"
<< waitingTime << endl;
currentTime = processes[i].completionTime;
}


double throughput = n / schedulingLength;
double averageWaitingTime = totalWaitingTime / n;


cout << "\nAverage Waiting Time: " << averageWaitingTime << endl;
cout << "Scheduling Length: " << schedulingLength << " time units" << endl; cout << "Throughput: " << throughput << " processes per unit of time" << endl;
 
return 0;
}
