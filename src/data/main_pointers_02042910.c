/* main .data pointer tables, 0x02042910-0x02042958.
 *
 * 3 tables, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

typedef void (*Ov_Fn)(void);

extern void func_01fff0e0(void);
extern void func_01fff290(void);
extern void func_01fff554(void);
extern void func_02029444(void);
extern void func_0202947c(void);
extern void func_02029480(void);
extern void func_020294b0(void);
extern void func_0202951c(void);
extern void func_02029520(void);
extern void func_0202958c(void);
extern void func_0202980c(void);
extern void func_02029810(void);
extern void func_02029a7c(void);
extern void func_02029f3c(void);

Ov_Fn data_02042910[6] = {

    func_02029444,

    func_0202951c,

    func_01fff554,

    func_01fff290,

    func_02029520,

    func_020294b0,

};

Ov_Fn data_02042928[6] = {

    func_0202958c,

    func_0202980c,

    func_02029810,

    func_02029a7c,

    func_02029480,

    func_02029f3c,

};

Ov_Fn data_02042940[6] = {

    func_02029444,

    func_0202947c,

    func_01fff0e0,

    func_01fff290,

    func_02029480,

    func_020294b0,

};
