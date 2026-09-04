/* ov046 .data pointer tables, 0x020b4ab4-0x020b4ac8.
 *
 * 1 table, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

typedef void (*Ov_Fn)(void);

extern void func_ov022_020915bc(void);
extern void func_ov022_020916e0(void);
extern void func_ov046_020b3c38(void);
extern void func_ov046_020b3d94(void);

Ov_Fn data_ov046_020b4ab4[5] = {

    0,

    func_ov022_020915bc,

    func_ov046_020b3c38,

    func_ov022_020916e0,

    func_ov046_020b3d94,

};
