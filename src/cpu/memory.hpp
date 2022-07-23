#include "../defs.hpp"
#include <algorithm>
#include <array>

#pragma once

// TODO: fix this part by switching it to a class than a namespace and other stuff

namespace MEMORY {
//    private:
        static constexpr uint16_t MAX_MEM = UINT16_MAX; // 2^16 bits of memory
        //static constexpr uint16_t MAX_MEM = 1 << 16; // 2^16 bits of memory

//    public:
        //static std::array<uint8_t, MAX_MEM> memory;

        //static uint8_t memory[MAX_MEM];
        std::array<uint8_t, MAX_MEM> memory;
        [[nodiscard]] static constexpr inline bool Initialise() noexcept {
            try {
                std::fill (memory.begin(), memory.end(), 0);
                return true;
            } catch (...) {
                return false;
            }
        }

        [[maybe_unused]] GNU_INLINE static inline void Write(const uint8_t &value, const uint16_t &address) noexcept {
            memory[address] = value;
        }

        [[maybe_unused, nodiscard]] GNU_INLINE static inline uint16_t Read(const uint16_t &address) noexcept {
            return memory[address];
        }

};