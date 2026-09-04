/* ov087 .data pointer tables, 0x020b9b28-0x020b9b3c.
 *
 * 1 table, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

typedef void (*Ov_Fn)(void);

extern void func_ov022_020915bc(void);
extern void func_ov022_020916e0(void);
extern void func_ov022_0209183c(void);
extern void func_ov087_020b9344(void);

Ov_Fn data_ov087_020b9b28[5] = {

    0,

    func_ov022_020915bc,

    func_ov087_020b9344,

    func_ov022_020916e0,

    func_ov022_0209183c,

};
