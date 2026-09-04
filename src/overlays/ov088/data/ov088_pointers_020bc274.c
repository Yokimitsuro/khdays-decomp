/* ov088 .data pointer tables, 0x020bc274-0x020bc29c.
 *
 * 2 tables, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

typedef void (*Ov_Fn)(void);

extern void func_ov022_020915bc(void);
extern void func_ov022_020916e0(void);
extern void func_ov022_0209183c(void);
extern void func_ov088_020bbc34(void);
extern void func_ov088_020bbdc0(void);
extern void func_ov088_020bbed0(void);

Ov_Fn data_ov088_020bc274[5] = {

    0,

    func_ov022_020915bc,

    func_ov088_020bbc34,

    func_ov022_020916e0,

    func_ov022_0209183c,

};

Ov_Fn data_ov088_020bc288[5] = {

    0,

    func_ov022_020915bc,

    func_ov088_020bbdc0,

    func_ov022_020916e0,

    func_ov088_020bbed0,

};
