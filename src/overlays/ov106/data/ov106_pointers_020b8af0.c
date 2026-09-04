/* ov106 .data pointer tables, 0x020b8af0-0x020b8b20.
 *
 * 1 table, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

typedef void (*Ov_Fn)(void);

extern void func_ov106_020b821c(void);
extern void func_ov106_020b823c(void);
extern void func_ov106_020b825c(void);
extern void func_ov106_020b82c8(void);
extern void func_ov106_020b833c(void);
extern void func_ov106_020b834c(void);
extern void func_ov106_020b8350(void);
extern void func_ov106_020b83c4(void);

Ov_Fn data_ov106_020b8af0[12] = {

    func_ov106_020b821c,

    0,

    func_ov106_020b823c,

    0,

    func_ov106_020b825c,

    func_ov106_020b82c8,

    func_ov106_020b833c,

    0,

    func_ov106_020b834c,

    func_ov106_020b8350,

    func_ov106_020b83c4,

    0,

};
