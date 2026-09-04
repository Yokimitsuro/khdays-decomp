/* ov064 .data pointer tables, 0x020b7394-0x020b73a8.
 *
 * 1 table, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

typedef void (*Ov_Fn)(void);

extern void func_ov022_020915bc(void);
extern void func_ov022_020916e0(void);
extern void func_ov022_020916e8(void);
extern void func_ov022_0209183c(void);

Ov_Fn data_ov064_020b7394[5] = {

    0,

    func_ov022_020915bc,

    func_ov022_020916e8,

    func_ov022_020916e0,

    func_ov022_0209183c,

};
