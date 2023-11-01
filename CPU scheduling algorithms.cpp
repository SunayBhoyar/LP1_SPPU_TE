#include <iostream>
#include <bits/stdc++.h>
using namespace std;
#define MAX 999
class job
{
public:
    int arrival, burst, complete, ta, wait, pri;
    // string name;
    int id;

    job()
    {
        arrival = burst = complete = ta = wait = pri = id = 0;
        // name = "";
    }

    void set()
    {
        // cout << "enter name of job :" << endl;
        // cin >> name;
        cout << "enter job id :" << endl;
        cin >> id;
        cout << "enter arrival time :" << endl;
        cin >> arrival;
        cout << "enter burst time :" << endl;
        cin >> burst;
        cout << "enter priority :" << endl;
        cin >> pri;
    }

    // void display()
    // {
    //     cout << id << "\t" << arrival << "\t" << burst << "\t" << complete << "\t" << wait << "\t" << ta << "\t" << pri << endl;
    // }
    friend class scheduling;
};

bool cmpAt(job a, job b)
{
    if (a.arrival < b.arrival)
    {
        return true;
    }
    return false;
}

bool cmpCT(job a, job b)
{
    if (a.complete < b.complete)
    {
        return true;
    }
    return false;
}

// bool c3(job a, job b)
// {
//     if (a.pri < b.pri)
//     {
//         return true;
//     }
//     return false;
// }

class scheduling
{
public:
    int np;
    vector<job> j1;
    scheduling()
    {
        cout << "No of process :" << endl;
        cin >> np;
        for (int i = 0; i < np; i++)
        {
            job temp;
            temp.set();
            j1.push_back(temp);
        }
    }

    void display()
    {
        cout << "\n-------------------------------------------------------------------------------------------------------";
        cout << "\nProcess ID | Arrival Time | Burst Time | Completion Time | Turn-Around Time | Wait Time | Response Time";
        cout << "\n-------------------------------------------------------------------------------------------------------\n";

        for (int i = 0; i < np; i++)
        {
            cout << "    " << j1[i].id << "\t\t" << j1[i].arrival << "\t\t" << j1[i].burst << "\t\t" << j1[i].complete << "\t\t" << j1[i].ta << "\t\t" << j1[i].wait << "\t\t" << endl;
        }
        cout << "-------------------------------------------------------------------------------------------------------\n";
    }

    void FCFS()
    {
        sort(j1.begin(), j1.end(), cmpAt);
        // for first process
        j1[0].complete = j1[0].burst;
        j1[0].ta = j1[0].burst;
        j1[0].wait = 0;
        int completion = j1[0].burst;
        for (int i = 1; i < j1.size(); i++)
        {
            completion += j1[i].burst;
            j1[i].complete = completion;
            j1[i].ta = j1[i].complete - j1[i].arrival;
            j1[i].wait = j1[i].ta - j1[i].burst;
        }
        double awt = 0;
        double att = 0;

        for (int i = 0; i < np; i++)
        {
            awt += j1[i].wait;
        }
        awt /= np;
        cout << "\nAverage Waiting Time: " << awt << " secs";

        for (int i = 0; i < np; i++)
        {
            att += j1[i].ta;
        }
        att /= np;
        cout << "\nAverage Turn-Around Time: " << att << " secs";
        cout << endl;
    }

    void srtf() // sjf preemtive
    {
        int *remaining = new int[np];

        for (int i = 0; i < np; i++)
        {
            remaining[i] = j1[i].burst;
        }

        int current = 0;
        int completedTasks = 0;
        int shortestTask = 0;
        int minBurst = MAX;
        bool active = false;

        while (completedTasks != np)
        {
            for (int j = 0; j < np; j++)
            {
                if (j1[j].arrival <= current && j1[j].burst < minBurst && remaining[j] > 0)
                {
                    shortestTask = j;
                    minBurst = j1[j].burst;
                    active = true;
                }
            }

            if (active == false)
            {
                current++;
                continue;
            }

            minBurst = --remaining[shortestTask];
            if (minBurst == 0)
            {
                minBurst = MAX;
            }

            if (remaining[shortestTask] == 0)
            {
                completedTasks++;
                active = false;
                j1[shortestTask].complete = current + 1;
                j1[shortestTask].ta = j1[shortestTask].complete - j1[shortestTask].arrival;
                j1[shortestTask].wait = j1[shortestTask].ta - j1[shortestTask].burst;

                if (j1[shortestTask].wait < 0)
                {
                    j1[shortestTask].wait = 0;
                }
            }
            current++;
        }
        double awt = 0;
        double att = 0;

        for (int i = 0; i < np; i++)
        {
            awt += j1[i].wait;
        }
        awt /= np;
        cout << "\nAverage Waiting Time: " << awt << " secs";

        for (int i = 0; i < np; i++)
        {
            att += j1[i].ta;
        }
        att /= np;
        cout << "\nAverage Turn-Around Time: " << att << " secs";
        cout << endl;
    }

