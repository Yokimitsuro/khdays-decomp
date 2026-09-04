/* ov005 .rodata pointer tables, 0x0205b368-0x0205b38c.
 *
 * 1 table, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

typedef void (*Ov_Fn)(void);

extern void func_ov005_020540b4(void);
extern void func_ov005_020545f8(void);
extern void func_ov005_02054674(void);
extern void func_ov005_02054774(void);
extern void func_ov005_020547e4(void);
extern void func_ov005_020549bc(void);
extern void func_ov005_02054a10(void);
extern void func_ov005_02054a4c(void);
extern void func_ov005_02054ad0(void);

const Ov_Fn data_ov005_0205b368[9] = {

    func_ov005_020540b4,

    func_ov005_020545f8,

    func_ov005_02054674,

    func_ov005_02054774,

    func_ov005_020547e4,

    func_ov005_020549bc,

    func_ov005_02054a10,

    func_ov005_02054a4c,

    func_ov005_02054ad0,

};
