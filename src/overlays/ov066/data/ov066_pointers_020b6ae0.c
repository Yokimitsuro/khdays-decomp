/* ov066 .data pointer tables, 0x020b6ae0-0x020b6af4.
 *
 * 1 table, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

typedef void (*Ov_Fn)(void);

extern void func_ov022_020915bc(void);
extern void func_ov022_020916e0(void);
extern void func_ov022_0209183c(void);
extern void func_ov066_020b63fc(void);

Ov_Fn data_ov066_020b6ae0[5] = {

    0,

    func_ov022_020915bc,

    func_ov066_020b63fc,

    func_ov022_020916e0,

    func_ov022_0209183c,

};
