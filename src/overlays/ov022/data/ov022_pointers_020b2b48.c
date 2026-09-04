/* ov022 .data pointer tables, 0x020b2b48-0x020b2b6c.
 *
 * 2 tables, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

typedef void (*Ov_Fn)(void);

extern void func_ov022_020915bc(void);
extern void func_ov022_020915fc(void);
extern void func_ov022_020916e0(void);
extern void func_ov022_020916e8(void);
extern void func_ov022_0209183c(void);

Ov_Fn data_ov022_020b2b48[4] = {

    0,

    func_ov022_020915bc,

    func_ov022_020915fc,

    func_ov022_020916e0,

};

Ov_Fn data_ov022_020b2b58[5] = {

    0,

    func_ov022_020915bc,

    func_ov022_020916e8,

    func_ov022_020916e0,

    func_ov022_0209183c,

};
