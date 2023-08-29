//
// Created by Administrator on 2023/7/1.
//
#include "iostream"
#include "thread"

static bool s_Finished =false;

void DoWork(){
    using namespace std::literals::chrono_literals;



    
while(!s_Finished){
    std::cout<<"Working\n";
    std::this_thread::sleep_for(1s);
}
}

int main(){
    std::thread worker(DoWork);

    std::cin.get();
    s_Finished=true;

    worker.join();

    std::cin.get();
}