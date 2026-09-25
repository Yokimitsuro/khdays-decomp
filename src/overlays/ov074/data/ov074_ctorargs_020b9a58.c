/* ov074 constructor argument block data_ov074_020b9a58, 0x020b9a58-0x020b9a6c (.rodata).
 *
 * Five words handed to a class constructor: the resource path of the object's archive
 * ('ba/ch/so/li_e1.p.z') and four parameters the constructor reads.  Used by func_ov074_020b8910.
 */

typedef struct ClassCtorArgs {
    const char *pszResource;  /* 0x00 */
    int aParam[4];            /* 0x04 */
} ClassCtorArgs;

extern char data_ov074_020b9ac0;  /* the path string */

const ClassCtorArgs data_ov074_020b9a58 = {
    &data_ov074_020b9ac0,
    { 1, 0, 0, 0 },
};
