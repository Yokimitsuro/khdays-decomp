/* ov052 constructor argument block data_ov052_020b7f24, 0x020b7f24-0x020b7f38 (.rodata).
 *
 * Five words handed to a class constructor: the resource path of the object's archive
 * ('ba/ch/xi/li_e2.p.z') and four parameters the constructor reads.  Used by func_ov052_020b7194.
 */

typedef struct ClassCtorArgs {
    const char *pszResource;  /* 0x00 */
    int aParam[4];            /* 0x04 */
} ClassCtorArgs;

extern char data_ov052_020b7fe0;  /* the path string */

const ClassCtorArgs data_ov052_020b7f24 = {
    &data_ov052_020b7fe0,
    { 3, 0, 0, 0 },
};
