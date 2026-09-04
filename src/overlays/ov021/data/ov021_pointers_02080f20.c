/* ov021 .data pointer tables, 0x02080f20-0x02080f40.
 *
 * 1 table, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

typedef void (*Ov_Fn)(void);

extern void func_ov021_02080c98(void);
extern void func_ov021_02080d94(void);
extern void func_ov021_02080e30(void);
extern void func_ov021_02080e7c(void);

Ov_Fn data_ov021_02080f20[8] = {

    func_ov021_02080c98,

    0,

    func_ov021_02080d94,

    0,

    func_ov021_02080e30,

    0,

    func_ov021_02080e7c,

    0,

};
