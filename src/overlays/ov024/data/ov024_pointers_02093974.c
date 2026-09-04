/* ov024 .data pointer tables, 0x02093974-0x020939ac.
 *
 * 1 table, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

typedef void (*Ov_Fn)(void);

extern void func_ov024_02083368(void);
extern void func_ov024_020833b8(void);
extern void func_ov024_020833dc(void);
extern void func_ov024_02083414(void);
extern void func_ov024_0208343c(void);
extern void func_ov024_02083468(void);
extern void func_ov024_02083474(void);
extern void func_ov024_02083488(void);
extern void func_ov024_0208349c(void);

Ov_Fn data_ov024_02093974[14] = {

    func_ov024_020833b8,

    0,

    func_ov024_0208343c,

    0,

    func_ov024_02083368,

    0,

    func_ov024_020833dc,

    func_ov024_02083414,

    func_ov024_02083468,

    func_ov024_02083474,

    func_ov024_02083488,

    0,

    func_ov024_0208349c,

    0,

};
