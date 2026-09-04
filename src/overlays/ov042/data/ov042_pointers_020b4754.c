/* ov042 .data pointer tables, 0x020b4754-0x020b4768.
 *
 * 1 table, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

typedef void (*Ov_Fn)(void);

extern void func_ov022_020915bc(void);
extern void func_ov022_020916e0(void);
extern void func_ov022_0209183c(void);

Ov_Fn data_ov042_020b4754[5] = {

    0,

    func_ov022_020915bc,

    0,

    func_ov022_020916e0,

    func_ov022_0209183c,

};
