/* ov076 constructor argument block data_ov076_020b9bf0, 0x020b9bf0-0x020b9c04 (.rodata).
 *
 * Five words handed to a class constructor: the resource path of the object's archive
 * ('ba/ch/la/li_e0.p.z') and four parameters the constructor reads.  Used by func_ov076_020b8a78.
 */

typedef struct ClassCtorArgs {
    const char *pszResource;  /* 0x00 */
    int aParam[4];            /* 0x04 */
} ClassCtorArgs;

extern char data_ov076_020b9c60;  /* the path string */

const ClassCtorArgs data_ov076_020b9bf0 = {
    &data_ov076_020b9c60,
    { 3, 0, 0, 0 },
};
