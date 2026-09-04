/* ov020 .data pointer tables, 0x020800c0-0x020800d8.
 *
 * 1 table, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

typedef void (*Ov_Fn)(void);

extern void func_ov020_0207fa40(void);
extern void func_ov020_0207fa7c(void);
extern void func_ov020_0207fac8(void);

Ov_Fn data_ov020_020800c0[6] = {

    func_ov020_0207fa40,

    0,

    func_ov020_0207fa7c,

    0,

    func_ov020_0207fac8,

    0,

};
