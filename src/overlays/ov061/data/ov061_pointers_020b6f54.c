/* ov061 .data pointer tables, 0x020b6f54-0x020b6f68.
 *
 * 1 table, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

typedef void (*Ov_Fn)(void);

extern void func_ov022_020915bc(void);
extern void func_ov022_020916e0(void);
extern void func_ov022_0209183c(void);

Ov_Fn data_ov061_020b6f54[5] = {

    0,

    func_ov022_020915bc,

    0,

    func_ov022_020916e0,

    func_ov022_0209183c,

};
