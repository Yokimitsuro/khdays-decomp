/* ov095 .data pointer tables, 0x020bcb08-0x020bcb1c.
 *
 * 1 table, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

typedef void (*Ov_Fn)(void);

extern void func_ov022_020915bc(void);
extern void func_ov022_020916e0(void);
extern void func_ov095_020bba84(void);
extern void func_ov095_020bba9c(void);

Ov_Fn data_ov095_020bcb08[5] = {

    0,

    func_ov022_020915bc,

    func_ov095_020bba84,

    func_ov022_020916e0,

    func_ov095_020bba9c,

};
