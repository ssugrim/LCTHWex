#include<thread>
#include<mutex>
#include<iostream>
#include<functional>

using std::cout;

int countto(const int i, const std::string &s, std::mutex &mut){

    int j = 0;
    for(; j < i; j++){
        mut.lock();
        cout << "Number " << s << " " << j << "\n";
        mut.unlock();
    }
    return j;
}

int main (){

   int count = 100;
   std::string str1 = "thread1";

   std::mutex mut; 

   std::thread thread1(countto, count, str1, std::ref(mut));

   std::string str2 = "thread2";
   std::thread thread2(countto, count, str2, std::ref(mut));

   //thread2.detach();
   thread1.join();
   thread2.join();

}

