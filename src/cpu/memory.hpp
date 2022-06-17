/*
#include <array>
#include <iterator>
#include <algorithm>
*/
#include <variant>
#pragma once

// TODO: fix this part by switching it to a class than a namespace and other stuff

namespace MEMORY {
//    private:
        static constexpr uint16_t MAX_MEM = UINT16_MAX; // 2^16 bits of memory
        //static constexpr uint16_t MAX_MEM = 1 << 16; // 2^16 bits of memory

//    public:
        //static std::array<uint8_t, MAX_MEM> memory;

        static uint8_t memory[MAX_MEM];

        [[nodiscard]] static constexpr inline bool Initialise(void) noexcept {

            #if __cplusplus == 202002L
                try {
                    //std::fill(std::begin(memory), std::begin(memory)+MAX_MEM, 0);

                    for (size_t i = 0; i < MAX_MEM; ++i) {
                        memory[i] = 0;
                    }
                    return true;
                } catch (...) {
                    return false;
                }
            #else 
                for (size_t i = 0; i < MAX_MEM; ++i) {
                    memory[i] = 0;
                }
                return true;
            #endif
        }

        [[maybe_unused]] static void Write(const uint8_t &value, const uint16_t &address) noexcept {
            memory[address] = value;
        }

        [[maybe_unused]] [[gnu::always_inline]] [[nodiscard]] static inline uint16_t Read(const uint16_t &address) noexcept {
            return memory[address];
        }

};