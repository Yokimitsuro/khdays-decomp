/* ov015 .data pointer tables, 0x02082904-0x02082960.
 *
 * 1 table, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

typedef void (*Ov_Fn)(void);

extern void func_ov015_020822b0(void);
extern void func_ov015_02082380(void);
extern void func_ov015_02082474(void);
extern void func_ov015_020824a0(void);
extern void func_ov015_02082574(void);
extern void func_ov015_02082740(void);
extern void func_ov015_020827a0(void);
extern void func_ov015_02082838(void);

Ov_Fn data_ov015_02082904[23] = {

    func_ov015_020822b0,

    0,

    func_ov015_02082380,

    0,

    func_ov015_02082474,

    0,

    func_ov015_020824a0,

    0,

    func_ov015_02082574,

    0,

    func_ov015_02082740,

    0,

    func_ov015_020827a0,

    0,

    func_ov015_02082838,

    0,

    0,

    0,

    0,

    0,

    0,

    0,

    0,

};
