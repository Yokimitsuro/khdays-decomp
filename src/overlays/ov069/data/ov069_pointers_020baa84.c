/* ov069 .data pointer tables, 0x020baa84-0x020baab4.
 *
 * 1 table, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

typedef void (*Ov_Fn)(void);

extern void func_ov069_020b84dc(void);
extern void func_ov069_020b8518(void);
extern void func_ov069_020b8548(void);
extern void func_ov069_020b8604(void);
extern void func_ov069_020b8698(void);
extern void func_ov069_020b86e4(void);

Ov_Fn data_ov069_020baa84[12] = {

    func_ov069_020b84dc,

    0,

    func_ov069_020b8518,

    0,

    func_ov069_020b8548,

    0,

    func_ov069_020b8604,

    0,

    func_ov069_020b8698,

    0,

    func_ov069_020b86e4,

    0,

};
