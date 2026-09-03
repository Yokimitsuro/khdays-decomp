/* ov002 .rodata pointer tables, 0x0207dc60-0x0207dc90.
 *
 * 1 table, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

typedef void (*Ov_Fn)(void);

extern void func_ov002_02055ba8(void);
extern void func_ov002_02055bd0(void);
extern void func_ov002_02055c14(void);
extern void func_ov002_02055c38(void);
extern void func_ov002_02055d60(void);
extern void func_ov002_02055f38(void);
extern void func_ov002_02055fac(void);
extern void func_ov002_020560d8(void);
extern void func_ov002_02056118(void);
extern void func_ov002_020561ac(void);
extern void func_ov002_02056258(void);
extern void func_ov002_020562ec(void);

const Ov_Fn data_ov002_0207dc60[12] = {

    func_ov002_02055ba8,

    func_ov002_02055bd0,

    func_ov002_02055c14,

    func_ov002_02055c38,

    func_ov002_02055d60,

    func_ov002_02055f38,

    func_ov002_02055fac,

    func_ov002_020560d8,

    func_ov002_02056118,

    func_ov002_020561ac,

    func_ov002_02056258,

    func_ov002_020562ec,

};
