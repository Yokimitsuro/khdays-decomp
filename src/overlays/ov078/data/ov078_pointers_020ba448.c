/* ov078 .data pointer tables, 0x020ba448-0x020ba45c.
 *
 * 1 table, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

typedef void (*Ov_Fn)(void);

extern void func_ov022_020915bc(void);
extern void func_ov022_020916e0(void);
extern void func_ov078_020b93c4(void);
extern void func_ov078_020b93dc(void);

Ov_Fn data_ov078_020ba448[5] = {

    0,

    func_ov022_020915bc,

    func_ov078_020b93c4,

    func_ov022_020916e0,

    func_ov078_020b93dc,

};
