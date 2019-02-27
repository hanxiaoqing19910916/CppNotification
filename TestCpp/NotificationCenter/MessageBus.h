//
//  MessageBus.h
//  TestCpp
//
//  Created by hanxiaoqing on 2019/2/25.
//  Copyright © 2019 sdk. All rights reserved.
//

#ifndef MessageBus_h
#define MessageBus_h

#include <string>
#include <functional>
#include <map>
#include "Any.h"
#include "Function_traits.h"

using namespace std;

class MessageBus {
public:
    template<typename F>
    void Attach(F&& f, const string& strTopic = "") {
        auto func = hx::to_function(f);
        Add(strTopic, std::move(func));
    }
    
    template<typename R>
    void SendReq(const string& strTopic = "") {
        using function_type = std::function<R()>;
        string strMsgType = strTopic + typeid(function_type).name();
        
        auto range = m_map.equal_range(strMsgType);
        for (Iterater it = range.first; it != range.second; ++it) {
            auto f = it->second.As<function_type>();
            f();
        }
    }
    
    template<typename R, typename... Args>
    void SendReq(Args&& ...args, const string& strTopic = "") {
        using function_type = std::function<R(Args...)>;
        string strMsgType = strTopic + typeid(function_type).name();
        
        auto range = m_map.equal_range(strMsgType);
        for (Iterater it = range.first; it != range.second; ++it) {
            auto f = it->second.As<function_type>();
            f(std::forward<Args>(args) ...);
        }
    }
    
    template<typename R, typename... Args>
    void Remove(const string& strTopic = "") {
        using function_type = std::function<R(Args...)>;
        string strMsgType = strTopic + typeid(function_type).name();
        auto range = m_map.equal_range(strMsgType);
        m_map.erase(range.first, range.second);
    }
    
    
private:
    std::multimap<string, hx::Any> m_map;
    typedef std::multimap<string, hx::Any>::iterator Iterater;
    
    template<typename F>
    void Add(const string& strTopic, F&& f)  {
         string strMsgType = strTopic + typeid(F).name();
         m_map.emplace(std::move(strMsgType), std::forward<F>(f));
    }
};










#endif /* MessageBus_h */
