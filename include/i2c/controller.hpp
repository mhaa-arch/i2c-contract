#ifndef MHAA_I2C_CONTROLLER_HPP
#define MHAA_I2C_CONTROLLER_HPP

#include <stdint.h>
#include <i2c/types.hpp>

namespace mhaa
{
    namespace i2c
    {
        /** @brief Executes complete controller-mode transactions on a configured bus. */
        class Controller
        {
        public:
            virtual ~Controller() = default;

            /** @brief Accepts a nonzero nominal bus frequency when supported. */
            virtual bool set_frequency_hz(uint32_t frequency_hz) = 0;

            /** @brief Runs both phases under one budget, using repeated START when both are present.
             *  @return Status and completed byte counts. Only the reported read prefix changes.
             */
            virtual Result transact(const Transaction &transaction) = 0;
        };
    }
}

#endif
