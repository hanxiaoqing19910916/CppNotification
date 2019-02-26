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

using namespace std;

namespace hx {
    
    struct Notification {
    public:
        Notification(string &name) : m_notificationName(name) {};
        string& name() {
            return m_notificationName;
        }
    private:
        string m_notificationName;
    };
    
    class NotificationCenter {
    public:
        static NotificationCenter* defaultCenter();
        
        template <typename T, typename C, typename... Args>
        void addObserver(T observer, void (C::*selector)(Args...), string& name) {
            m_observers.push_back(observer);
            std::function<void(Notification&)> func = std::bind(selector, observer, std::placeholders::_1);
            msg_bus.Attach(func, name);
        }
        
        template <typename T, typename... Args>
        void addObserver(T observer, std::function<void(Notification&)>&& selector, string& name) {
            m_observers.push_back(observer);
            msg_bus.Attach(selector, name);
        }
        
        void postNotification(Notification& notification) {
            // msg_bus.SendReq<void, int, hx::Any>(50, this, topic);
        }
        
        template<typename... Args>
        void postNotification(string& notificationName, Args&& ...args) {
            for(auto it = m_observers.begin(); it != m_observers.end(); ++it) { }
            
            Notification noti(notificationName);
            msg_bus.SendReq<void, Notification&>(noti, notificationName);
        }
        
        
    private:
        static NotificationCenter* m_center;
        
        NotificationCenter();
        NotificationCenter(const NotificationCenter&);
        NotificationCenter& operator=(const NotificationCenter&);
        
        virtual ~NotificationCenter() = default;
        
        MessageBus msg_bus;
        vector<hx::Any> m_observers;
    };
    
}



#endif /* HXNotificationCenter_h */
