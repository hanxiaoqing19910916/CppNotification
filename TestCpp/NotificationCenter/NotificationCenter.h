//
//  HXNotificationCenter.h

#ifndef HXNotificationCenter_h
#define HXNotificationCenter_h

#include <stdio.h>
#include <functional>
#include <vector>
#include <unordered_map>
#include <memory>
#include "Any.h"
#include "MessageBus.h"

/*
 NotificationCenter 使用说明:
 
 string notiName = "oneBigThing"; // 通知名字
 struct Person {
     Person() {
         // 添加要监听的通知名字,以及监听对象以及回调Function
         NotificationCenter *notic = NotificationCenter::defaultCenter();
 
         //注意添加某个类的实例方法的时候,要用(&+类名+方法名形式),如下: &Person::recieved
         notic->addObserver(this, &Person::recieved, notiName);
     }
 
     //回调函数的参数被限定死,只能是一个Notification&类型
     void recieved(Notification& noti) {
         cout << "recieved" << endl;
 
         // noti.name() 获取当前通知名字
         cout << noti.name() << endl;
 
         //发通知的时候,可以携带一个任意类型的数据,用于传递通知过程的一些上下文信息
         //由于设计了一个Any的万能容器,可接受任意类型的传值,因此在取出的使用要用As<类型>还原.
         cout << noti.userInfo().As<int>() << endl;
     }
 
     ~Person() { }
 };
 
 
 void testNotificationCenter()
 {
     Person p;
 
     NotificationCenter *notic = NotificationCenter::defaultCenter();
     //发出通知,第一个参数是通知名字,第二个参数可以传一个任意类型的数据,用于同步给监听者
     notic->postNotification(notiName, 1);
 }

*/



using namespace std;

namespace hx {
    
    struct Notification {
    public:
        Notification(string& name, Any& userInfo) : m_notificationName(name), m_userInfo(userInfo) {};
        string& name()  { return m_notificationName; }
        Any& userInfo() {  return m_userInfo; }
    private:
        string m_notificationName;
        Any m_userInfo;
    };
    
    class NotificationCenter {
    public:
        static NotificationCenter* defaultCenter();
        
        template <typename T, typename C>
        void addObserver(T observer, void (C::*selector)(Notification&), string name) {
            std::function<void(Notification&)> func = std::bind(selector, observer, std::placeholders::_1);
            msg_bus.Attach(func, name);
        }
        
        template <typename T>
        void addObserver(T observer, std::function<void(Notification&)>&& selector, string name) {
            msg_bus.Attach(selector, name);
        }
        
        void removeObserver(string notificationName) {
            msg_bus.Remove<void, Notification&>(notificationName);
        }
        
        template<typename... Args>
        void postNotification(string notificationName, Any userInfo) {
            Notification noti(notificationName, userInfo);
            msg_bus.SendReq<void, Notification&>(noti, notificationName);
        }
        
    private:
        static NotificationCenter* m_center;
        
        NotificationCenter();
        NotificationCenter(const NotificationCenter&);
        NotificationCenter& operator=(const NotificationCenter&);
        
        virtual ~NotificationCenter() = default;
        
        MessageBus msg_bus;
        //vector<hx::Any> m_observers;
    };
    
}
#endif /* NotificationCenter_h */
