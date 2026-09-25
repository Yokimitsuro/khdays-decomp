/* ov086 constructor argument block data_ov086_020b996c, 0x020b996c-0x020b9980 (.rodata).
 *
 * Five words handed to a class constructor: the resource path of the object's archive
 * ('ba/ch/go/li_e2.p.z') and four parameters the constructor reads.  Used by func_ov086_020b8814.
 */

typedef struct ClassCtorArgs {
    const char *pszResource;  /* 0x00 */
    int aParam[4];            /* 0x04 */
} ClassCtorArgs;

extern char data_ov086_020b99a0;  /* the path string */

const ClassCtorArgs data_ov086_020b996c = {
    &data_ov086_020b99a0,
    { 4, 0, 0, 0 },
};
