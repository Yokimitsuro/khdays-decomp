/* ov004 .rodata pointer tables, 0x020510b8-0x020510cc.
 *
 * 1 table, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

typedef void (*Ov_Fn)(void);

extern void func_ov004_02050b04(void);
extern void func_ov004_02050c60(void);
extern void func_ov004_02050e44(void);
extern void func_ov004_02050f9c(void);
extern void func_ov004_02051008(void);

const Ov_Fn data_ov004_020510b8[5] = {

    func_ov004_02050b04,

    func_ov004_02050c60,

    func_ov004_02050e44,

    func_ov004_02050f9c,

    func_ov004_02051008,

};
