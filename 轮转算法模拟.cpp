#include <iostream>
#include <queue>
#include <iomanip>
using namespace std;
 
//���ÿ��������Ϣ�Ľṹ��
struct PROCESS{
    char name;
    double AT;//����ʱ��
    double ST;//����ʱ��
    double FT;//���ʱ��
    double WT;//��תʱ��
};
 
queue<PROCESS>PROCESSqueue;  //����ģ�����ִ��RR�����㷨�Ķ���
double SumWT=0,AverageWT =0;//ƽ����תʱ�䡢ƽ����Ȩ��תʱ��
int time_slice;  //ʱ��Ƭ
int n;  //���̸���
PROCESS PROCESSarray[100];  //���̽ṹ��
PROCESS temp;//�м���� 

void Input();
void RR() ;
void output() ;

int main(){
	int i,j;
    cout<<"��������̸���: ";
    cin>>n;
    
    for (i=0;i<n;i++){
      PROCESSarray[i].name=i+65;//�Զ�����������˳����ΪA��B��C��D��E��
    }
 
    for (i=0;i<n;i++){
      PROCESSarray[i].AT=0;
    }
 
    cout<<"���������ʱ��: ";
    for (i=0;i<n;i++){
      cin>>PROCESSarray[i].ST;
    }
 	
	cout<<"������ʱ��Ƭtime_slice�Ĵ�С: ";
    cin>>time_slice;
    
    //���ݴ�ʱ������
    for(i=0;i<n;i++) {
        for(j=i+1;j<n;j++) {
            if(PROCESSarray[i].AT > PROCESSarray[j].AT) {
                temp = PROCESSarray[i];
                PROCESSarray[i] = PROCESSarray[j];
                PROCESSarray[j] = temp;
            }
        }
    }
    RR();//����RR		���� 
    cout<<"ID"<<"\t";
    cout<<"����ʱ��"<<"\t";
    cout<<"���ʱ��"<<"\t";
    cout<<"��תʱ��"<<"\t";
    cout<<"�ȴ�ʱ��"<<endl;
    for (int i=0;i<n;i++){
        cout<<PROCESSarray[i].name<<"\t\t";
        cout<<PROCESSarray[i].ST<<"\t\t";
        cout<<PROCESSarray[i].FT<<"\t\t";
        cout<<PROCESSarray[i].WT<<"\t\t";
        cout<<PROCESSarray[i].WT-PROCESSarray[i].ST<<"\t\t"<<endl;
    }
    cout<<"ƽ����תʱ�� = "<<setprecision(3)<<AverageWT<<endl;
    double sum=0;
    for(int i=0;i<n;i++)
    {
    	sum+=PROCESSarray[i].WT-PROCESSarray[i].ST;
	}
    cout<<"ƽ���ȴ�ʱ�� = "<<setprecision(3)<<sum/n<<endl;
    return 0;
}
//ִ��RR�����㷨
void RR(){
    char PROCESScessName[100];   //�洢ÿ��ʱ��Ƭp��Ӧ�Ľ�������
   	PROCESSqueue.push(PROCESSarray[0]);   //��һ�����̽�����
    int CurrentTime=0;//��ǰʱ�� 
    int tempTime;   //����CurrentTime���ۼ�ʱ�䣬��ǰ���̵ķ���ʱ��С��ʱ��Ƭtime_slice��ʱ������Ҫ����
    int i=1;  
    int a=0; 
    int PROCESScessNumber = 0;   //ִ��RR�㷨�󣬽��̵ĸ��� 
    int Time[100] ;
    //�жϵ�һ�����̵ķ���ʱ���Ƿ����ʱ��Ƭ���������CurrentTime=time_slice�����С��CurrentTime=����ʱ��
    if (PROCESSarray[0].ST>=time_slice)
        CurrentTime = time_slice;
    else
        CurrentTime = PROCESSarray[0].ST;
  
    while(!PROCESSqueue.empty()){
        for (int j=i;j<n;j++){   //ʹ��������̵ĵ���ʱ��С�ڵ�ǰʱ��Ľ��̶��������
            if (CurrentTime >= PROCESSarray[j].AT){
                PROCESSqueue.push(PROCESSarray[j]);
                i++;
            }
        }
        //�����׽��̽���ִ�У�����ÿִ��һ�Σ��ͽ������ʱ�� -time_slice
        if (PROCESSqueue.front().ST>=time_slice)
            tempTime = time_slice;
        else
            tempTime = PROCESSqueue.front().ST;
            	
        PROCESSqueue.front().ST -= time_slice;  
 
        //�����׽��̵����Ʒ���������
        PROCESScessName[a]= PROCESSqueue.front().name;
        a++;
        Time[PROCESScessNumber] = tempTime; 
        PROCESScessNumber++;
 
 
        if (PROCESSqueue.front().ST <= 0)  //��ִ����Ľ����˳�����
            PROCESSqueue.pop();   //������̵ķ���ʱ��С�ڵ��ڣ����ý����Ѿ��������ˣ������˶� 
        else{
            //�������Ƶ���β
            PROCESSqueue.push(PROCESSqueue.front());
            PROCESSqueue.pop();
        }
         CurrentTime += tempTime;
    }
   //�����������   ÿ��ʱ��ζ�Ӧ��ִ�еĽ���
 

	int time = Time[0];
	int count = 0;

  
  //�������ʱ��
	for (int i=0;i<PROCESScessNumber;i++)
	{
		count = 0;
		while(PROCESSarray[count].name!=PROCESScessName[i] &&count<n)
		{	
			count++ ;
		} 
		PROCESSarray[count].FT=time ;
		if (i<PROCESScessNumber-1)
		{
			time += Time[i+1];
		}
	}
 	
	//��תʱ�䡢��Ȩ��תʱ�䡢ƽ����תʱ�䡢��Ȩƽ����תʱ��ļ���
    for (int i=0;i<n;i++){
        PROCESSarray[i].WT = PROCESSarray[i].FT - PROCESSarray[i].AT;
    }
 
    for (int i=0;i<n;i++){
        SumWT += PROCESSarray[i].WT;
    }
    AverageWT = SumWT/n;
}
 
