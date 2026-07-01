# Progress policy

This project separates progress into several categories so contributors and
external trackers can see what has actually been decompiled into C.

## Real C decompilation

A function counts as real C decompilation only when it is implemented in C and
passes byte-exact verification against the original code.

## ASM stubs

ASM stubs, inline ASM, or placeholder assembly may be used temporarily while the
project is being bootstrapped.

These functions may match the original bytes, but they do not count as
C-decompiled progress.

## SDK identification

SDK/library functions identified through byte matching are useful for naming and
understanding the binary, but they are tracked separately from game-code
decompilation.

## Named-only functions

A function may have a known or provisional name before it has a real C
implementation. Names are useful for research, but they do not count as
C-decompiled progress.

## Why this matters

The goal is to keep progress reporting honest and useful for contributors and
external project trackers such as decomp.dev. Byte-exact matching remains the
technical verification gate, but public C progress only counts real C
implementations.
