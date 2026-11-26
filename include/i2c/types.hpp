#ifndef MHAA_I2C_TYPES_HPP
#define MHAA_I2C_TYPES_HPP

#include <stdint.h>
#include <stddef.h>

namespace mhaa
{
    namespace i2c
    {
        enum class Status
        {
            Success,
            Busy,
            InvalidArgument,
            Unsupported,
            AddressNack,
            DataNack,
            ArbitrationLost,
            BusError,
            Timeout
        };

        struct Transaction
        {
            uint16_t address;
            const uint8_t *write_data;
            size_t write_size;
            uint8_t *read_data;
            size_t read_size;
            uint32_t timeout_ms;
        };

        struct Result
        {
            Status status;
            size_t written;
            size_t read;
        };
    }
}

#endif
