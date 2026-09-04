/* ov011 .data pointer tables, 0x0205e8b4-0x0205e8e4.
 *
 * 2 tables, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

typedef void (*Ov_Fn)(void);

extern void func_ov011_0205c370(void);
extern void func_ov011_0205c3a0(void);
extern void func_ov011_0205c5e0(void);
extern void func_ov011_0205c5e4(void);

Ov_Fn data_ov011_0205e8b4[6] = {

    func_ov011_0205c370,

    func_ov011_0205c3a0,

    func_ov011_0205c370,

    func_ov011_0205c370,

    func_ov011_0205c5e4,

    func_ov011_0205c5e0,

};

Ov_Fn data_ov011_0205e8cc[6] = {

    func_ov011_0205c370,

    func_ov011_0205c3a0,

    func_ov011_0205c370,

    func_ov011_0205c370,

    func_ov011_0205c5e4,

    func_ov011_0205c5e0,

};
