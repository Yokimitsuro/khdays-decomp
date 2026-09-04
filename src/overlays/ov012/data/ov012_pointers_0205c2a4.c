/* ov012 .data pointer tables, 0x0205c2a4-0x0205c2bc.
 *
 * 1 table, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

typedef void (*Ov_Fn)(void);

extern void func_ov012_0205b2a4(void);
extern void func_ov012_0205b32c(void);
extern void func_ov012_0205b3a4(void);
extern void func_ov012_0205b3d4(void);
extern void func_ov012_0205b4b0(void);
extern void func_ov012_0205b57c(void);

Ov_Fn data_ov012_0205c2a4[6] = {

    func_ov012_0205b2a4,

    func_ov012_0205b32c,

    func_ov012_0205b3a4,

    func_ov012_0205b3d4,

    func_ov012_0205b4b0,

    func_ov012_0205b57c,

};
