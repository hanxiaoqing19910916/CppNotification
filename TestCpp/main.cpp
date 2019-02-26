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


string topic = "dds";


struct Bus {
    Bus()
    {
        NotificationCenter *notic = NotificationCenter::defaultCenter();
        notic->addObserver(this, &Bus::drive, topic);
    }
    void drive(Notification& noti)
    {
        //cout << "Bus drive" << noti << endl;
    }
};





void testNotificationCenter()
{

    Bus *bus = new Bus();
    NotificationCenter *notic = NotificationCenter::defaultCenter();
    notic->postNotification(topic, 1,2);
    
}





int main(int argc, const char * argv[])
{

//    testMessageBus();
//    testAny();
    
    
    testNotificationCenter();
    return 0;
}
