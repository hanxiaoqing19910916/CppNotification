//
//  Any.h
//  TestCpp
//
//  Created by hanxiaoqing on 2019/2/20.
//  Copyright © 2019 sdk. All rights reserved.
//

#ifndef Any_h
#define Any_h

#include <stdio.h>
#include <memory>
#include <typeindex>


namespace hx {
    
    struct Any
    {
    public:
        Any(void) : m_tpIndex(std::type_index(typeid(void))) {}
        Any(const Any& that) : m_ptr(that.Clone()), m_tpIndex(that.m_tpIndex) {}
        Any(Any&& that) : m_ptr(std::move(that.m_ptr)), m_tpIndex(that.m_tpIndex) {}
        
        template<typename U, class = typename std::enable_if<!std::is_same<typename std::decay<U>::type, Any>::value, U>::type>
        Any(U && value) : m_ptr(new Derived<typename std::decay<U>::type> (std::forward<U>(value))),
        m_tpIndex(std::type_index(typeid(typename std::decay<U>::type))) {}
        
        bool IsNull() const { return !bool(m_ptr); }
        
        template<class U> bool Is() const
        {
            return m_tpIndex == std::type_index(typeid(U));
        }
        
        template<class U> U& AnyCast()
        {
            if (!Is<U>()) {
                throw std::bad_cast();
            }
            auto dervied = dynamic_cast<Derived<U> *> (m_ptr.get());
            return dervied->m_value;
        }
        

        
        Any& operator=(const Any& a)
        {
            if (m_ptr == a.m_ptr) { return *this; }
            
            m_ptr = a.Clone();
            m_tpIndex = a.m_tpIndex;
            return *this;
        }
        
        
    private:
        struct Base;
        
        std::type_index m_tpIndex;
        std::unique_ptr<Base> m_ptr;
        
        struct Base
        {
            virtual ~Base() {}
            virtual std::unique_ptr<Base> Clone() const = 0;
        };
        
        template<typename T>
        struct Derived : Base
        {
            template<typename U>
            Derived(U && value) : m_value(std::forward<U>(value)) {}
            
            std::unique_ptr<Base> Clone() const
            {
                return std::unique_ptr<Base>(new Derived<T>(m_value));
            }
            
            T m_value;
        };
        
        std::unique_ptr<Base> Clone() const
        {
            if (m_ptr != nullptr)  {
                return m_ptr->Clone();
            }
            return nullptr;
        }
    };
    
}

#endif /* Any_h */
