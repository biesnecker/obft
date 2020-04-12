#pragma once

#include <exception>

#define DEFINE_RUNTIME_ERROR_TYPE(name)          \
    struct name : public std::runtime_error {    \
        using std::runtime_error::runtime_error; \
    }