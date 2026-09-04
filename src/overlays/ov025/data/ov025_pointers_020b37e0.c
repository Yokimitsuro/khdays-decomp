/* ov025 .rodata pointer tables, 0x020b37e0-0x020b3808.
 *
 * 1 table, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

typedef void (*Ov_Fn)(void);

extern void func_ov025_02083338(void);
extern void func_ov025_020835e0(void);
extern void func_ov025_02083648(void);
extern void func_ov025_02083680(void);
extern void func_ov025_02083758(void);
extern void func_ov025_02083828(void);
extern void func_ov025_02083888(void);
extern void func_ov025_020838e0(void);
extern void func_ov025_020839f0(void);

const Ov_Fn data_ov025_020b37e0[10] = {

    0,

    func_ov025_02083338,

    func_ov025_020835e0,

    func_ov025_02083648,

    func_ov025_02083680,

    func_ov025_02083758,

    func_ov025_02083828,

    func_ov025_02083888,

    func_ov025_020839f0,

    func_ov025_020838e0,

};
