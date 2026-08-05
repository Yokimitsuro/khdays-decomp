/*
 * func_ov002_02050a08 - compute a scaled fixed-point value from the current display mode (ARM).
 *
 * Reads a mode/flags word (func_02023bf0()->[0x20]->[0x3c]) to pick a base scale: 0x1000 normally,
 * 0x800 when bit1 is set, 0x1800 when bit2 is set (bit2 wins as it is tested last). A second factor
 * comes from func_02023c40(): 0x480 when it returns 1, else 0x300. The result is the fixed-point
 * product (factor * scale + 0x800) >> 12, evaluated in 64 bits (smull) with 0x800 rounding before
 * the 12-bit shift.
 */
extern int func_02023bf0(void);
extern int func_02023c40(void);

int func_ov002_02050a08(void)
{
    int flags = *(int *)(*(int *)(func_02023bf0() + 0x20) + 0x3c);
    int scale = 0x1000;
    int factor;
    if (flags & 2) scale = 0x800;
    if (flags & 4) scale = 0x1800;
    factor = (func_02023c40() == 1) ? 0x480 : 0x300;
    return (int)(((long long)factor * scale + 0x800) >> 12);
}
