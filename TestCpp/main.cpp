//
//  main.cpp
//  TestCpp
//
//  Created by hanxiaoqing on 2019/2/1.
//  Copyright © 2019 sdk. All rights reserved.
//

#include <iostream>
#include "NotificationCenter.h"
#include "Any.h"
#include "MessageBus.h"
#include <vector>
using namespace std;
using namespace hx;

template <typename T, typename C>
class TTS {
public:
    typedef T valueType;
    TTS() {
        cout << "TTS<typename T, typename C>" << endl;
    }
};
template <typename T>
class TTS<int, T> {
public:
    TTS() {
        cout << "TTS<T, int>" << endl;
    }
};



void testAny() {
    Any n;
    auto r = n.IsNull(); //true
    string s1 = "hello";
    n = s1;
    n = "world";
    //n.As<int>(); //can not cast int to string
    Any n1 = 1;
    n1.As<int>(); //true
    
    vector<string> ss = {"1", "2", "3"};
    Any n3 = ss;
    n3.As<vector<string>>();
}


string topic = "dds";


struct Car {
    Car()
    {
        NotificationCenter *notic = NotificationCenter::defaultCenter();
        notic->addObserver(this, &Car::drive, topic);
    }
    void drive(Notification& noti)
    {
        //cout << "Bus drive" << noti << endl;
    }
};



struct Bus {
    
    void make() {
        cout << "make Bus" << endl;
    }
    
    Bus() {
        NotificationCenter *notic = NotificationCenter::defaultCenter();
        notic->addObserver(this, &Bus::drive, "dds");
    }
    
    Bus(const Bus& b) {
        
    }
    
    Bus(const Bus&& b) {
        cout << "Bus(const Bus&& b)" << endl;
    }
    
    Bus& operator=(Bus&& b)
    {
        cout << "Move Assignment operator" << endl;
        return *this;
    }
    
    
    void drive(Notification& noti) {
        cout << this << endl;
        vector<string> ss = noti.userInfo().As<vector<string>>();
        //cout <<  << endl;
    }
    ~Bus() {
        cout << "~Bus 析构" << endl;
        NotificationCenter *notic = NotificationCenter::defaultCenter();
        notic->removeObserver(topic);
    }
};



void testNotificationCenter()
{
    Bus *bus = new Bus();
    //delete bus;
    
    
    NotificationCenter *notic = NotificationCenter::defaultCenter();
    
    vector<string> ss = {"1", "2", "3"};
    
    notic->postNotification("dds", ss);
}


void testRef(Bus& bus)
{
    
    
}
void testRef(Bus&& bus)
{
    bus.make();
}

namespace TS {
    template <class _Tp, _Tp __v>
    struct _LIBCPP_TEMPLATE_VIS integral_constant
    {
        static _LIBCPP_CONSTEXPR const _Tp      value = __v;
        typedef _Tp               value_type;
        typedef integral_constant type;
        _LIBCPP_INLINE_VISIBILITY
        _LIBCPP_CONSTEXPR operator value_type() const _NOEXCEPT {return value;}
#if _LIBCPP_STD_VER > 11
        _LIBCPP_INLINE_VISIBILITY
        constexpr value_type operator ()() const _NOEXCEPT {return value;}
#endif
    };
}


int main(int argc, const char * argv[])
{
    testAny();
    
    TTS<void, int> ts;
    TTS<int, void> ts1;
    
    return 0;
}
