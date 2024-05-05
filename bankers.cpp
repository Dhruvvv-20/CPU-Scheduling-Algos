#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, r;
    cout << "Enter the number of processes: ";
    cin >> n;
    cout << "Enter the number of resources: ";
    cin >> r;
    
    int allocation[n][r], max[n][r], avail[r];

    cout << "Enter the allocation matrix:\n";
    for (int i = 0; i < n; i++) {
        cout << "For process " << i << ":\n";
        for (int j = 0; j < r; j++) {
            cin >> allocation[i][j];
        }
    }

    cout << "Enter the max matrix:\n";
    for (int i = 0; i < n; i++) {
        cout << "For process " << i << ":\n";
        for (int j = 0; j < r; j++) {
            cin >> max[i][j];
        }
    }

    cout << "Enter the available resources:\n";
    for (int i = 0; i < r; i++) {
        cin >> avail[i];
    }

    int need[n][r];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < r; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    int f[n], ans[n], ind = 0;
    for (int i = 0; i < n; i++) {
        f[i] = 0;
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if (f[i] == 0) {
                int flag = 0;
                for (int j = 0; j < r; j++) {
                    if (need[i][j] > avail[j]) {
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0) {
                    ans[ind++] = i;
                    for (int y = 0; y < r; y++) {
                        avail[y] += allocation[i][y];
                    }
                    f[i] = 1;
                }
            }
        }
    }

    cout << "The Safe Sequence is: " << endl;
    for (int i = 0; i < n; i++) {
        cout << "P" << ans[i];
        if (i != n - 1) cout << " -> ";
    }

    return 0;
}
