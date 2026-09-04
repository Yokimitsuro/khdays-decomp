/* ov092 .data pointer tables, 0x020bc3f4-0x020bc408.
 *
 * 1 table, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

typedef void (*Ov_Fn)(void);

extern void func_ov022_020915bc(void);
extern void func_ov022_020916e0(void);
extern void func_ov092_020bb3e4(void);
extern void func_ov092_020bb4a0(void);

Ov_Fn data_ov092_020bc3f4[5] = {

    0,

    func_ov022_020915bc,

    func_ov092_020bb3e4,

    func_ov022_020916e0,

    func_ov092_020bb4a0,

};
