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
// FIFOʵ��
void FIFO(vector<int>& pageAccessSequence, int numFrames) {
    int pageFaults = 0;  // ȱҳ����

    // ҳ���
    vector<int> pageTable(numFrames, -1);

    // ҳ�����У�����ʵ��FIFO�㷨
    vector<int> frameQueue(numFrames, -1);
    int front = 0;  // ����ͷ������
    int rear = 0;   // ����β������

    for (int i = 0; i < pageAccessSequence.size(); i++) {
        int page = pageAccessSequence[i];

        // ���ҳ���Ƿ���ҳ�����
        bool found = false;
        for (int j = 0; j < numFrames; j++) {
            if (pageTable[j] == page) {
                found = true;
                break;
            }
        }

        if (!found) {
            // ҳ�治��ҳ����У�����ȱҳ�ж�
            pageFaults++;

            if (frameQueue[front] != -1) {
                // ��ҳ������Ƴ���������ҳ��
                pageTable[frameQueue[front]] = -1;
            }

            // ����ҳ����ӵ�ҳ���Ͷ�����
            pageTable[rear] = page;
            frameQueue[rear] = rear;

            // ���¶�������
            rear = (rear + 1) % numFrames;
            front = (front + 1) % numFrames;
        }

        // �����ǰҳ��������к�ҳ���
        cout << "��ǰҳ��: " << page << endl;
        cout << "ҳ������: ";
        for (int j = 0; j < numFrames; j++) {
            cout << pageTable[j] << " ";
        }
        cout << endl;
        cout << "---------------------" << endl;
    }

    // ���ȱҳ��
    FIFOfaultRate = static_cast<double>(pageFaults) / pageAccessSequence.size();
    cout << "FIFOȱҳ��: " << FIFOfaultRate << endl;
}
//LRU
void LRU(vector<int>& pageAccessSequence, int numFrames) {
    int pageFaults = 0; // ȱҳ����

    // ҳ���
    vector<int> pageTable(numFrames, -1);

    // ҳ�����У�����ʵ��LRU�㷨
    vector<int> frameQueue;

    int newIndex = 0;
    for (int i = 0; i < pageAccessSequence.size(); i++) {
        int page = pageAccessSequence[i];

        // ���ҳ���Ƿ���ҳ�����
        auto it = find(pageTable.begin(), pageTable.end(), page);
        if (it != pageTable.end()) {
            // ҳ����ҳ����У�����ҳ������
            int index = distance(pageTable.begin(), it);
            st[index]=0;
            frameQueue.erase(remove(frameQueue.begin(), frameQueue.end(), index), frameQueue.end());
            frameQueue.push_back(index);
        } else {
            // ҳ�治��ҳ����У�����ȱҳ�ж�
            pageFaults++;
            //int oldestPage = findMAXIndex(st);
            //cout<<oldestPage<<endl;
            if (frameQueue.size() == numFrames) {
                // ҳ����������Ƴ�������δʹ�õ�ҳ��
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

        // �����ǰҳ��������к�ҳ���
        cout << "��ǰҳ��: " << page << endl;
        cout << "ҳ������: ";
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

    // ���ȱҳ��
    LRUfaultRate = static_cast<double>(pageFaults) / pageAccessSequence.size();
    cout << "LRUȱҳ��: " << LRUfaultRate << endl;
}

//clock�㷨
void CLOCK(vector<int>& pageAccessSequence, int numFrames) {
    int pageFaults = 0; // ȱҳ����

    // ҳ���
    vector<int> pageTable(numFrames, -1);

    // ��¼ҳ���Ƿ񱻷��ʵ�λͼ
    vector<bool> pageReferenceBit(numFrames, false);

    // ҳ��ָ�룬ָ��ǰӦ�滻��ҳ��
    int pointer = 0;

    for (int i = 0; i < pageAccessSequence.size(); i++) {
        int page = pageAccessSequence[i];

        // ���ҳ���Ƿ���ҳ�����
        auto it = find(pageTable.begin(), pageTable.end(), page);
        if (it != pageTable.end()) {
            // ҳ����ҳ����У�����ҳ��ķ���λΪtrue
            int index = distance(pageTable.begin(), it);
            pageReferenceBit[index] = true;
        } else {
            // ҳ�治��ҳ����У�����ȱҳ�ж�
            pageFaults++;

            while (true) {
                // ������һ�������滻��ҳ��
                if (pageReferenceBit[pointer] == false) {
                    // ���ҳ��ķ���λΪfalse���滻��ҳ��
                    pageTable[pointer] = page;
                    pageReferenceBit[pointer] = true;
                    pointer = (pointer + 1) % numFrames;
                    break;
                } else {
                    // ҳ��ķ���λΪtrue����������Ϊfalse��ָ������ƶ�
                    pageReferenceBit[pointer] = false;
                    pointer = (pointer + 1) % numFrames;
                }
            }
        }

        // �����ǰҳ��������к�ҳ���
        cout << "��ǰҳ��: " << page << endl;
        cout << "ҳ������: ";
        for (int j = 0; j < numFrames; j++) {
            cout << pageTable[j] << " ";
        }
        cout << endl;
        cout << "---------------------" << endl;
    }

    // ���ȱҳ��
    CLOCKfaultRate = static_cast<double>(pageFaults) / pageAccessSequence.size();
    cout << "CLOCKȱҳ��: " << CLOCKfaultRate << endl;
}
 
int main() {
    // ҳ���������
    vector<int> pageAccessSequence = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
    int numFrames = 3;

    // FIFO
    cout<<"FIFO�㷨��(-1��ʾ��ǰҳ��Ϊ��)"<<endl; 
    FIFO(pageAccessSequence, numFrames);
    cout<<endl;
    // LRU
    cout<<"LRU�㷨����-1��ʾ��ǰҳ��Ϊ�գ�"<<endl;
    LRU(pageAccessSequence, numFrames);
    cout<<endl;
	// CLOCK
	cout<<"CLOCK�㷨��-1��ʾ��ǰҳ��Ϊ�գ�"<<endl; 
	CLOCK(pageAccessSequence, numFrames);
    return 0;
}


