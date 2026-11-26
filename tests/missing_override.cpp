#include <i2c/controller.hpp>

using namespace mhaa::i2c;

class Incomplete final : public Controller
{
public:
    Result transact(const Transaction &transaction) override;
};

int main()
{
    Incomplete implementation;
    (void)implementation;
}
