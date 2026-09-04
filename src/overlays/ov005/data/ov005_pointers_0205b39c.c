/* ov005 .rodata pointer tables, 0x0205b39c-0x0205b3bc.
 *
 * 2 tables, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

extern void func_ov005_02057270(void);
extern void func_ov005_020573e8(void);
extern void func_ov005_020576c8(void);
extern void func_ov005_02057704(void);
extern void func_ov005_02057784(void);
extern int data_ov005_0205b60c;

void *const data_ov005_0205b39c[5] = {

    (void *)func_ov005_02057270,

    (void *)func_ov005_020573e8,

    (void *)func_ov005_020576c8,

    (void *)func_ov005_02057704,

    (void *)func_ov005_02057784,

};

void *const data_ov005_0205b3b0[3] = {

    &data_ov005_0205b60c,

    0,

    0,

};