    void priority()
    {
        int *remaining = new int[np];

        for (int i = 0; i < np; i++)
        {
            remaining[i] = j1[i].burst;
        }
        int current = 0;
        int completedTasks = 0;
        int completionTime = 0;
        int higherPriority = 0;
        int remBurst = 0;
        int maxPriority = MAX;
        bool taskActive = false;

        while (completedTasks != np)
        {
            for (int j = 0; j < np; j++)
            {
                if (j1[j].arrival <= current && remaining[j] > 0 && j1[j].pri < maxPriority)
                {
                    higherPriority = j;
                    maxPriority = j1[j].pri;
                    taskActive = true;
                }
            }

            if (!taskActive)
            {
                current++;
                continue;
            }

            current += j1[higherPriority].burst;
            remaining[higherPriority] = 0;
            maxPriority = MAX;
            taskActive = false;
            completedTasks++;

            j1[higherPriority].complete = current;
            j1[higherPriority].ta = j1[higherPriority].complete - j1[higherPriority].arrival;
            j1[higherPriority].wait = j1[higherPriority].ta - j1[higherPriority].burst;

            double awt = 0;
            double att = 0;

            for (int i = 0; i < np; i++)
            {
                awt += j1[i].wait;
            }
            awt /= np;
            cout << "\nAverage Waiting Time: " << awt << " secs";

            for (int i = 0; i < np; i++)
            {
                att += j1[i].ta;
            }
            att /= np;
            cout << "\nAverage Turn-Around Time: " << att << " secs";
            cout << endl;
        }
    }

    // round robin algorithm (preemptive by nature)
    void roundRobin(int tq)
    {
        // tq is qauntum time is time allocated by CPU to each process
        queue<int> ready;

        int current = 0;
        int completedTasks = 0;
        int curr;

        int *remaining = new int[np];
        for (int i = 0; i < np; i++)
        {
            remaining[i] = j1[i].burst;
        }

        for (int j = 0; j < np; j++)
        {
            if (j1[j].arrival <= current)
            {
                ready.push(j);
            }
        }

        while (completedTasks != np)
        {
            curr = ready.front();
            ready.pop();

            int counter = 0;

            while (counter != tq && counter != remaining[curr])
            {
                current++;
                counter++;

                for (int j = 0; j < np; j++)
                {
                    if (j1[j].arrival == current)
                    {
                        ready.push(j);
                    }
                }
            }

            remaining[curr] -= counter;

            if (remaining[curr] == 0)
            {
                j1[curr].complete = current;
                j1[curr].ta = j1[curr].complete - j1[curr].arrival;
                j1[curr].wait = j1[curr].ta - j1[curr].burst;
                completedTasks++;
            }
            else
            {
                ready.push(curr);
            }
        }
        double awt = 0;
        double att = 0;

        for (int i = 0; i < np; i++)
        {
            awt += j1[i].wait;
        }
        awt /= np;
        cout << "\nAverage Waiting Time: " << awt << " secs";

        for (int i = 0; i < np; i++)
        {
            att += j1[i].ta;
        }
        att /= np;
        cout << "\nAverage Turn-Around Time: " << att << " secs";
        cout << endl;
    }
};
int main()
{
    scheduling s;
    int ch, tq; // tq is quantum time
    char ans = 'y';

    do
    {
        cout<<"\nChoose algorithm: \n1. FCFS\n2. SRTF\n3. Priority\n4. Round Robin\n\nEnter choice: ";
        cin>>ch;

        switch(ch)
        {
            case 1:
            s.FCFS();
            s.display();
            break;

            case 2:
            s.srtf();
            s.display();
            break;

            case 3:
            s.priority();
            s.display();
            break;

            case 4:
            cout<<"\nEnter time quantum: ";
            cin>>tq;
            s.roundRobin(tq);
            s.display();
            break;            

            default:
            cout<<"\nInvalid choice!";
            break;
        }
    } while (ans=='y' || ans=='Y');
    return 0;
}



