/* ov079 constructor argument block data_ov079_020b9924, 0x020b9924-0x020b9938 (.rodata).
 *
 * Five words handed to a class constructor: the resource path of the object's archive
 * ('ba/ch/ma/li_e2.p.z') and four parameters the constructor reads.  Used by func_ov079_020b8748.
 */

typedef struct ClassCtorArgs {
    const char *pszResource;  /* 0x00 */
    int aParam[4];            /* 0x04 */
} ClassCtorArgs;

extern char data_ov079_020b9940;  /* the path string */

const ClassCtorArgs data_ov079_020b9924 = {
    &data_ov079_020b9940,
    { 1, 0, 0, 0 },
};
