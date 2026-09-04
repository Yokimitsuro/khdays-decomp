/* ov000 .rodata pointer tables, 0x0205a710-0x0205a734.
 *
 * 1 table, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

typedef void (*Ov_Fn)(void);

extern void func_ov000_0205223c(void);
extern void func_ov000_020522d0(void);
extern void func_ov000_02052374(void);
extern void func_ov000_020526fc(void);
extern void func_ov000_020529c4(void);
extern void func_ov000_02052c74(void);
extern void func_ov000_02052ef8(void);
extern void func_ov000_02052f78(void);
extern void func_ov000_02052fb8(void);

const Ov_Fn data_ov000_0205a710[9] = {

    func_ov000_0205223c,

    func_ov000_020522d0,

    func_ov000_02052374,

    func_ov000_020526fc,

    func_ov000_020529c4,

    func_ov000_02052c74,

    func_ov000_02052ef8,

    func_ov000_02052f78,

    func_ov000_02052fb8,

};
