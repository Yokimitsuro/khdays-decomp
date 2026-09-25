/* DS Protect 1.10 encrypted-range markers.
 *
 * The library brackets the instructions it keeps encrypted with two hand-written sequences
 * (they pass pc to the range helpers and keep the range key inline, which C cannot express):
 * the opening one decrypts everything up to the matching key before running it, the closing one
 * encrypts it again. tools/dsprot_encode.py encrypts the ranges after compilation, as the
 * library's own build did, so nothing inside a range may need a relocation. */
#ifndef DSPROT_RANGES_H
#define DSPROT_RANGES_H

extern void func_ov028_0208a7e0(unsigned int *pRange);   /* Encryptor_StartRange */
extern void func_ov028_0208a8ac(unsigned int *pRange);   /* Encryptor_EndRange */

#define DSPROT_RANGE_BEGIN(key)                 \
    asm {                                       \
        stmfd sp!, {r0-r7};                     \
        mov r0, #6;                             \
        add r0, pc, r0, lsl #1;                 \
        bl func_ov028_0208a7e0;                 \
        ldmia sp!, {r0-r7};                     \
        b @begin_##key;                         \
        dcd 0xEB000000 + key;                   \
    @begin_##key:                               \
    }

#define DSPROT_RANGE_END(key)                   \
    asm {                                       \
        b @end_##key;                           \
        dcd 0xEB000000 + key;                   \
    @end_##key:                                 \
        stmfd sp!, {r0};                        \
        mov r0, pc;                             \
        sub r0, r0, #0x14;                      \
        bl func_ov028_0208a8ac;                 \
        ldmfd sp!, {r0};                        \
    }

#endif
