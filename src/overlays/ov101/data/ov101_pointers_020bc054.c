/* ov101 .data pointer tables, 0x020bc054-0x020bc068.
 *
 * 1 table, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

typedef void (*Ov_Fn)(void);

extern void func_ov022_020915bc(void);
extern void func_ov022_020916e0(void);
extern void func_ov101_020bb1d8(void);
extern void func_ov101_020bb334(void);

Ov_Fn data_ov101_020bc054[5] = {

    0,

    func_ov022_020915bc,

    func_ov101_020bb1d8,

    func_ov022_020916e0,

    func_ov101_020bb334,

};
