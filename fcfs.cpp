#include <iostream>
#include <vector>
using namespace std;

struct Process{
    int pid;
    int AT;
    int BT;
    int CT;
    int TAT;
    int WT;
};

void find_CT(Process proc[], int n){
    proc[0].CT = proc[0].BT;
    for (int i = 1;i<n;i++)
    {
        proc[i].CT = proc[i-1].CT + proc[i].BT;

    }

}

void find_TAT(Process proc[], int n){
    for(int i = 0;i<n;i++)
    {
        proc[i].TAT = proc[i].CT - proc[i].AT;
        
    }
}

void find_WT(Process proc[], int n){

    for(int i = 0;i<n;i++)
    {
        proc[i].WT = proc[i].TAT - proc[i].BT;
    }
}

void find_FCFS(vector<Process> &proc, int n){
    find_CT(proc.data(), n);
    find_TAT(proc.data(), n);
    find_WT(proc.data(), n);
}


void print_FCFS(vector<Process> &proc, int n){
    int total_tat = 0;
    cout << "FCFS Scheduling : " <<endl;
    cout << "PID\t" << "AT\t" << "BT\t" << "CT\t" << "TAT\t" << "WT\t"<<endl;
    for(int i = 0;i<n;i++){
        cout << proc[i].pid << "\t" << proc[i].AT << "\t" << proc[i].BT << "\t" << proc[i].CT << "\t" << proc[i].TAT << "\t" << proc[i].WT << "\t" << endl;
        total_tat = total_tat + proc[i].TAT;
    }
    cout << "Average TAT = " << total_tat/n <<endl;
    cout << "Scheduling Length = " << proc[n-1].CT - proc[0].AT<<endl;
    cout << "Throughput = "<< (proc[n-1].CT - proc[0].AT)/n<<endl;

    cout << "Gantt Chart : "<<endl;
    int nexttime = 1;
    for(int i = 0 ; i < n ; i++){
        cout << "P" << nexttime++ << " " << proc[i].CT << " | ";
    }
}



int main(){
    int n;
    cout << "Enter the number of processes : ";
    cin >> n;
    if(n == 0){
        cout << "The number of processes cant be zero"<<endl;
    }
    vector<Process> proc;
    for(int j = 0; j < n; j++){
        Process temp; 
        cout << "Enter the Process ID: ";
        cin >> temp.pid;
        cout << "Enter the AT: ";
        cin >> temp.AT;
        cout << "Enter the BT: ";
        cin >> temp.BT;
        proc.push_back(temp); 
    }
    
    find_FCFS(proc, n);
    print_FCFS(proc, n);

    return 0;
}
