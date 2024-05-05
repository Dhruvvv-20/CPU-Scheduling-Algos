#include <iostream>
using namespace std;


int turn = 0;
int flag[2] = {0,0};
int process_id = 0;


void peterson(int process_id){
    while(1){
        flag[process_id] = 1;
        turn = 1 - process_id;
        while(turn == 1 - process_id && flag[1-process_id] == 1 );
        cout << "The process inside critical section is : " << process_id << endl;
        flag[process_id] = 0;
    }
}

int main(){
    peterson(0);
    peterson(1);
    return 0;
}

