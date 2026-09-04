/* main .data pointer tables, 0x02042504-0x0204252c.
 *
 * 3 tables, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

typedef void (*Ov_Fn)(void);

extern void func_01ffa13c(void);
extern void func_01ffa1b8(void);
extern void func_01ffa218(void);
extern void func_01ffa2dc(void);
extern void func_01ffa450(void);
extern void func_01ffa5dc(void);

Ov_Fn data_02042504[3] = {

    func_01ffa13c,

    func_01ffa218,

    0,

};

Ov_Fn data_02042510[3] = {

    func_01ffa1b8,

    func_01ffa2dc,

    0,

};

Ov_Fn data_0204251c[4] = {

    func_01ffa450,

    0,

    func_01ffa5dc,

    0,

};
