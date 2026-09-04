/* ov058 .data pointer tables, 0x020b7d68-0x020b7d7c.
 *
 * 1 table, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

typedef void (*Ov_Fn)(void);

extern void func_ov022_020915bc(void);
extern void func_ov022_020916e0(void);
extern void func_ov058_020b6ce4(void);
extern void func_ov058_020b6cfc(void);

Ov_Fn data_ov058_020b7d68[5] = {

    0,

    func_ov022_020915bc,

    func_ov058_020b6ce4,

    func_ov022_020916e0,

    func_ov058_020b6cfc,

};
