#include<thread>
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
   std::vector<std::thread> threads;

   //My only mutex
   std::mutex mut;

   /*
    * There is much going on here. Two things:
    *
    * emplaceback contstructs the thread object by calling it's constuctor
    * and passing it the arguments specified in the arg list.
    *
    * The mutex can't be taken as an argument directly. The logic that
    * decides how to pass the mutex will try to copy it. Instead a std::ref
    * hint is required to tell the compiler we really mean to pass a ref here.
    *
    */

   for(int count = 0; count < 100; count ++){
       int r = rand() % 100; // random number from 1 to 100

       threads.emplace_back(countto, r, count, std::ref(mut)); 
       // An implicit call to std::thread THREADOBJNAME(countto, r, count, std::ref(mut));
   }

   for(auto &t: threads){
        t.join();
   }

}

