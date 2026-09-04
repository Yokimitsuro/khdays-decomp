/* ov065 .data pointer tables, 0x020b72b4-0x020b72c8.
 *
 * 1 table, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

typedef void (*Ov_Fn)(void);

extern void func_ov022_020915bc(void);
extern void func_ov022_020916e0(void);
extern void func_ov065_020b6438(void);
extern void func_ov065_020b6594(void);

Ov_Fn data_ov065_020b72b4[5] = {

    0,

    func_ov022_020915bc,

    func_ov065_020b6438,

    func_ov022_020916e0,

    func_ov065_020b6594,

};
