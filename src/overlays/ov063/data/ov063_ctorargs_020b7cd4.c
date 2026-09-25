/* ov063 constructor argument block data_ov063_020b7cd4, 0x020b7cd4-0x020b7ce8 (.rodata).
 *
 * Five words handed to a class constructor: the resource path of the object's archive
 * ('ba/ch/ro/li_e3.p.z') and four parameters the constructor reads.  Used by func_ov063_020b6fd0.
 */

typedef struct ClassCtorArgs {
    const char *pszResource;  /* 0x00 */
    int aParam[4];            /* 0x04 */
} ClassCtorArgs;

extern char data_ov063_020b7db0;  /* the path string */

const ClassCtorArgs data_ov063_020b7cd4 = {
    &data_ov063_020b7db0,
    { 3, 0, 0, 0 },
};
