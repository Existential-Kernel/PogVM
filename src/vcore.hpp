#pragma once

#include "cycle/fetch.hpp"
#include "cycle/decode.hpp"
#include "cycle/execute.hpp"

//https://www.cplusplus.com/reference/thread/thread/?kw=thread

class KERNEL final : public FETCH, public DECODE, public EXECUTE {
	public:
		KERNEL();
		~KERNEL();

	private:
		static constexpr void InitHardware(void);
		static bool CheckIfBufferIsEmpty(const std::deque<uint8_t> &buffer);

    public:
	    static void Kernel(const std::string &argv, const uint8_t &bits, const uint8_t &mode, const uint8_t &processor);
};
