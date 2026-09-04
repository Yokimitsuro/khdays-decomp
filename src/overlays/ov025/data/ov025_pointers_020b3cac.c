/* ov025 .rodata pointer tables, 0x020b3cac-0x020b3cbc.
 *
 * 1 table, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

typedef void (*Ov_Fn)(void);

extern void func_ov025_02097b90(void);
extern void func_ov025_02097de8(void);
extern void func_ov025_02097ebc(void);

const Ov_Fn data_ov025_020b3cac[4] = {

    0,

    func_ov025_02097b90,

    func_ov025_02097de8,

    func_ov025_02097ebc,

};
