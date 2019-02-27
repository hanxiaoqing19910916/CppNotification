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
#endif /* HXNotificationCenter_h */
