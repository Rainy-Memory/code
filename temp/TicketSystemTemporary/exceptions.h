//
// Created by Rainy Memory on 2021/5/25.
//

#ifndef CODE_EXCEPTIONS_H
#define CODE_EXCEPTIONS_H

#include <cstddef>
#include <cstring>
#include <string>

namespace RainyMemory {
    
    class exception : public std::exception {
    protected:
        const std::string variant = "";
        std::string detail = "";
    public:
        exception() {}
        
        exception(const exception &ec) : variant(ec.variant), detail(ec.detail) {}
        
        virtual std::string what() {
            return variant + " " + detail;
        }
    };
    
    class index_out_of_bound : public exception {
        /* __________________________ */
    };
    
    class runtime_error : public exception {
        /* __________________________ */
    };
    
    class invalid_iterator : public exception {
        /* __________________________ */
    };
    
    class container_is_empty : public exception {
        /* __________________________ */
    };
}

#endif //CODE_EXCEPTIONS_H
