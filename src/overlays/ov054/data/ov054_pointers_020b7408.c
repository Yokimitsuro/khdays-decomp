/* ov054 .data pointer tables, 0x020b7408-0x020b741c.
 *
 * 1 table, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

typedef void (*Ov_Fn)(void);

extern void func_ov022_020915bc(void);
extern void func_ov022_020916e0(void);
extern void func_ov022_0209183c(void);
extern void func_ov054_020b6b2c(void);

Ov_Fn data_ov054_020b7408[5] = {

    0,

    func_ov022_020915bc,

    func_ov054_020b6b2c,

    func_ov022_020916e0,

    func_ov022_0209183c,

};
