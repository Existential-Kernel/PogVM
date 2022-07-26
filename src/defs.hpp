#include <filesystem>

#pragma once

#if __cpp_attributes 
    #if __has_cpp_attribute(gnu::hot)
        #define GNU_HOT [[gnu::hot]]
    #else
        #define GNU_HOT
    #endif

    #if __has_cpp_attribute(gnu::always_inline)
        #define GNU_INLINE [[gnu::always_inline]]
    #else
        #define GNU_INLINE
    #endif
#else
	#define GNU_HOT
    #define GNU_INLINE
#endif

namespace INFO {
    std::string program = "PogVM";
    char major       = 1;
    char minor       = 0;
    std::string link    = "https://github.com/Existential-Kernel/PogVM";

    const std::string version = program + " version " + major + "." + minor;
    const std::string information = version \
    + "\nMade by Existential-Kernel (" + link \
    + ")\nCopyright 2022 Existential-Kernel\nLicense: WTFPL";
};

namespace OUTPUT {
	// Output the version of the program
    [[noreturn]] static void Version(void);

    // Display the help menu
    [[noreturn]] static void HelpMenu(void);

    // Log errors
    [[noreturn]] static void Error(const std::string &error, const uint8_t &code, const std::string &arg = "");

    // Abort log
    [[noreturn]] static void Abort(const std::string &error);
};

namespace UTIL {
    [[nodiscard]] bool FileExists(const std::filesystem::path &path, const std::filesystem::file_status &status = std::filesystem::file_status{});

    [[nodiscard]] static bool CheckExtension(const std::string &file, const std::string &extension);

    void PogVM_Preprocess(void);

    [[nodiscard]] static inline uint64_t getCycles(void);

    [[nodiscard]] static inline uint32_t getMillisecondCounter(void);

    // clock speed in kilohertz
    [[nodiscard]] volatile static inline uint64_t getClockSpeed(void);
}

// For debugging or development purposes only
namespace DEV {
    [[maybe_unused]] static inline void ClearConsole(void);

    [[maybe_unused, noreturn]] static void BP(const std::string &message);

    [[maybe_unused]] static std::string IntToHex(const uint64_t &integer);

};