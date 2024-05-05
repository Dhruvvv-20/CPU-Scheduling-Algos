#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int p, r, x;
    cout << "Enter number of processes: ";
    cin >> p;
    cout << "Enter number of resources: ";
    cin >> r;
    int remain = p;
    vector<vector<int>> allocation(p, vector<int>(r)), maximum(p, vector<int>(r)), need(p, vector<int>(r));
    vector<int> available(r);
    vector<string> safe_sequence;

    for (int i = 0; i < p; i++)
    {
        cout << "Enter allocated resources for P" << i << " : ";
        for (int j = 0; j < r; j++)
        {
            cin >> allocation[i][j];
        }
        cout << "Enter maximum resources for P" << i << " : ";
        for (int j = 0; j < r; j++)
        {
            cin >> maximum[i][j];
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
        cout << endl;
    }
    cout << "Enter available resources: ";
    for (int j = 0; j < r; j++)
    {
        cin >> available[j];
    }
    cout << endl;

    cout << "Enter number of processes requesting for additional resources: ";
    cin >> x;
    vector<vector<int>> request(x, vector<int>(r));
    for (int i = 0; i < x; i++)
    {
        int pid;
        cout << "Enter process id of demanding process" << i << " : P";
        cin >> pid;
        cout << "Enter resources additionally required by P" << pid << " : ";
        for (int j = 0; j < r; j++)
        {
            cin >> request[i][j];
            allocation[pid][j] += request[i][j];
            available[j] -= request[i][j];
            need[pid][j] -= request[i][j];
            if (allocation[pid][j] > maximum[pid][j] || available[j] < 0)
            {
                cout << "Invalid request!!!";
                exit(0);
            }
        }
    }

    cout << "Resources:\t";
    for (char ch = 'A'; ch < 'A' + r; ch++)
    {
        cout << ch << "\t";
    }
    cout << endl;

    cout << "Available:\t";
    for (int j = 0; j < r; j++)
    {
        cout << available[j] << "\t";
    }
    cout << endl;
    while (true)
    {
        bool deadlock = true;
        for (int i = 0; i < p; i++)
        {
            bool canExecute = true;
            for (int j = 0; j < r; j++)
            {
                if (available[j] < need[i][j])
                {
                    canExecute = false;
                    break;
                }
            }
            if (canExecute)
            {
                deadlock = false;
                for (int j = 0; j < r; j++)
                {
                    available[j] += allocation[i][j];
                    need[i][j] = INT8_MAX;
                }
                cout << "P" << i << " released:\t";
                for (int j = 0; j < r; j++)
                {
                    cout << allocation[i][j] << "\t";
                }
                cout << endl;
                cout << "Process P" << i << " executed." << endl;
                safe_sequence.push_back("P" + to_string(i));
                cout << "Available:\t";
                for (int j = 0; j < r; j++)
                {
                    cout << available[j] << "\t";
                }
                cout << endl;
                remain--;
                break;
            }
        }
        if (deadlock && remain > 0)
        {
            cout << "Deadlock detected!" << endl;
            break;
        }
        if (remain == 0)
        {
            cout << "All processes executed successfully." << endl;
            cout << "Safe sequence: < ";
            for (auto it : safe_sequence)
            {
                cout << it << " ";
            }
            cout << ">" << endl;
            cout << "No deadlock detected." << endl;
            break;
        }
    }
    return 0;
}