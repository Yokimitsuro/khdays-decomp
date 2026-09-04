/* main .rodata pointer tables, 0x02041eac-0x02041ecc.
 *
 * 1 table, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

typedef void (*Ov_Fn)(void);

extern void func_02024524(void);
extern void func_02024574(void);
extern void func_020247a4(void);
extern void func_020247f4(void);

const Ov_Fn data_02041eac[8] = {

    0,

    0,

    func_02024524,

    func_02024574,

    0,

    0,

    func_020247a4,

    func_020247f4,

};
