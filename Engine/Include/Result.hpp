//
// Created by Shreejit Murthy on 25/12/2024.
// Merry Christmas :-)
//
// Hacked together enum Result<T, E> (from Rust) in C++.

#pragma once

#include <iostream>
#include <string>
#include <utility>

template <typename T, typename E>
class Result {
private:
    union {
        T okValue;
        E errValue;
    };
    bool isOk;

public:
    Result(T ok) : okValue(std::move(ok)), isOk(true) {}
    Result(E err) : errValue(std::move(err)), isOk(false) {}

    ~Result() {
        if (isOk) {
            okValue.~T();
        } else {
            errValue.~E();
        }
    }

    bool is_ok() const { return isOk; }
    bool is_err() const { return !isOk; }

    T& unwrap() {
        if (!isOk) {
            throw std::runtime_error("Called unwrap() on an Err value");
        }
        return okValue;
    }

    E& unwrap_err() {
        if (isOk) {
            throw std::runtime_error("Called unwrap_err() on an Ok value");
        }
        return errValue;
    }

    T& expect(const std::string& msg) {
        if (!isOk) {
            throw std::runtime_error(msg);
        }
        return okValue;
    }

    E& expect_err(const std::string& msg) {
        if (isOk) {
            throw std::runtime_error(msg);
        }
        return errValue;
    }
};

