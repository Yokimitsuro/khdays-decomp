/* ov016 .data pointer tables, 0x020826e0-0x02082740.
 *
 * 1 table, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

typedef void (*Ov_Fn)(void);

extern void func_ov016_02080fa4(void);
extern void func_ov016_02080ffc(void);
extern void func_ov016_02081108(void);
extern void func_ov016_02081144(void);
extern void func_ov016_02081200(void);
extern void func_ov016_020812a4(void);
extern void func_ov016_02081360(void);
extern void func_ov016_020813e8(void);
extern void func_ov016_020814b0(void);
extern void func_ov016_02081550(void);

Ov_Fn data_ov016_020826e0[24] = {

    0,

    0,

    0,

    0,

    func_ov016_02080fa4,

    0,

    func_ov016_02080ffc,

    0,

    func_ov016_02081108,

    0,

    func_ov016_02081144,

    0,

    func_ov016_02081200,

    0,

    func_ov016_020812a4,

    0,

    func_ov016_02081360,

    0,

    func_ov016_020813e8,

    0,

    func_ov016_020814b0,

    0,

    func_ov016_02081550,

    0,

};
