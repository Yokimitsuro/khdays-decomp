/* ov031 .data pointer tables, 0x020b4cd4-0x020b4cfc.
 *
 * 2 tables, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

typedef void (*Ov_Fn)(void);

extern void func_ov022_020915bc(void);
extern void func_ov022_020916e0(void);
extern void func_ov022_0209183c(void);
extern void func_ov031_020b4694(void);
extern void func_ov031_020b4820(void);
extern void func_ov031_020b4930(void);

Ov_Fn data_ov031_020b4cd4[5] = {

    0,

    func_ov022_020915bc,

    func_ov031_020b4694,

    func_ov022_020916e0,

    func_ov022_0209183c,

};

Ov_Fn data_ov031_020b4ce8[5] = {

    0,

    func_ov022_020915bc,

    func_ov031_020b4820,

    func_ov022_020916e0,

    func_ov031_020b4930,

};
