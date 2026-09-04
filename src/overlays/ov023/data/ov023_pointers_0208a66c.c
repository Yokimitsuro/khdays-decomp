/* ov023 .data pointer tables, 0x0208a66c-0x0208a69c.
 *
 * 1 table, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

typedef void (*Ov_Fn)(void);

extern void func_ov023_02086f6c(void);
extern void func_ov023_02086f8c(void);
extern void func_ov023_02086fac(void);
extern void func_ov023_02087018(void);
extern void func_ov023_0208708c(void);
extern void func_ov023_0208709c(void);
extern void func_ov023_020870a0(void);
extern void func_ov023_02087114(void);

Ov_Fn data_ov023_0208a66c[12] = {

    func_ov023_02086f6c,

    0,

    func_ov023_02086f8c,

    0,

    func_ov023_02086fac,

    func_ov023_02087018,

    func_ov023_0208708c,

    0,

    func_ov023_0208709c,

    func_ov023_020870a0,

    func_ov023_02087114,

    0,

};
