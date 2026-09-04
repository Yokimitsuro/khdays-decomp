/* ov016 .data pointer tables, 0x02082748-0x0208274c.
 *
 * 1 table, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

typedef void (*Ov_Fn)(void);

extern void func_ov016_02081d2c(void);

Ov_Fn data_ov016_02082748[1] = {

    func_ov016_02081d2c,

};
