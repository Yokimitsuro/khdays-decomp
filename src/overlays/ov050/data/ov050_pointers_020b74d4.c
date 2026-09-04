/* ov050 .data pointer tables, 0x020b74d4-0x020b74fc.
 *
 * 2 tables, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

typedef void (*Ov_Fn)(void);

extern void func_ov022_020915bc(void);
extern void func_ov022_020916e0(void);
extern void func_ov022_0209183c(void);
extern void func_ov050_020b6e94(void);
extern void func_ov050_020b7020(void);
extern void func_ov050_020b7130(void);

Ov_Fn data_ov050_020b74d4[5] = {

    0,

    func_ov022_020915bc,

    func_ov050_020b6e94,

    func_ov022_020916e0,

    func_ov022_0209183c,

};

Ov_Fn data_ov050_020b74e8[5] = {

    0,

    func_ov022_020915bc,

    func_ov050_020b7020,

    func_ov022_020916e0,

    func_ov050_020b7130,

};
