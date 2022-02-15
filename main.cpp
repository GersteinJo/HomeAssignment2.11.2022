#include <iostream>
#include <chrono>
#include <array>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <algorithm>
#include <map>
#include <experimental/random>

//question how would be different work of a program should we write a macros instead of a void function?
//if we do this despite how evil it might sound?

#define Range(container) container.begin(), container.end()
#define OUT(simpleTypeContainer) for(auto i: simpleTypeContainer) std::cout<<i<<" "; std::cout<<"\n";

using namespace std::chrono;

class Timer
{
private:
    steady_clock::time_point start;
public:
    Timer(){};
    ~Timer(){};
    void Start()
    {
        start = steady_clock::now();
    };

    int Stop()
    {
        return duration_cast<std::chrono::nanoseconds>(steady_clock::now()-start).count();
    };
};



int main() {
    std::array<int, 1000> myArray;
    std::vector<int> myVector;
    std::deque<int> myDeque;

    std::list<int> myList;
    std::forward_list<int> myForwardList;

    for(auto i = 0; i<1000;i++) myArray[i]=std::experimental::randint(-10000,10000);
    for(auto i = 0; i<1000;i++) myVector.push_back(myArray[i]);
    for(auto i = 0; i<1000;i++) myDeque.push_back(myArray[i]);
    for(auto i = 0; i<1000;i++) myList.push_back(myArray[i]);
    for(auto i = 0; i<1000;i++) myForwardList.push_front(myArray[1000-i]);

    Timer myTimer;
    std::map<std::string, int> results;

    myTimer.Start();
    std::sort(Range(myArray), std::less<int>());
    results["myArray"] = myTimer.Stop();


    myTimer.Start();
    std::sort(Range(myVector), std::less<int>());
    results["myVector"] = myTimer.Stop();


    myTimer.Start();
    std::sort(Range(myDeque), std::less<int>());
    results["myDeque"] = myTimer.Stop();


    myTimer.Start();
    myList.sort();
    results["myList"] = myTimer.Stop();


    myTimer.Start();
    myForwardList.sort();
    results["myForwardList"] = myTimer.Stop();


    std::pair<std::string,int> fastest("myArray", results["myArray"]);
    for(const auto& [container, time]: results)
    {
        if(time<fastest.second)
        {
            fastest.first = container;
            fastest.second = time;
        }
        std::cout<<container<<" "<<time<<"\n";
    }
    std::cout<<"The fastest one is "<<fastest.first<<"\n";

/*    OUT(myArray);
    OUT(myVector);
    OUT(myDeque);
    OUT(myList);
    OUT(myForwardList);*/

    return 0;
}
