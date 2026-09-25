/* ov040 constructor argument block data_ov040_020b4a44, 0x020b4a44-0x020b4a58 (.rodata).
 *
 * Five words handed to a class constructor: the resource path of the object's archive
 * ('ba/ch/ma/li_e2.p.z') and four parameters the constructor reads.  Used by func_ov040_020b3868.
 */

typedef struct ClassCtorArgs {
    const char *pszResource;  /* 0x00 */
    int aParam[4];            /* 0x04 */
} ClassCtorArgs;

extern char data_ov040_020b4a60;  /* the path string */

const ClassCtorArgs data_ov040_020b4a44 = {
    &data_ov040_020b4a60,
    { 1, 0, 0, 0 },
};
