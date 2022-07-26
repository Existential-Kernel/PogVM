#pragma once

class AUDIT {
    public:
        AUDIT();
        ~AUDIT();

    private:
        // Log the initialisation process if it succeeded or failed
        static constexpr void AuditLog(const uint8_t &result, const std::string &message);

        [[nodiscard]] static constexpr inline bool ArchCheck(void);

        // Check if there's at least 4 threads in the end-user's CPU for pipelining
        [[nodiscard]] static inline bool CPUThreadCheck(void);

        // Check if CPU cores are working as expected
        [[nodiscard]] static inline bool CPUCoreCheck(void);

        [[nodiscard]] static inline bool CPUClockSpeedCheck(void);

    public:
        // Checks all the necessary processes and data needed to run the machine
        static void AuditCheck(void);
};