# I2C Contract example

[The conformance program](../tests/conformance.cpp) pairs a simulated implementation with assertions at the Contract boundary. The fake implements `Controller`, accepts 100 kHz and recognizes only address `0x42`. A request to another address produces `AddressNack` while leaving the receive buffer untouched. Then the test uses the same buffer for a one-byte write and a two-byte read, and checks the reported counts. This models the transaction boundary and result, while bus waveforms belong to target testing.

## Implementation excerpt

This class is taken from the program. The linked source contains the test cases and any additional fixtures.

```cpp
#include <i2c/controller.hpp>


using namespace mhaa::i2c;

class Fake final : public Controller
{
public:
    bool set_frequency_hz(uint32_t frequency) override
    {
        configured_ = frequency == 100000;
        return configured_;
    }

    Result transact(const Transaction &transaction) override
    {
        if (!configured_)
        {
            return {Status::Busy, 0, 0};
        }
        if (transaction.address != 0x42)
        {
            return {Status::AddressNack, 0, 0};
        }
        combined = transaction.write_size && transaction.read_size;
        uint8_t reply = 10;
        for (size_t i = 0; i < transaction.read_size; ++i)
        {
            transaction.read_data[i] = reply++;
        }
        return {Status::Success, transaction.write_size, transaction.read_size};
    }

    bool combined = false;

private:
    bool configured_ = false;
};
```

## Build and run

From this repository root, with assertions enabled, compile the full program. A passing run exits with status 0 and prints no output. Use `conformance.exe` on Windows.

```sh
g++ -std=c++11 -Wall -Wextra -Wpedantic -Werror -fno-rtti -fno-exceptions -Iinclude tests/conformance.cpp -o conformance
./conformance
```

To verify enforcement of the abstract interface, compile the two negative sources separately. The first should diagnose an abstract type and the second an incompatible override.

```sh
g++ -std=c++11 -Wall -Wextra -Wpedantic -Werror -fno-rtti -fno-exceptions -Iinclude -fsyntax-only tests/missing_override.cpp
g++ -std=c++11 -Wall -Wextra -Wpedantic -Werror -fno-rtti -fno-exceptions -Iinclude -fsyntax-only tests/wrong_override.cpp
```
