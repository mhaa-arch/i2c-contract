#include <i2c/controller.hpp>

#include <cassert>

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

int main()
{
    Fake fake;
    Controller &controller = fake;
    assert(controller.set_frequency_hz(100000));
    uint8_t buffer[] = {42, 73};
    const Result missing = controller.transact({0x52, nullptr, 0, buffer, 2, 1});
    assert(missing.status == Status::AddressNack && missing.read == 0);
    assert(buffer[0] == 42 && buffer[1] == 73);
    const Result combined = controller.transact({0x42, buffer, 1, buffer, 2, 1});
    assert(fake.combined && combined.status == Status::Success);
    assert(combined.written == 1 && combined.read == 2 && buffer[1] == 11);
}
