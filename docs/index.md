# I2C Contract guide

A combined write/read is one transaction with a repeated START. Two separate facade calls have different bus boundaries. Read the transaction shape and byte-count rules before choosing how to retry an operation.

1. Start with [the contract](contract.md) for implementer obligations and capability boundaries.
2. Read [the conformance example](examples.md) for an implementation you can compile locally.
3. Consult [the portability notes](compatibility.md) before choosing a hardware mapping.
For the bus timeline and retry implications of partial results, see [Transaction flow](transactions.md).
