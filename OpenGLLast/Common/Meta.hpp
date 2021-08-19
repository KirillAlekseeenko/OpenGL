//
//  Meta.hpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 19.05.2021.
//

#ifndef Meta_hpp
#define Meta_hpp

#include <type_traits>
#include <istream>
#include <iostream>
#include <sstream>

template <typename E>
constexpr auto to_underlying(E e) noexcept
{
    return static_cast<std::underlying_type_t<E>>(e);
}

void output_str(std::ostream& os);

template<typename TFirst, typename ...Rest>
void output_str(std::ostream& os, TFirst &&first, Rest &&...rest)
{
    os << std::forward<TFirst>(first);
    output_str(os, std::forward<Rest>(rest)...);
}

template<typename TFirst, typename ...Rest>
std::string construct(TFirst &&first, Rest && ...rest)
{
    std::ostringstream builder{};
    
    output_str(builder, std::forward<TFirst>(first), std::forward<Rest>(rest)...);
    
    return builder.str();
}


#endif /* Meta_hpp */
