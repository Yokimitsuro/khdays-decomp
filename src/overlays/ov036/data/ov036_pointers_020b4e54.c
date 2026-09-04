/* ov036 .data pointer tables, 0x020b4e54-0x020b4e68.
 *
 * 1 table, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

typedef void (*Ov_Fn)(void);

extern void func_ov022_020915bc(void);
extern void func_ov022_020916e0(void);
extern void func_ov036_020b3e44(void);
extern void func_ov036_020b3f00(void);

Ov_Fn data_ov036_020b4e54[5] = {

    0,

    func_ov022_020915bc,

    func_ov036_020b3e44,

    func_ov022_020916e0,

    func_ov036_020b3f00,

};
