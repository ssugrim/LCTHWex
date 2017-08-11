#include<thread>
#include<future>
#include<mutex>
#include<iostream>
#include<functional>
#include<vector>
#include<cstdlib>

/*
 * This is my dummy function. I'll take a mutex as an ARG (instead of the
 * usual global).
 * Note how the mutex is taken by reference
 */
int countto(const int i, const int tno, std::mutex &mut){ 

    int j = 0;
    for(; j < i; j++){
        mut.lock();
        std::cout << "Thread" << tno << " " << j << "\n";
        mut.unlock();
    }
    return j;
}

int main (){

   //Think of this as a vector of pthread_ts 
   std::vector<std::shared_future<int>> futures;

   //My only mutex
   std::mutex mut;


   for(int count = 0; count < 100; count ++){
       int r = rand() % 100; // random number from 1 to 100

       std::shared_future<int> f = std::async(std::launch::async, countto, r, count, std::ref(mut));
       futures.push_back(f);
   }

   for(auto &f: futures){
       auto ret = f.get(); // put the blocking call to f.get outside the critical section so you don't get a race condition
       mut.lock();
       std::cout << "Got" << ret << "\n";
       mut.unlock();
   }

}

