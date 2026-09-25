/* ov037 constructor argument block data_ov037_020b4d10, 0x020b4d10-0x020b4d24 (.rodata).
 *
 * Five words handed to a class constructor: the resource path of the object's archive
 * ('ba/ch/la/li_e0.p.z') and four parameters the constructor reads.  Used by func_ov037_020b3b98.
 */

typedef struct ClassCtorArgs {
    const char *pszResource;  /* 0x00 */
    int aParam[4];            /* 0x04 */
} ClassCtorArgs;

extern char data_ov037_020b4d80;  /* the path string */

const ClassCtorArgs data_ov037_020b4d10 = {
    &data_ov037_020b4d80,
    { 3, 0, 0, 0 },
};
