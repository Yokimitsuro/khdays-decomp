/* ov024 .data pointer tables, 0x020939c4-0x02093a20.
 *
 * 2 tables, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

typedef void (*Ov_Fn)(void);

extern void func_ov024_02084f98(void);
extern void func_ov024_020850e0(void);
extern void func_ov024_020850e4(void);
extern void func_ov024_02085e8c(void);
extern void func_ov024_02085ed8(void);
extern void func_ov024_02085f48(void);
extern void func_ov024_02085fc4(void);
extern void func_ov024_02085fec(void);
extern void func_ov024_02086000(void);

Ov_Fn data_ov024_020939c4[9] = {

    func_ov024_020850e0,

    func_ov024_020850e4,

    0,

    0,

    0,

    0,

    0,

    0,

    0,

};

Ov_Fn data_ov024_020939e8[14] = {

    func_ov024_02086000,

    func_ov024_02084f98,

    func_ov024_02085e8c,

    func_ov024_02085ed8,

    func_ov024_02085f48,

    func_ov024_02085fc4,

    func_ov024_02085fec,

    0,

    0,

    0,

    0,

    0,

    0,

    0,

};
