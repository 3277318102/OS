#include<bits/stdc++.h>
using namespace std;

struct File {
    string name;
    string content;
};

struct Directory {
    string name;
    vector<File> files;
    vector<Directory> subdirectories;
};

void printFileContent(File* Filename)
{
	cout<<Filename->content<<endl;
}
struct FileSystem {
    Directory root;
    
    // �����ļ�
    void createFile(string path, string fileName) {
        // ���·���Ƿ����
        Directory* directory = navigateToDirectory(path);
        if (directory == nullptr) {
            cout << "·��"<<path<<"������" << endl;
            return;
        }
        
        // ����ļ��Ƿ��Ѿ�����
        for (const File& file : directory->files) {
            if (file.name == fileName) {
                cout << "�ļ�"<<fileName<<"�Ѵ���" << endl;
                return;
            }
        }
        
        // �������ļ�
        File newFile;
        newFile.name = fileName;
        directory->files.push_back(newFile);
        
        cout << "�ļ�"<<fileName<<"�����ɹ�" << endl;
    }
    
    // д���ļ�����
    void writeFile(string path, string content) {
        // ������Ŀ���ļ�
        File* file = navigateToFile(path);
        if (file == nullptr) {
            cout << "�ļ�������" << endl;
            return;
        }
        
        // �����ļ�����
        file->content = content;
        
        cout << "�ļ�д��ɹ�" << endl;
        cout<<"�ļ�����Ϊ��"; 
        printFileContent(file);
    }
    
    // ɾ���ļ�
    void deleteFile(string path) {
        // ������Ŀ���ļ����ڵ��ļ���
        Directory* directory = navigateToParentDirectory(path);
        if (directory == nullptr) {
            cout << "·��"<<path<<"������" << endl;
            return;
        }
        
        // ��ȡ�ļ���
        string fileName = getFileNameFromPath(path);
        
        // ���Ҳ�ɾ���ļ�
        bool fileFound = false;
        for (auto it = directory->files.begin(); it != directory->files.end(); ++it) {
            if (it->name == fileName) {
                directory->files.erase(it);
                fileFound = true;
                break;
            }
        }
        
        if (fileFound) {
            cout << "�ļ�"<<fileName<<"ɾ���ɹ�" << endl;
        } else {
            cout << "�ļ�"<<fileName<<"������" << endl;
        }
    }
    
    // ������ָ��·�����ļ���
    Directory* navigateToDirectory(string path) {
        if (path == "/") {
            return &root;
        }
        
        vector<string> directories = splitPath(path);
        Directory* currentDirectory = &root;
        
        for (const string& dir : directories) {
            bool directoryFound = false;
            for (Directory& subdirectory : currentDirectory->subdirectories) {
                if (subdirectory.name == dir) {
                    currentDirectory = &subdirectory;
                    directoryFound = true;
                    break;
                }
            }
            
            if (!directoryFound) {
                return nullptr; // ·��������
            }
        }
        
        return currentDirectory;
    }
    
    // ������ָ��·���ĸ��ļ���
    Directory* navigateToParentDirectory(string path) {
        if (path == "/") {
            return nullptr; // ��Ŀ¼û�и��ļ���
        }
        
        size_t lastSlashPos = path.find_last_of('/');
        string parentPath = path.substr(0, lastSlashPos);
        return navigateToDirectory(parentPath);
    }
    
    // ������ָ��·�����ļ�
    File* navigateToFile(string path) {
        Directory* parentDirectory = navigateToParentDirectory(path);
        if (parentDirectory == nullptr) {
            return nullptr; // ·��������
        }
        
        string fileName = getFileNameFromPath(path);
        for (File& file : parentDirectory->files) {
            if (file.name == fileName) {
                return &file;
            }
        }
        
        return nullptr; // �ļ�������
    }
    
    // ��·������ȡ�ļ���
    string getFileNameFromPath(string path) {
        size_t lastSlashPos = path.find_last_of('/');
        return path.substr(lastSlashPos + 1);
    }
    
    // ��·�����ΪĿ¼�б�
    vector<string> splitPath(string path) {
        vector<string> directories;
        stringstream ss(path);
        string directory;
        
        while (getline(ss, directory, '/')) {
            if (!directory.empty()) {
                directories.push_back(directory);
            }
        }
        
        return directories;
    }
};


int main() {
    FileSystem fs;
    string fn="";
    cout<<"�����ļ�-----"<<endl;
	while(1)
	{
		cout<<"�������ļ�����"; 
		cin>>fn;
		if(fn=="#")
		break;
		fs.createFile("/",fn);
	 } 
    
    cout<<"д���ļ�����-----"<<endl;
    // д���ļ�����
    string p1="";
    string context ;
    while(p1!="#")
    {
    	cout<<"�������ļ�·����";
    	cin>>p1;
    	if(p1=="#")
    	break;
    	cout<<"������д�����ݣ�";
    	cin>>context;
		fs.writeFile(p1, context);
	}
    
    cout<<"ɾ���ļ�-----"<<endl;
    // ɾ���ļ�
	string p;
	 while(1)
	 {
	 	cout<<"�������ļ�·����";
	 	cin>>p;
	 	if(p=="#")
	 	break;
	 	fs.deleteFile(p);
	 }
   
    return 0;
}

