# Porting the I2C Contract

The portable surface is seven-bit controller mode. Hardware Definitions describe bus instances and fixed hardware capabilities. The Adapter chooses available nominal rates, supported transaction lengths, a suitable time source and a bus recovery strategy. Some controllers perform the phases internally while others drive them individually. Both must expose the same repeated START, ACK/NACK and closure semantics.

This repository's host simulations and shared API compile/link checks provide source-level evidence. Target timing and physical behavior require hardware validation.
