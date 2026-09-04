/* ov014 .data pointer tables, 0x020808e0-0x02080920.
 *
 * 1 table, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

typedef void (*Ov_Fn)(void);

extern void func_ov014_02080664(void);
extern void func_ov014_02080718(void);
extern void func_ov014_020807c4(void);
extern void func_ov014_02080828(void);

Ov_Fn data_ov014_020808e0[16] = {

    func_ov014_02080664,

    0,

    func_ov014_02080718,

    0,

    0,

    0,

    0,

    0,

    func_ov014_020807c4,

    0,

    func_ov014_02080828,

    0,

    0,

    0,

    0,

    0,

};
