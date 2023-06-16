#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int st[3]={0};
int findMAXIndex(int st[])
{
	int j,temp=-2;
	for(int i=0;i<3;i++)
	{
		if(st[i]>temp)
		{
			temp=st[i];
			j=i;
		}
	}
	return j;
}
double CLOCKfaultRate,FIFOfaultRate,LRUfaultRate;
// FIFO实验
void FIFO(vector<int>& pageAccessSequence, int numFrames) {
    int pageFaults = 0;  // 缺页次数

    // 页面表
    vector<int> pageTable(numFrames, -1);

    // 页面框队列，用于实现FIFO算法
    vector<int> frameQueue(numFrames, -1);
    int front = 0;  // 队列头部索引
    int rear = 0;   // 队列尾部索引

    for (int i = 0; i < pageAccessSequence.size(); i++) {
        int page = pageAccessSequence[i];

        // 检查页面是否在页面表中
        bool found = false;
        for (int j = 0; j < numFrames; j++) {
            if (pageTable[j] == page) {
                found = true;
                break;
            }
        }

        if (!found) {
            // 页面不在页面表中，产生缺页中断
            pageFaults++;

            if (frameQueue[front] != -1) {
                // 从页面表中移除最早进入的页面
                pageTable[frameQueue[front]] = -1;
            }

            // 将新页面添加到页面表和队列中
            pageTable[rear] = page;
            frameQueue[rear] = rear;

            // 更新队列索引
            rear = (rear + 1) % numFrames;
            front = (front + 1) % numFrames;
        }

        // 输出当前页面访问序列和页面表
        cout << "当前页面: " << page << endl;
        cout << "页表序列: ";
        for (int j = 0; j < numFrames; j++) {
            cout << pageTable[j] << " ";
        }
        cout << endl;
        cout << "---------------------" << endl;
    }

    // 输出缺页率
    FIFOfaultRate = static_cast<double>(pageFaults) / pageAccessSequence.size();
    cout << "FIFO缺页率: " << FIFOfaultRate << endl;
}
//LRU
void LRU(vector<int>& pageAccessSequence, int numFrames) {
    int pageFaults = 0; // 缺页次数

    // 页面表
    vector<int> pageTable(numFrames, -1);

    // 页面框队列，用于实现LRU算法
    vector<int> frameQueue;

    int newIndex = 0;
    for (int i = 0; i < pageAccessSequence.size(); i++) {
        int page = pageAccessSequence[i];

        // 检查页面是否在页面表中
        auto it = find(pageTable.begin(), pageTable.end(), page);
        if (it != pageTable.end()) {
            // 页面在页面表中，更新页面框队列
            int index = distance(pageTable.begin(), it);
            st[index]=0;
            frameQueue.erase(remove(frameQueue.begin(), frameQueue.end(), index), frameQueue.end());
            frameQueue.push_back(index);
        } else {
            // 页面不在页面表中，产生缺页中断
            pageFaults++;
            //int oldestPage = findMAXIndex(st);
            //cout<<oldestPage<<endl;
            if (frameQueue.size() == numFrames) {
                // 页面框已满，移除最近最久未使用的页面
                //cout<<frameQueue.front();
                int oldestPage = findMAXIndex(st);
                st[oldestPage]=0;
                //frameQueue.erase(frameQueue.begin());
                pageTable[oldestPage] = page;
            }
            else
            {
            	pageTable[newIndex] = page;
                frameQueue.push_back(newIndex);
                if(newIndex<3)
            	   newIndex++;
			}

        }

        // 输出当前页面访问序列和页面表
        cout << "当前页面: " << page << endl;
        cout << "页表序列: ";
        for (int j = 0; j < numFrames; j++) {
            cout << pageTable[j] << " ";
        }
        cout << endl;
        cout << "---------------------" << endl;
        for(int i=0;i<3;i++)
        {
        	if(pageTable[i]!=-1)
        	{
        		st[i]++;
			}
		}
    }

    // 输出缺页率
    LRUfaultRate = static_cast<double>(pageFaults) / pageAccessSequence.size();
    cout << "LRU缺页率: " << LRUfaultRate << endl;
}

//clock算法
void CLOCK(vector<int>& pageAccessSequence, int numFrames) {
    int pageFaults = 0; // 缺页次数

    // 页面表
    vector<int> pageTable(numFrames, -1);

    // 记录页面是否被访问的位图
    vector<bool> pageReferenceBit(numFrames, false);

    // 页面指针，指向当前应替换的页面
    int pointer = 0;

    for (int i = 0; i < pageAccessSequence.size(); i++) {
        int page = pageAccessSequence[i];

        // 检查页面是否在页面表中
        auto it = find(pageTable.begin(), pageTable.end(), page);
        if (it != pageTable.end()) {
            // 页面在页面表中，设置页面的访问位为true
            int index = distance(pageTable.begin(), it);
            pageReferenceBit[index] = true;
        } else {
            // 页面不在页面表中，产生缺页中断
            pageFaults++;

            while (true) {
                // 查找下一个可以替换的页面
                if (pageReferenceBit[pointer] == false) {
                    // 如果页面的访问位为false，替换该页面
                    pageTable[pointer] = page;
                    pageReferenceBit[pointer] = true;
                    pointer = (pointer + 1) % numFrames;
                    break;
                } else {
                    // 页面的访问位为true，将其设置为false，指针向后移动
                    pageReferenceBit[pointer] = false;
                    pointer = (pointer + 1) % numFrames;
                }
            }
        }

        // 输出当前页面访问序列和页面表
        cout << "当前页面: " << page << endl;
        cout << "页表序列: ";
        for (int j = 0; j < numFrames; j++) {
            cout << pageTable[j] << " ";
        }
        cout << endl;
        cout << "---------------------" << endl;
    }

    // 输出缺页率
    CLOCKfaultRate = static_cast<double>(pageFaults) / pageAccessSequence.size();
    cout << "CLOCK缺页率: " << CLOCKfaultRate << endl;
}
 
int main() {
    // 页面访问序列
    vector<int> pageAccessSequence = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
    int numFrames = 3;

    // FIFO
    cout<<"FIFO算法：(-1表示当前页面为空)"<<endl; 
    FIFO(pageAccessSequence, numFrames);
    cout<<endl;
    // LRU
    cout<<"LRU算法：（-1表示当前页面为空）"<<endl;
    LRU(pageAccessSequence, numFrames);
    cout<<endl;
	// CLOCK
	cout<<"CLOCK算法：-1表示当前页面为空）"<<endl; 
	CLOCK(pageAccessSequence, numFrames);
    return 0;
}


