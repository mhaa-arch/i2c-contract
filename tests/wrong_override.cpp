#include <i2c/controller.hpp>

using namespace mhaa::i2c;

class WrongOverride final : public Controller
{
public:
    bool set_frequency_hz(uint32_t frequency_hz) const override;
};
