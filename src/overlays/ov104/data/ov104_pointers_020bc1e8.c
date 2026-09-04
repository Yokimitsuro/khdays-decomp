/* ov104 .data pointer tables, 0x020bc1e8-0x020bc1fc.
 *
 * 1 table, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

typedef void (*Ov_Fn)(void);

extern void func_ov022_020915bc(void);
extern void func_ov022_020916e0(void);
extern void func_ov022_0209183c(void);
extern void func_ov104_020bba04(void);

Ov_Fn data_ov104_020bc1e8[5] = {

    0,

    func_ov022_020915bc,

    func_ov104_020bba04,

    func_ov022_020916e0,

    func_ov022_0209183c,

};
