/* ov102 .data pointer tables, 0x020bb880-0x020bb894.
 *
 * 1 table, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

typedef void (*Ov_Fn)(void);

extern void func_ov022_020915bc(void);
extern void func_ov022_020916e0(void);
extern void func_ov022_0209183c(void);
extern void func_ov102_020bb19c(void);

Ov_Fn data_ov102_020bb880[5] = {

    0,

    func_ov022_020915bc,

    func_ov102_020bb19c,

    func_ov022_020916e0,

    func_ov022_0209183c,

};
