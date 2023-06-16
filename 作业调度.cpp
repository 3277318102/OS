#include <iostream>
#include <vector>

using namespace std;

struct Job {
    int id;
    int aT;
    int eT;
    int wT;
    int rT;
};

void simulateFCFS(vector<Job>& jobs) {
    int currentTime = 0;
    double totalwT = 0;
    double totalrT = 0;

    for (int i = 0; i < jobs.size(); i++) {
        if (currentTime < jobs[i].aT) {
            currentTime = jobs[i].aT;
        }

        jobs[i].wT = currentTime - jobs[i].aT;
        jobs[i].rT = jobs[i].wT + jobs[i].eT;

        totalwT += jobs[i].wT;
        totalrT += jobs[i].rT;

        currentTime += jobs[i].eT;
    }

    int numJobs = jobs.size();
    double averagewT = totalwT / numJobs;
    double averagerT = totalrT / numJobs;

    cout << "作业调度结果：" << endl;
    cout << "作业\t到达时间\t需要处理机时间\t等待时间\t周转时间" << endl;

    for (int i = 0; i < numJobs; i++) {
        cout << jobs[i].id << "\t" << jobs[i].aT << "\t\t" << jobs[i].eT << "\t\t"
             << jobs[i].wT << "\t\t" << jobs[i].rT << endl;
    }

    cout << "平均等待时间： " << averagewT << endl;
    cout << "平均周转时间： " << averagerT << endl;
}

int main() {
    vector<Job> jobs = {
        {1, 0, 6, 0, 0},
        {2, 2, 8, 0, 0},
        {3, 4, 4, 0, 0}
    };

    simulateFCFS(jobs);

    return 0;
}

