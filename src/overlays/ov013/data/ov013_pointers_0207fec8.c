/* ov013 .data pointer tables, 0x0207fec8-0x0207fee0.
 *
 * 1 table, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

typedef void (*Ov_Fn)(void);

extern void func_ov013_0207fe40(void);
extern void func_ov013_0207fe98(void);

Ov_Fn data_ov013_0207fec8[6] = {

    func_ov013_0207fe40,

    0,

    func_ov013_0207fe98,

    0,

    0,

    0,

};
