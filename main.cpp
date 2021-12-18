#include "multiThread/Loop.h"
#include "time/timeMarker.h"
#include <iostream>

class test{
public:
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
};

int main(){
    test testClass;

    LoopFunc loop01("loop01", 0.001, boost::bind(&test::loop01, &testClass));
    LoopFunc loop02("loop02", 0.001, boost::bind(&test::loop02, &testClass));

    loop01.start();
    loop02.start();

    // usleep(2000000);
    while(true){}

    return 0;
}