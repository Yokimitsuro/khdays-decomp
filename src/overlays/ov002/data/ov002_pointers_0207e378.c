/* ov002 .rodata pointer tables, 0x0207e378-0x0207e388.
 *
 * 1 table, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

typedef void (*Ov_Fn)(void);

extern void func_ov002_02062a00(void);
extern void func_ov002_02062a04(void);
extern void func_ov002_02062ad8(void);
extern void func_ov002_02062b30(void);

const Ov_Fn data_ov002_0207e378[4] = {

    func_ov002_02062a00,

    func_ov002_02062a04,

    func_ov002_02062ad8,

    func_ov002_02062b30,

};
