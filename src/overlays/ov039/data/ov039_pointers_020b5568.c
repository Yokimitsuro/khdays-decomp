/* ov039 .data pointer tables, 0x020b5568-0x020b557c.
 *
 * 1 table, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

typedef void (*Ov_Fn)(void);

extern void func_ov022_020915bc(void);
extern void func_ov022_020916e0(void);
extern void func_ov039_020b44e4(void);
extern void func_ov039_020b44fc(void);

Ov_Fn data_ov039_020b5568[5] = {

    0,

    func_ov022_020915bc,

    func_ov039_020b44e4,

    func_ov022_020916e0,

    func_ov039_020b44fc,

};
