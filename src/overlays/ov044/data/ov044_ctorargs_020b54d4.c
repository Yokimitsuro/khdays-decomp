/* ov044 constructor argument block data_ov044_020b54d4, 0x020b54d4-0x020b54e8 (.rodata).
 *
 * Five words handed to a class constructor: the resource path of the object's archive
 * ('ba/ch/ro/li_e3.p.z') and four parameters the constructor reads.  Used by func_ov044_020b47d0.
 */

typedef struct ClassCtorArgs {
    const char *pszResource;  /* 0x00 */
    int aParam[4];            /* 0x04 */
} ClassCtorArgs;

extern char data_ov044_020b55b0;  /* the path string */

const ClassCtorArgs data_ov044_020b54d4 = {
    &data_ov044_020b55b0,
    { 3, 0, 0, 0 },
};
