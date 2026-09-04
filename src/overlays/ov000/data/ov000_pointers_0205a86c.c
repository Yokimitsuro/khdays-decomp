/* ov000 .rodata pointer tables, 0x0205a86c-0x0205a884.
 *
 * 1 table, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

typedef void (*Ov_Fn)(void);

extern void func_ov000_02054170(void);
extern void func_ov000_020541fc(void);
extern void func_ov000_02054288(void);
extern void func_ov000_020544b0(void);
extern void func_ov000_02054640(void);
extern void func_ov000_02054644(void);

const Ov_Fn data_ov000_0205a86c[6] = {

    func_ov000_02054170,

    func_ov000_020541fc,

    func_ov000_02054288,

    func_ov000_020544b0,

    func_ov000_02054640,

    func_ov000_02054644,

};
