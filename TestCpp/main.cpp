//
//  main.cpp
//  TestCpp
//
//  Created by hanxiaoqing on 2019/2/1.
//  Copyright © 2019 sdk. All rights reserved.
//

#include <iostream>
#include "HXNotificationCenter.h"
#include "Any.h"
#include "MessageBus.h"
#include <vector>
using namespace std;
using namespace hx;

void testAny() {
    Any n;
    auto r = n.IsNull(); //true
    string s1 = "hello";
    n = s1;
    n = "world";
    //n.AnyCast<int>(); //can not cast int to string
    Any n1 = 1;
    n1.Is<int>(); //true
}


MessageBus g_bus;
string topic = "dds";
struct Subject {
    Subject()
    {
        m_name = "Subject";
    }
    void SendReq(const string& topic)
    {
        g_bus.SendReq<void, int, hx::Any>(50, this, topic);
    }
    string m_name;
};


struct Car {
    Car() {
        g_bus.Attach([this](int speed, hx::Any any) {
            drive(speed);
            
            
        }, topic);
    }
    void drive(int speed)
    {
        cout << "Car drive" << speed << endl;
    }
};

struct Bus {
    Bus()
    {
       // g_bus.Attach([this](int speed) { drive(speed); }, topic);
        NotificationCenter *notic = NotificationCenter::defaultCenter();
        notic->addObserver(this, std::bind(&Bus::drive, this,std::placeholders::_1), topic);
        
//      notic->addObserver(this, Bus::drive, topic);
    }
    void drive(Notification& noti)
    {
        //cout << "Bus drive" << noti << endl;
    }
};



void testMessageBus()
{
    Car car;
    Bus bus;
    
    Subject subject;
    subject.SendReq(topic);
}



void testNotificationCenter()
{
    Car car;
    
    Bus *bus = new Bus();
    NotificationCenter *notic = NotificationCenter::defaultCenter();
    notic = NotificationCenter::defaultCenter();
    

    notic->addObserver(bus, std::bind(&Bus::drive, bus,std::placeholders::_1), topic);
    notic->postNotification(topic, 1,2);
    
}





int main(int argc, const char * argv[])
{

//    testMessageBus();
//    testAny();
    
    
    testNotificationCenter();
    return 0;
}
