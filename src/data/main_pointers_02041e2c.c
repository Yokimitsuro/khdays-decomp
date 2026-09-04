/* main .rodata pointer tables, 0x02041e2c-0x02041e6c.
 *
 * 2 tables, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

typedef void (*Ov_Fn)(void);

extern void func_020242f8(void);
extern void func_02024368(void);
extern void func_020243f4(void);
extern void func_0202443c(void);
extern void func_02024484(void);
extern void func_020244d4(void);
extern void func_020245c4(void);
extern void func_0202461c(void);
extern void func_02024674(void);
extern void func_020246bc(void);
extern void func_02024704(void);
extern void func_02024754(void);

const Ov_Fn data_02041e2c[8] = {

    0,

    0,

    func_02024484,

    func_020244d4,

    0,

    0,

    func_02024704,

    func_02024754,

};

const Ov_Fn data_02041e4c[8] = {

    func_020242f8,

    func_02024368,

    func_020243f4,

    func_0202443c,

    func_020245c4,

    func_0202461c,

    func_02024674,

    func_020246bc,

};
