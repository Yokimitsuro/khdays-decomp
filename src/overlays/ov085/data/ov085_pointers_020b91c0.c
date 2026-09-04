/* ov085 .data pointer tables, 0x020b91c0-0x020b91d4.
 *
 * 1 table, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

typedef void (*Ov_Fn)(void);

extern void func_ov022_020915bc(void);
extern void func_ov022_020916e0(void);
extern void func_ov022_0209183c(void);
extern void func_ov085_020b8adc(void);

Ov_Fn data_ov085_020b91c0[5] = {

    0,

    func_ov022_020915bc,

    func_ov085_020b8adc,

    func_ov022_020916e0,

    func_ov022_0209183c,

};
