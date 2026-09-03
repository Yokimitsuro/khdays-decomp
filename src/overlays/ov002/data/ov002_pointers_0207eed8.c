/* ov002 .data pointer tables, 0x0207eed8-0x0207eee8.
 *
 * 1 table, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

typedef void (*Ov_Fn)(void);

extern void func_ov002_0206739c(void);
extern void func_ov002_020673d4(void);
extern void func_ov002_02067404(void);

Ov_Fn data_ov002_0207eed8[4] = {

    func_ov002_02067404,

    func_ov002_0206739c,

    func_ov002_020673d4,

    0,

};
