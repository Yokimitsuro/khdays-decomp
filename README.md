# khdays-decomp

A work-in-progress **matching decompilation** of *Kingdom Hearts 358/2 Days*
(Nintendo DS). The goal is C source that recompiles to a binary **byte-for-byte
identical** to the original game code.

> ### ⚠️ Disclaimer
> This repository does **NOT** contain the game ROM, any game assets, or any of
> the original binary/assembly. **An existing, legally-obtained copy of the game
> is required** to extract and build it.
>
> This project **is not, and will not, produce a port** to PC or any other
> platform. It is a decompilation of the original game code that can be compiled
> back into a binary identical to the original. All trademarks and the original
> game are property of their respective owners.

## Status

| | |
|---|---|
| Functions matched (byte-exact, in `src/`) | **2,959** / ~23,240 (~12.7%) |
| NitroSDK functions identified by byte-match | **+979** / ~23,240 (~4.2%) |
| Total functions named or decompiled | **~3,938** / ~23,240 (~17.0%) |
| Region | EU (`YKGP`) |
| Compiler | CodeWarrior `mwccarm` 3.0 build 139 |

Every committed function is verified byte-exact against the original — see
[CONTRIBUTING.md](CONTRIBUTING.md).

The 979 NitroSDK identifications come from compiling reference SDK source
(via `pret/pokediamond`) with our `mwccarm` and matching the produced bytes
against `build/func_index.json`. They are *named* rather than re-decompiled
into `src/`. See [sdk/README.md](sdk/README.md) for the workflow and
per-module match rates.

## Repository layout

```
src/auto/     decompiled leaf functions (no external calls)
src/calls/    decompiled functions that call other functions
config/        dsd project config (symbols / delinks / relocs per module)
macros/        assembler macros (function.inc)
tools/         Python tooling (extraction, matching, candidate finders)
sdk/           NitroSDK byte-match identification harness (see sdk/README.md)
build/         manifests (decompiled.txt); build output is git-ignored
```

The ROM, the extracted data (`dsd_extract/`, `asm/`), build artifacts, and the
proprietary toolchain are intentionally **not** tracked — see `.gitignore`.

## Building / verifying

You need your own copy of the game plus the toolchain (see
[CONTRIBUTING.md](CONTRIBUTING.md) for setup). Then, to verify a single function:

```sh
python tools/getcand.py func_XXXXXXXX        # prints disasm + the verify command
python tools/match.py <your.c> <...>          # compiles and byte-compares
```

A green `>>> MATCH <<<` means your C reproduces the original exactly.

## Toolchain

- [`dsd`](https://github.com/AetiasHax/ds-decomp) — DS ROM extraction / delinking
- `mwccarm` 3.0 (CodeWarrior for Nintendo DS) — the matching compiler
- `arm-none-eabi-as` (GNU binutils) — assembling the not-yet-decompiled `.s`
- Python 3 with `capstone`, `pyelftools`, `ndspy`

See the [Nintendo DS decompilation guide](https://decomp.wiki/platforms/nintendo-ds).

## Contributing

Contributions are very welcome — see **[CONTRIBUTING.md](CONTRIBUTING.md)**. The
only hard rule: every function must pass **byte-exact verification**. Progress
per module and how to claim one is in **[PROGRESS.md](PROGRESS.md)**.

## License

The decompilation and tooling in this repository are dedicated to the public
domain under [CC0 1.0](LICENSE). This applies only to the contributors' own
work; the original game and its assets remain the property of their owners.
