/* main .data pointer tables, 0x02042494-0x020424b4.
 *
 * 8 tables, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

typedef void (*Ov_Fn)(void);

extern void func_02015d14(void);
extern void func_02015df0(void);
extern void func_020161dc(void);
extern void func_020172a0(void);
extern void func_020189f0(void);
extern void func_02018ec0(void);
extern void func_02019120(void);
extern void func_020191e0(void);

Ov_Fn data_02042494[1] = {

    func_020191e0,

};

Ov_Fn data_02042498[1] = {

    func_020172a0,

};

Ov_Fn data_0204249c[1] = {

    func_02018ec0,

};

Ov_Fn data_020424a0[1] = {

    func_02019120,

};

Ov_Fn data_020424a4[1] = {

    func_020189f0,

};

Ov_Fn data_020424a8[1] = {

    func_020161dc,

};

Ov_Fn data_020424ac[1] = {

    func_02015df0,

};

Ov_Fn data_020424b0[1] = {

    func_02015d14,

};
