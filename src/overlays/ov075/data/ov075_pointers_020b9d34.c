/* ov075 .data pointer tables, 0x020b9d34-0x020b9d48.
 *
 * 1 table, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

typedef void (*Ov_Fn)(void);

extern void func_ov022_020915bc(void);
extern void func_ov022_020916e0(void);
extern void func_ov075_020b8d24(void);
extern void func_ov075_020b8de0(void);

Ov_Fn data_ov075_020b9d34[5] = {

    0,

    func_ov022_020915bc,

    func_ov075_020b8d24,

    func_ov022_020916e0,

    func_ov075_020b8de0,

};
