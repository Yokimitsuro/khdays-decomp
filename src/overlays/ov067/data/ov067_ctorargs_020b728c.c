/* ov067 constructor argument block data_ov067_020b728c, 0x020b728c-0x020b72a0 (.rodata).
 *
 * Five words handed to a class constructor: the resource path of the object's archive
 * ('ba/ch/go/li_e2.p.z') and four parameters the constructor reads.  Used by func_ov067_020b6134.
 */

typedef struct ClassCtorArgs {
    const char *pszResource;  /* 0x00 */
    int aParam[4];            /* 0x04 */
} ClassCtorArgs;

extern char data_ov067_020b72c0;  /* the path string */

const ClassCtorArgs data_ov067_020b728c = {
    &data_ov067_020b72c0,
    { 4, 0, 0, 0 },
};
