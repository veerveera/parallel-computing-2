#include <iostream>
#include <fstream>
#include<vector>
#include<thread>
#include <mutex>
using namespace std;
mutex emae;
 
void writeFile(vector<string>list) {
    emae.lock();
    ofstream my_file("file.txt");
    for(int i = 0; i<list.size(); i++) {
        my_file<<list[i]<<' ';
    }
    my_file.close();
    emae.unlock();
}
 
void readFile() {
    emae.lock();
    ifstream my_file("file.txt");
    string s;
    int index = 1;
    while(my_file >> s) {
        cout<<index<<". "<<s<<endl;
        index++;
    }
    my_file.close();
    emae.unlock();
}
int main() {
    int n;
    cout<<"Введите размер массива строк: "<<endl;
    cin>>n;
    vector<string> str_list;
    string s;
    for(int i =0; i<n;i++) {
        cout<<"Введите строку "<<i+1<<": ";
        cin>>s;
        str_list.push_back(s);
    }
    thread thread1 = thread(writeFile, str_list);
    thread thread2 = thread(readFile);
    thread1.join();
    thread2.join();
    
    return 0;
}
