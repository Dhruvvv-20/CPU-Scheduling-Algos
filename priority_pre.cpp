#include <iostream>
#include <vector>

using namespace std;

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int priority;
    int is_completed;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

void schedule(vector<Process> &processes, vector<int> &burst_times, int quanta) {
    int current_time = 0;
    int processes_remaining = processes.size();
    cout<<"Gantt Chart"<<endl;
    while (processes_remaining > 0) {
        int highest_priority = -1;
        int current_process = -1;
        
        for (int i = 0; i < processes.size(); i++) {
            if (processes[i].is_completed == 0 && processes[i].arrival_time <= current_time) {
                if (highest_priority == -1 || processes[i].priority < highest_priority) {
                    highest_priority = processes[i].priority;
                    current_process = i;
                }
            }
        }
        
        if (current_process != -1) {
            if (processes[current_process].burst_time <= quanta) {
                current_time += processes[current_process].burst_time;
                processes_remaining--;
                cout << "P" << processes[current_process].id << " | ";
                processes[current_process].is_completed = 1;
                processes[current_process].completion_time = current_time;
                processes[current_process].turnaround_time = processes[current_process].completion_time -
                                                             processes[current_process].arrival_time;
                processes[current_process].waiting_time = processes[current_process].turnaround_time -
                                                          burst_times[current_process];
            } else {
                current_time += quanta;
                processes[current_process].burst_time -= quanta;
            }
        } else {
            current_time++;
        }
    }
    cout << endl;
}

void print_table(const vector<Process> &processes) {
    cout << "PID    \tAT  \tBT   \tCT   \tTAT   \tWT  \n";
    for (const Process &p : processes) {
        cout << p.id << "\t" << p.arrival_time << "\t\t" << p.burst_time << "\t\t" 
             << p.completion_time << "\t\t" << p.turnaround_time << "\t\t\t" << p.waiting_time << endl;
    }
}

int main() {
    int n, quanta;
    cout << "Enter number of processes: ";
    cin >> n;
    cout << "Enter time quanta: ";
    cin >> quanta;
    
    vector<Process> processes(n);
    vector<int> burst_times(n);
    
    for (int i = 0; i < n; i++) {
        cout << "Enter arrival time, burst time, and priority for process " << i << ": ";
        cin >> processes[i].arrival_time >> processes[i].burst_time >> processes[i].priority;
        burst_times[i] = processes[i].burst_time;
        processes[i].id = i;
        processes[i].is_completed = 0;
    }
    
    schedule(processes, burst_times, quanta);
    print_table(processes);
    
    return 0;
}
