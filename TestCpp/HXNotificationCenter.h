//
//  HXNotificationCenter.h

#ifndef HXNotificationCenter_h
#define HXNotificationCenter_h

#include <stdio.h>
#include <functional>
#include <vector>
#include <unordered_map>
#include "Any.h"
#include "MessageBus.h"

using namespace std;

namespace hx {

    #define HAS_MEM_FUNC(FunctionName, HelperClassName) \
    template<typename T> \
    struct HelperClassName { \
        typedef char one; \
        typedef long two; \
        template <typename C> static one test(decltype(&C::FunctionName)); \
        template <typename C> static two test(...); \
    public: \
    enum { value = sizeof(test<T>(0)) == sizeof(char) }; \
    }
    
    HAS_MEM_FUNC(operator(), hasOperatorParentheses);

    template<class T, class Enable = void>
    class A {
    public:
        static const bool value = false;
        static void execute(const typename std::decay<T>::type & t){
            // std::cout << "no function to call" << std::endl;
        }
    };
    
    template<class T>
    class A <T, typename std::enable_if<hasOperatorParentheses<T>::value >::type>
    {
    public:
        static const bool value = true;
        static void execute(const typename std::decay<T>::type & t){
            const_cast<typename std::decay<T>::type&>(t)();
        }
    };
    

//    template <typename T>
//    class Notification { };
//
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
        
        
        template <typename T, typename... Args>
        void addObserver(T observer, typename T::func&& selector, string& name)
        {
           
            
        }
        
        
        template <typename T, typename... Args>
        void addObserver(T observer, std::function<void(Notification&)>&& selector, string& name)
        {
            m_observers.push_back(observer);
            
           // std::bind(selector, &observer);
            msg_bus.Attach(selector, name);
        
        }
        
        void postNotification(Notification& notification)
        {
           // msg_bus.SendReq<void, int, hx::Any>(50, this, topic);
        }
        
        template<typename... Args>
        void postNotification(string& notificationName, Args&& ...args)
        {
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
