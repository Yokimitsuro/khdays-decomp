/* ov091 .data pointer tables, 0x020bc1a8-0x020bc1bc.
 *
 * 1 table, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

typedef void (*Ov_Fn)(void);

extern void func_ov022_020915bc(void);
extern void func_ov022_020916e0(void);
extern void func_ov022_0209183c(void);
extern void func_ov091_020bb8cc(void);

Ov_Fn data_ov091_020bc1a8[5] = {

    0,

    func_ov022_020915bc,

    func_ov091_020bb8cc,

    func_ov022_020916e0,

    func_ov022_0209183c,

};
