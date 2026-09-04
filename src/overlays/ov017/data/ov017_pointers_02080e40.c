/* ov017 .data pointer tables, 0x02080e40-0x02080ea0.
 *
 * 1 table, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

typedef void (*Ov_Fn)(void);

extern void func_ov017_02080a6c(void);
extern void func_ov017_02080b08(void);
extern void func_ov017_02080bcc(void);
extern void func_ov017_02080c40(void);
extern void func_ov017_02080c88(void);
extern void func_ov017_02080cb4(void);
extern void func_ov017_02080d0c(void);
extern void func_ov017_02080dd0(void);
extern void func_ov017_02080dfc(void);

Ov_Fn data_ov017_02080e40[24] = {

    func_ov017_02080a6c,

    0,

    func_ov017_02080b08,

    0,

    func_ov017_02080bcc,

    0,

    func_ov017_02080c40,

    0,

    func_ov017_02080c88,

    0,

    func_ov017_02080cb4,

    0,

    func_ov017_02080d0c,

    0,

    func_ov017_02080dd0,

    0,

    func_ov017_02080dfc,

    0,

    0,

    0,

    0,

    0,

    0,

    0,

};
