#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 磁盘请求的数据结构
struct Request {
    int track; // 磁道号
};

// 请求队列
vector<Request> requestQueue;
vector<Request> requestQueue1;
// 添加请求到请求队列
void addRequest(int track) {
    Request request;
    request.track = track;
    requestQueue.push_back(request);
    requestQueue1.push_back(request);
}

// 执行磁盘调度算法（扫描算法）
void C_LOOK(int startTrack) {
    // 按磁道号排序请求队列
    sort(requestQueue.begin(), requestQueue.end(), [](const Request& r1, const Request& r2) {
        return r1.track < r2.track;
    });

    // 寻道方向（1：向外，-1：向内）
    int direction = 1;

    // 寻道过程
    int currentTrack = startTrack;
    int totalDistance = 0;
    int totalRequests = requestQueue.size();
    while (!requestQueue.empty()) {
        // 寻找下一个最近的请求
        int nextTrack = -1;
        for (const Request& request : requestQueue) {
            if ((direction == 1 && request.track >= currentTrack) || (direction == -1 && request.track <= currentTrack)) {
                nextTrack = request.track;
                break;
            }
        }

        // 如果没有找到下一个请求，则改变寻道方向
        if (nextTrack == -1) {
            direction *= -1;
            continue;
        }
        
        int distance = abs(nextTrack - currentTrack);
        totalDistance += distance;

        // 移动磁头
        currentTrack = nextTrack;

        // 删除已处理的请求
        auto it = find_if(requestQueue.begin(), requestQueue.end(), [&](const Request& request) {
            return request.track == nextTrack;
        });
        if (it != requestQueue.end()) {
            requestQueue.erase(it);
        }

        // 打印处理的请求
        cout << "当前磁道: " << currentTrack << endl;
    }

    // 输出统计信息
    cout << "总移动磁道数: " << totalDistance << endl;
    cout << "平均寻道时间: " << static_cast<double>(totalDistance) / totalRequests << endl;
}
// 执行磁盘调度算法（先来先服务）
void FCFS(int startTrack) {
    int currentTrack = startTrack;
    int totalDistance = 0;
    int totalRequests = requestQueue1.size();
    for (const Request& request : requestQueue1) {
        int distance = abs(request.track - currentTrack);
        totalDistance += distance;
        currentTrack = request.track;
        cout << "当前磁道: " << currentTrack << endl;
    }

    // 输出统计信息
    cout << "总移动磁道数: " << totalDistance << endl;
    cout << "平均寻道时间: " << static_cast<double>(totalDistance) / totalRequests << endl;
}
int main() {
    // 添加一些示例请求
   
   int n;
   cout << "磁道数：" << endl;
   cin >> n;
   int x;
   cout << "请输入磁道序列：" << endl;
   for(int i = 0; i < n; i++)
   {
       cin >> x;
       addRequest(x);
   } 

    // 执行磁盘调度算法，初始磁道号为50，最大磁道号为199
    cout << "请输入初始磁道号：" << endl;
    int initial;
    cin >> initial;
    
    cout << "请输入最大磁道号：" << endl;
    int maxTrack;
    cin >> maxTrack;
    
    cout<<"C-LOOK:"<<endl; 
    C_LOOK(initial);
    
    cout<<"FCFS:"<<endl;
    FCFS(initial);
    
    return 0;
}

