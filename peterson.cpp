

#include <iostream>
#include <thread>
using namespace std;
int turn = 0;
int flag[2] = {0};
int c = 0, in = 0, out = 0;
int buffer[10];
void lock(int p)
{
int other = 1 - p;
flag[p] = 1;
turn = p;
while (flag[other] == 1 && turn == p);
}
void unlock(int p)
{
flag[p] = 0;
}
void display()
{
cout << "The buffer is: ";
for (int i = 0; i < 10; i++)
{
cout << buffer[i] << " ";
}
cout << endl;
}
void producer()
{
for (int i = 0; i < 20; i++)
{
while (c == 10);
lock(0);
buffer[in] = 100 + i * 2;
cout << "producer produced: " << buffer[in] << endl;
in = (in + 1) % 10;
c++;
display();
unlock(0);
}
}
void consumer()
{
for (int i = 0; i < 20; i++)
{
while (c == 0);
lock(1);
int k = buffer[out];
cout << "Consumer consumed: " << k << endl;
buffer[out] = 0;
out = (out + 1) % 10;
c--;
display();
unlock(1);
}
}
int main()
{
thread t1(producer);
thread t2(consumer);
t1.join();
t2.join();
}
