//
// Created by Shreejit Murthy on 1/11/2024.
//

#pragma once

#include <filesystem>
#include <iostream>
#include <type_traits>
#include <fstream>
#include <array>

#include "Result.hpp"

#include <log/log.h>

constexpr int ERR = 1;

template <typename T>
void checkType(const T& arg) {
    if constexpr (std::is_same<T, int>::value) {
        std::cout << arg << " is an int\n";
    } else if constexpr (std::is_same<T, double>::value) {
        std::cout << arg << " is a double\n";
    } else if constexpr (std::is_same<T, std::string>::value) {
        std::cout << arg << " is a string\n";
    } else {
        std::cout << arg << " is of unknown type\n";
    }
}

namespace fs = std::filesystem;

namespace System {
    fs::path findEnginePath(const fs::path& startDir = fs::current_path());
    fs::path findPathUpwards(const fs::path& targetPath, const fs::path& startDir = fs::current_path());
    // string path, err number
    Result<std::string, int> getPath(const fs::path& targetPath, const fs::path& startDir = fs::current_path());

    template <typename... Args>
    void writeOutBinary(const std::string& filename, Args... args) {
        std::ofstream outFile(filename, std::ios::binary);
        if (!outFile) {
            log_error("Error opening file for writing: %s", filename.c_str());
            return;
        }

        // perculiar c++
        (
            [&]() {
                // implement other types later as required
                if constexpr (std::is_same_v<Args, unsigned int>) {  // unsigned int
                    outFile.write(reinterpret_cast<const char*>(&args), sizeof(args));
                } if constexpr (std::is_same_v<Args, std::array<float, 32>>) {  // std::array
                    outFile.write(reinterpret_cast<const char*>(args.data()), args.size() * sizeof(float));
                } if constexpr (std::is_same_v<Args, int>) {  // int
                    outFile.write(reinterpret_cast<const char*>(&args), sizeof(args));
                }
            }(),
            ...
        );

        outFile.close();

        if (!outFile) {
            log_error("Error writing to file: %s", filename.c_str());
            return;
        } else {
            log_info("Data successfully written to %s", filename.c_str());
        }
    }

    template<typename... Args> 
    void readBinary(const std::string& filename, Args&... args) {
        std::ifstream inFile(filename, std::ios::binary);
        if (!inFile) {
            log_error("Error opening file for reading: %s", filename.c_str());
            return;
        }

        (
            [&]() {
                // implement other types later as required
                if constexpr (std::is_same_v<Args, unsigned int>) {  // unsigned int
                    inFile.read(reinterpret_cast<char*>(&args), sizeof(args));
                } if constexpr (std::is_same_v<Args, std::array<float, 32>>) {  // std::array
                    inFile.read(reinterpret_cast<char*>(args.data()), args.size() * sizeof(float));
                } if constexpr (std::is_same_v<Args, int>) {  // int
                    inFile.read(reinterpret_cast<char*>(&args), sizeof(args));
                }
            }(),
            ...
        );

        inFile.close();

        if (!inFile) {
            // log_error("Error reading from file: %s", filename.c_str());
        } else {
            // log_info("Data successfully read from %s", filename.c_str());
        }

    }
}