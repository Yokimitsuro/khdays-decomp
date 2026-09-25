/* ov030 constructor argument block data_ov030_020b58b0, 0x020b58b0-0x020b58c4 (.rodata).
 *
 * Five words handed to a class constructor: the resource path of the object's archive
 * ('ba/ch/ro/w_d00.p.z') and four parameters the constructor reads.  Used by func_ov030_020b3234.
 */

typedef struct ClassCtorArgs {
    const char *pszResource;  /* 0x00 */
    int aParam[4];            /* 0x04 */
} ClassCtorArgs;

extern char data_ov030_020b58e0;  /* the path string */

const ClassCtorArgs data_ov030_020b58b0 = {
    &data_ov030_020b58e0,
    { 2, 0, 0, 7 },
};
