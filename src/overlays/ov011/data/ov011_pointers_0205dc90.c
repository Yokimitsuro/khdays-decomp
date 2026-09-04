/* ov011 .rodata pointer tables, 0x0205dc90-0x0205dca0.
 *
 * 1 table, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

typedef void (*Ov_Fn)(void);

extern void func_ov011_0205aff4(void);
extern void func_ov011_0205b014(void);
extern void func_ov011_0205c04c(void);
extern void func_ov011_0205c060(void);

const Ov_Fn data_ov011_0205dc90[4] = {

    func_ov011_0205aff4,

    func_ov011_0205c04c,

    func_ov011_0205b014,

    func_ov011_0205c060,

};
