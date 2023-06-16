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
    
    // 创建文件
    void createFile(string path, string fileName) {
        // 检查路径是否存在
        Directory* directory = navigateToDirectory(path);
        if (directory == nullptr) {
            cout << "路径"<<path<<"不存在" << endl;
            return;
        }
        
        // 检查文件是否已经存在
        for (const File& file : directory->files) {
            if (file.name == fileName) {
                cout << "文件"<<fileName<<"已存在" << endl;
                return;
            }
        }
        
        // 创建新文件
        File newFile;
        newFile.name = fileName;
        directory->files.push_back(newFile);
        
        cout << "文件"<<fileName<<"创建成功" << endl;
    }
    
    // 写入文件内容
    void writeFile(string path, string content) {
        // 导航到目标文件
        File* file = navigateToFile(path);
        if (file == nullptr) {
            cout << "文件不存在" << endl;
            return;
        }
        
        // 更新文件内容
        file->content = content;
        
        cout << "文件写入成功" << endl;
        cout<<"文件内容为："; 
        printFileContent(file);
    }
    
    // 删除文件
    void deleteFile(string path) {
        // 导航到目标文件所在的文件夹
        Directory* directory = navigateToParentDirectory(path);
        if (directory == nullptr) {
            cout << "路径"<<path<<"不存在" << endl;
            return;
        }
        
        // 获取文件名
        string fileName = getFileNameFromPath(path);
        
        // 查找并删除文件
        bool fileFound = false;
        for (auto it = directory->files.begin(); it != directory->files.end(); ++it) {
            if (it->name == fileName) {
                directory->files.erase(it);
                fileFound = true;
                break;
            }
        }
        
        if (fileFound) {
            cout << "文件"<<fileName<<"删除成功" << endl;
        } else {
            cout << "文件"<<fileName<<"不存在" << endl;
        }
    }
    
    // 导航到指定路径的文件夹
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
                return nullptr; // 路径不存在
            }
        }
        
        return currentDirectory;
    }
    
    // 导航到指定路径的父文件夹
    Directory* navigateToParentDirectory(string path) {
        if (path == "/") {
            return nullptr; // 根目录没有父文件夹
        }
        
        size_t lastSlashPos = path.find_last_of('/');
        string parentPath = path.substr(0, lastSlashPos);
        return navigateToDirectory(parentPath);
    }
    
    // 导航到指定路径的文件
    File* navigateToFile(string path) {
        Directory* parentDirectory = navigateToParentDirectory(path);
        if (parentDirectory == nullptr) {
            return nullptr; // 路径不存在
        }
        
        string fileName = getFileNameFromPath(path);
        for (File& file : parentDirectory->files) {
            if (file.name == fileName) {
                return &file;
            }
        }
        
        return nullptr; // 文件不存在
    }
    
    // 从路径中提取文件名
    string getFileNameFromPath(string path) {
        size_t lastSlashPos = path.find_last_of('/');
        return path.substr(lastSlashPos + 1);
    }
    
    // 将路径拆分为目录列表
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
    cout<<"创建文件-----"<<endl;
	while(1)
	{
		cout<<"请输入文件名："; 
		cin>>fn;
		if(fn=="#")
		break;
		fs.createFile("/",fn);
	 } 
    
    cout<<"写入文件内容-----"<<endl;
    // 写入文件内容
    string p1="";
    string context ;
    while(p1!="#")
    {
    	cout<<"请输入文件路径：";
    	cin>>p1;
    	if(p1=="#")
    	break;
    	cout<<"请输入写入内容：";
    	cin>>context;
		fs.writeFile(p1, context);
	}
    
    cout<<"删除文件-----"<<endl;
    // 删除文件
	string p;
	 while(1)
	 {
	 	cout<<"请输入文件路径：";
	 	cin>>p;
	 	if(p=="#")
	 	break;
	 	fs.deleteFile(p);
	 }
   
    return 0;
}

