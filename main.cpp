#include "multiThread/Loop.h"
#include "time/timeMarker.h"
#include <iostream>


/*
将static范围最小化到一个辅助函数，妙啊
*/
class test{
public:
    test(){
        loopThread01 = new LoopFunc("loop01", 0.001, boost::bind(&test::loop01Static, this));
        loopThread02 = new LoopFunc("loop02", 0.001, boost::bind(&test::loop02Static, this));
        loopThread01->start();
        loopThread02->start();
    }
    ~test(){
        delete loopThread01;
        delete loopThread02;
    }

    static void* loop01Static(void* obj){
        reinterpret_cast<test*>(obj)->loop01();
    }

    static void* loop02Static(void* obj){
        reinterpret_cast<test*>(obj)->loop02();
    }

    void loop01(){
        std::cout << "loop01: " << getSystemTime() - timeMarker01 << std::endl;
        timeMarker01 = getSystemTime();
    }
    void loop02(){
        std::cout << "loop02: " << getSystemTime() - timeMarker02 << std::endl;
        timeMarker02 = getSystemTime();
    }
private:
    long long timeMarker01;
    long long timeMarker02;
    LoopFunc* loopThread01;
    LoopFunc* loopThread02;
};

int main(){
    test testClass;

    // usleep(2000000);
    while(true){}

    return 0;
}

/* 
全员static的弃疗模式
*/
// class test{
// public:
//     test(){
//         loopThread01 = new LoopFunc("loop01", 0.001, loop01);
//         loopThread02 = new LoopFunc("loop02", 0.001, loop02);
//         loopThread01->start();
//         loopThread02->start();
//     }
//     ~test(){
//         delete loopThread01;
//         delete loopThread02;
//     }

//     static void loop01(){
//         std::cout << "loop01: " << getSystemTime() - timeMarker01 << std::endl;
//         timeMarker01 = getSystemTime();
//     }
//     static void loop02(){
//         std::cout << "loop02: " << getSystemTime() - timeMarker02 << std::endl;
//         timeMarker02 = getSystemTime();
//     }
// private:
//     static long long timeMarker01;
//     static long long timeMarker02;
//     LoopFunc* loopThread01;
//     LoopFunc* loopThread02;
// };

// long long test::timeMarker01;
// long long test::timeMarker02;

// int main(){
//     test testClass;

//     // usleep(2000000);
//     while(true){}

//     return 0;
// }




/*
体外执行线程，不够简洁
*/
// class test{
// public:
//     void loop01(){
//         std::cout << "loop01: " << getSystemTime() - timeMarker01 << std::endl;
//         timeMarker01 = getSystemTime();
//     }
//     void loop02(){
//         std::cout << "loop02: " << getSystemTime() - timeMarker02 << std::endl;
//         timeMarker02 = getSystemTime();
//     }
// private:
//     long long timeMarker01;
//     long long timeMarker02;
// };

// int main(){
//     test testClass;

//     LoopFunc loop01("loop01", 0.001, boost::bind(&test::loop01, &testClass));
//     LoopFunc loop02("loop02", 0.001, boost::bind(&test::loop02, &testClass));

//     loop01.start();
//     loop02.start();

//     // usleep(2000000);
//     while(true){}

//     return 0;
// }