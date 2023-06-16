#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// ������������ݽṹ
struct Request {
    int track; // �ŵ���
};

// �������
vector<Request> requestQueue;
vector<Request> requestQueue1;
// ��������������
void addRequest(int track) {
    Request request;
    request.track = track;
    requestQueue.push_back(request);
    requestQueue1.push_back(request);
}

// ִ�д��̵����㷨��ɨ���㷨��
void C_LOOK(int startTrack) {
    // ���ŵ��������������
    sort(requestQueue.begin(), requestQueue.end(), [](const Request& r1, const Request& r2) {
        return r1.track < r2.track;
    });

    // Ѱ������1�����⣬-1�����ڣ�
    int direction = 1;

    // Ѱ������
    int currentTrack = startTrack;
    int totalDistance = 0;
    int totalRequests = requestQueue.size();
    while (!requestQueue.empty()) {
        // Ѱ����һ�����������
        int nextTrack = -1;
        for (const Request& request : requestQueue) {
            if ((direction == 1 && request.track >= currentTrack) || (direction == -1 && request.track <= currentTrack)) {
                nextTrack = request.track;
                break;
            }
        }

        // ���û���ҵ���һ��������ı�Ѱ������
        if (nextTrack == -1) {
            direction *= -1;
            continue;
        }
        
        int distance = abs(nextTrack - currentTrack);
        totalDistance += distance;

        // �ƶ���ͷ
        currentTrack = nextTrack;

        // ɾ���Ѵ��������
        auto it = find_if(requestQueue.begin(), requestQueue.end(), [&](const Request& request) {
            return request.track == nextTrack;
        });
        if (it != requestQueue.end()) {
            requestQueue.erase(it);
        }

        // ��ӡ���������
        cout << "��ǰ�ŵ�: " << currentTrack << endl;
    }

    // ���ͳ����Ϣ
    cout << "���ƶ��ŵ���: " << totalDistance << endl;
    cout << "ƽ��Ѱ��ʱ��: " << static_cast<double>(totalDistance) / totalRequests << endl;
}
// ִ�д��̵����㷨�������ȷ���
void FCFS(int startTrack) {
    int currentTrack = startTrack;
    int totalDistance = 0;
    int totalRequests = requestQueue1.size();
    for (const Request& request : requestQueue1) {
        int distance = abs(request.track - currentTrack);
        totalDistance += distance;
        currentTrack = request.track;
        cout << "��ǰ�ŵ�: " << currentTrack << endl;
    }

    // ���ͳ����Ϣ
    cout << "���ƶ��ŵ���: " << totalDistance << endl;
    cout << "ƽ��Ѱ��ʱ��: " << static_cast<double>(totalDistance) / totalRequests << endl;
}
int main() {
    // ���һЩʾ������
   
   int n;
   cout << "�ŵ�����" << endl;
   cin >> n;
   int x;
   cout << "������ŵ����У�" << endl;
   for(int i = 0; i < n; i++)
   {
       cin >> x;
       addRequest(x);
   } 

    // ִ�д��̵����㷨����ʼ�ŵ���Ϊ50�����ŵ���Ϊ199
    cout << "�������ʼ�ŵ��ţ�" << endl;
    int initial;
    cin >> initial;
    
    cout << "���������ŵ��ţ�" << endl;
    int maxTrack;
    cin >> maxTrack;
    
    cout<<"C-LOOK:"<<endl; 
    C_LOOK(initial);
    
    cout<<"FCFS:"<<endl;
    FCFS(initial);
    
    return 0;
}

