/* ov008 .rodata pointer tables, 0x0208fd8c-0x0208fdc8.
 *
 * 1 table, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

typedef void (*Ov_Fn)(void);

extern void func_ov008_0208101c(void);
extern void func_ov008_020810b0(void);
extern void func_ov008_020810b4(void);
extern void func_ov008_02081148(void);
extern void func_ov008_0208114c(void);
extern void func_ov008_020812d0(void);
extern void func_ov008_02081428(void);
extern void func_ov008_0208142c(void);
extern void func_ov008_02081430(void);
extern void func_ov008_02081458(void);
extern void func_ov008_0208145c(void);
extern void func_ov008_02081544(void);
extern void func_ov008_02081570(void);
extern void func_ov008_02081574(void);
extern void func_ov008_02081650(void);

const Ov_Fn data_ov008_0208fd8c[15] = {

    func_ov008_0208101c,

    func_ov008_020810b0,

    func_ov008_020810b4,

    func_ov008_02081148,

    func_ov008_0208114c,

    func_ov008_020812d0,

    func_ov008_02081428,

    func_ov008_0208142c,

    func_ov008_02081430,

    func_ov008_02081458,

    func_ov008_0208145c,

    func_ov008_02081544,

    func_ov008_02081570,

    func_ov008_02081574,

    func_ov008_02081650,

};
