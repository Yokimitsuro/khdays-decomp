/* ov047 .data pointer tables, 0x020b42e0-0x020b42f4.
 *
 * 1 table, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

typedef void (*Ov_Fn)(void);

extern void func_ov022_020915bc(void);
extern void func_ov022_020916e0(void);
extern void func_ov022_0209183c(void);
extern void func_ov047_020b3bfc(void);

Ov_Fn data_ov047_020b42e0[5] = {

    0,

    func_ov022_020915bc,

    func_ov047_020b3bfc,

    func_ov022_020916e0,

    func_ov022_0209183c,

};
