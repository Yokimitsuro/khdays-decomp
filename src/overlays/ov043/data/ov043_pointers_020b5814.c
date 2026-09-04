/* ov043 .data pointer tables, 0x020b5814-0x020b5828.
 *
 * 1 table, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

typedef void (*Ov_Fn)(void);

extern void func_ov022_020915bc(void);
extern void func_ov022_020916e0(void);
extern void func_ov043_020b547c(void);

Ov_Fn data_ov043_020b5814[5] = {

    0,

    func_ov022_020915bc,

    func_ov043_020b547c,

    func_ov022_020916e0,

    0,

};
