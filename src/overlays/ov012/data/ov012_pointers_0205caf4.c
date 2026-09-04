/* ov012 .data pointer tables, 0x0205caf4-0x0205cb20.
 *
 * 1 table, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

typedef void (*Ov_Fn)(void);

extern void func_ov012_0205b940(void);
extern void func_ov012_0205b984(void);
extern void func_ov012_0205b9a8(void);
extern void func_ov012_0205b9e0(void);
extern void func_ov012_0205ba08(void);
extern void func_ov012_0205ba3c(void);
extern void func_ov012_0205ba48(void);

Ov_Fn data_ov012_0205caf4[11] = {

    func_ov012_0205b984,

    0,

    func_ov012_0205ba08,

    0,

    func_ov012_0205b940,

    0,

    func_ov012_0205b9a8,

    func_ov012_0205b9e0,

    func_ov012_0205ba3c,

    func_ov012_0205ba48,

    0,

};
