/* ov070 .data pointer tables, 0x020b9bb4-0x020b9bdc.
 *
 * 2 tables, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

typedef void (*Ov_Fn)(void);

extern void func_ov022_020915bc(void);
extern void func_ov022_020916e0(void);
extern void func_ov022_0209183c(void);
extern void func_ov070_020b9574(void);
extern void func_ov070_020b9700(void);
extern void func_ov070_020b9810(void);

Ov_Fn data_ov070_020b9bb4[5] = {

    0,

    func_ov022_020915bc,

    func_ov070_020b9574,

    func_ov022_020916e0,

    func_ov022_0209183c,

};

Ov_Fn data_ov070_020b9bc8[5] = {

    0,

    func_ov022_020915bc,

    func_ov070_020b9700,

    func_ov022_020916e0,

    func_ov070_020b9810,

};
