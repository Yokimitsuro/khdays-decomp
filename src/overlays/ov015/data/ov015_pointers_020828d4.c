/* ov015 .rodata pointer tables, 0x020828d4-0x020828d8.
 *
 * 1 table, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

typedef void (*Ov_Fn)(void);

extern void func_ov015_0207fe0c(void);

const Ov_Fn data_ov015_020828d4[1] = {

    func_ov015_0207fe0c,

};
