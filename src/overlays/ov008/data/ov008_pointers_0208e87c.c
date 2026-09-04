/* ov008 .rodata pointer tables, 0x0208e87c-0x0208e8a4.
 *
 * 1 table, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

typedef void (*Ov_Fn)(void);

extern void func_ov008_0204f510(void);
extern void func_ov008_0204f7b8(void);
extern void func_ov008_0204f820(void);
extern void func_ov008_0204f858(void);
extern void func_ov008_0204f930(void);
extern void func_ov008_0204fa00(void);
extern void func_ov008_0204fa60(void);
extern void func_ov008_0204fab8(void);
extern void func_ov008_0204fbc8(void);

const Ov_Fn data_ov008_0208e87c[10] = {

    0,

    func_ov008_0204f510,

    func_ov008_0204f7b8,

    func_ov008_0204f820,

    func_ov008_0204f858,

    func_ov008_0204f930,

    func_ov008_0204fa00,

    func_ov008_0204fa60,

    func_ov008_0204fbc8,

    func_ov008_0204fab8,

};
