/* ov084 .data pointer tables, 0x020b9994-0x020b99a8.
 *
 * 1 table, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

typedef void (*Ov_Fn)(void);

extern void func_ov022_020915bc(void);
extern void func_ov022_020916e0(void);
extern void func_ov084_020b8b18(void);
extern void func_ov084_020b8c74(void);

Ov_Fn data_ov084_020b9994[5] = {

    0,

    func_ov022_020915bc,

    func_ov084_020b8b18,

    func_ov022_020916e0,

    func_ov084_020b8c74,

};
