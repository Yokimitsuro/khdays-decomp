/* ov019 .data pointer tables, 0x0207fd60-0x0207fd78.
 *
 * 1 table, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

typedef void (*Ov_Fn)(void);

extern void func_ov019_0207fa40(void);
extern void func_ov019_0207fa94(void);
extern void func_ov019_0207fc88(void);
extern void func_ov019_0207fcc0(void);
extern void func_ov019_0207fcdc(void);

Ov_Fn data_ov019_0207fd60[6] = {

    func_ov019_0207fa40,

    0,

    func_ov019_0207fa94,

    func_ov019_0207fc88,

    func_ov019_0207fcc0,

    func_ov019_0207fcdc,

};
