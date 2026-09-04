/* ov009 .rodata pointer tables, 0x02055f88-0x02055fb0.
 *
 * 1 table, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

typedef void (*Ov_Fn)(void);

extern void func_ov009_0204d224(void);
extern void func_ov009_0204d35c(void);
extern void func_ov009_0204d3c4(void);
extern void func_ov009_0204d3fc(void);
extern void func_ov009_0204d4d4(void);
extern void func_ov009_0204d5a4(void);
extern void func_ov009_0204d604(void);
extern void func_ov009_0204d65c(void);
extern void func_ov009_0204d76c(void);

const Ov_Fn data_ov009_02055f88[10] = {

    0,

    func_ov009_0204d224,

    func_ov009_0204d35c,

    func_ov009_0204d3c4,

    func_ov009_0204d3fc,

    func_ov009_0204d4d4,

    func_ov009_0204d5a4,

    func_ov009_0204d604,

    func_ov009_0204d76c,

    func_ov009_0204d65c,

};
