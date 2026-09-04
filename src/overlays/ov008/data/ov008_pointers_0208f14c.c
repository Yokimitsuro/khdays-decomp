/* ov008 .rodata pointer tables, 0x0208f14c-0x0208f15c.
 *
 * 1 table, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

typedef void (*Ov_Fn)(void);

extern void func_ov008_02065664(void);
extern void func_ov008_020658bc(void);
extern void func_ov008_02065990(void);

const Ov_Fn data_ov008_0208f14c[4] = {

    0,

    func_ov008_02065664,

    func_ov008_020658bc,

    func_ov008_02065990,

};
