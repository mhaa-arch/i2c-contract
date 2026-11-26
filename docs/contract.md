# I2C contract

## Transaction shape and timing

[Controller](../include/i2c/controller.hpp) accepts a supported positive nominal bus rate and runs complete controller transactions described by [Transaction and Result](../include/i2c/types.hpp). Pass an unshifted seven-bit address. Each nonempty phase needs a buffer of the declared length. Phase buffers can be identical or disjoint. Zero length omits that phase, and two valid empty phases succeed without a bus operation.

The positive millisecond timeout is one finite budget for the whole transaction, including successful closure. `UINT32_MAX` is a finite value. Use a time source that advances while the operation runs. A write/read pair uses a repeated START. ACK all but the final received byte, which gets NACK.

## Completion and cleanup

`written` counts acknowledged payload bytes and `read` counts received payload bytes. Only the received prefix may change. A failed close reports `BusError` or `Timeout` even if payload counts are complete. After a started transaction attempt STOP on error if bus ownership remains. After arbitration loss refrain from issuing STOP.

Use `Busy` when the bus cannot be acquired, `InvalidArgument` for an invalid shape, `Unsupported` for options outside the Adapter's supported set, and distinguish address and data NACK. An application may need separate target-specific recovery after a bus failure.

## Implementation boundary

The Adapter owns resource state. The caller must keep the implementation and transaction buffers alive during each call and arrange access from other execution contexts. Document the contexts and concurrency guarantees of the actual implementation. Shared public types are in [`i2c/types.hpp`](../include/i2c/types.hpp).

For the bus timeline and retry implications of partial results, see [Transaction flow](transactions.md).
