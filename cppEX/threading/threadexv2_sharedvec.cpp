#include<thread>
#include<mutex>
#include<iostream>
#include<functional>
#include<vector>
#include<cstdlib>

/*
 * It doesn't matter what the return type of the funcion is
 * It can never be retrieved.
 */

void countto(
        const int i,
        const int tno,
        std::mutex &mut,
        std::vector<int> &rets){ // in place of a return value

    int j = 0;
    for(; j < i; j++){
        mut.lock();
        std::cout << "Thread" << tno << " " << j << "\n";
        mut.unlock();
    }
    mut.lock();
    rets.push_back(j);
    mut.unlock();
}

int main (){
   std::vector<std::thread> threads;

   //shared storage variable
   std::vector<int> rets;

   //My only mutex
   std::mutex mut;

   /* sow */
   for(int count = 0; count < 100; count ++){
       int r = rand() % 100; // random number from 1 to 100

       threads.emplace_back(countto, r, count, std::ref(mut), std::ref(rets));
       //the vector has to be passed as a standard ref also
   }

   /* reap */
   for(auto &t: threads){
        t.join();
   }

   /* use */
   for(const auto &i: rets){
       std::cout << "Got " << i << std::endl;
   }
}

