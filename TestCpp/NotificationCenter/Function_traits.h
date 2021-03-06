//
//  Function_traits.h
//  TestCpp
//
//  Created by hanxiaoqing on 2019/2/22.
//  Copyright © 2019 sdk. All rights reserved.
//

#ifndef Function_traits_h
#define Function_traits_h

#include <stdio.h>

namespace hx {
    
    template<typename T>
    struct function_traits;
    
    template<typename Ret, typename... Args>
    struct function_traits<Ret(Args...)> {
    public:
        enum { arity = sizeof...(Args) };
        typedef Ret function_type(Args...);
        typedef Ret return_type;
        
        using stl_function_type = std::function<function_type>;
        typedef Ret(*pointer)(Args ...);
        
        template<size_t I>
        struct args {
            static_assert(I < arity, "index is out of range. index must less than size of Args.");
            using type = typename std::tuple_element<I, std::tuple<Args...>>::type;
        };
        
        template<size_t N>
        using arg_type = typename std::tuple_element<N, std::tuple<Args...>>::type;
    };
    
    template<typename Ret, typename... Args>
    struct function_traits<Ret(*)(Args...)> : function_traits<Ret(Args...)> {};
    
    template<typename Ret, typename... Args>
    struct function_traits<std::function<Ret(Args...)>> : function_traits<Ret(Args...)> {};
    
    #define FUNCTION_TRAITS(...) \
    template<typename ReturnType, typename ClassType, typename... Args> \
    struct function_traits<ReturnType(ClassType::*)(Args...) __VA_ARGS__> : \
    function_traits<ReturnType(Args...)> {}; \

    FUNCTION_TRAITS()
    FUNCTION_TRAITS(const)
    FUNCTION_TRAITS(volatile)
    FUNCTION_TRAITS(const volatile)
    
    template<typename Callable>
    struct function_traits: function_traits<decltype(&Callable::operator())> {};
    
    template<typename Function>
    typename function_traits<Function>::stl_function_type to_function(const Function& lamdba) {
        return static_cast<typename function_traits<Function>::stl_function_type>(lamdba);
    }
    
    template<typename Function>
    typename function_traits<Function>::stl_function_type to_function(const Function&& lamdba) {
        return static_cast<typename function_traits<Function>::stl_function_type> (std::forward<Function>(lamdba));
    }
    
    template<typename Function>
    typename function_traits<Function>::pointer to_function_pointer(const Function& lamdba) {
         return static_cast<typename function_traits<Function>::pointer>(lamdba);
    }
}


#endif /* Function_traits_h */
