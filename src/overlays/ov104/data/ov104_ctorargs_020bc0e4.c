/* ov104 constructor argument block data_ov104_020bc0e4, 0x020bc0e4-0x020bc0f8 (.rodata).
 *
 * Five words handed to a class constructor: the resource path of the object's archive
 * ('ba/ch/r2/li_e2.p.z') and four parameters the constructor reads.  Used by func_ov104_020baffc.
 */

typedef struct ClassCtorArgs {
    const char *pszResource;  /* 0x00 */
    int aParam[4];            /* 0x04 */
} ClassCtorArgs;

extern char data_ov104_020bc1c0;  /* the path string */

const ClassCtorArgs data_ov104_020bc0e4 = {
    &data_ov104_020bc1c0,
    { 4, 0, 0, 0 },
};
