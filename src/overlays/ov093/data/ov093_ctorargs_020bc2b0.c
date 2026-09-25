/* ov093 constructor argument block data_ov093_020bc2b0, 0x020bc2b0-0x020bc2c4 (.rodata).
 *
 * Five words handed to a class constructor: the resource path of the object's archive
 * ('ba/ch/la/li_e0.p.z') and four parameters the constructor reads.  Used by func_ov093_020bb138.
 */

typedef struct ClassCtorArgs {
    const char *pszResource;  /* 0x00 */
    int aParam[4];            /* 0x04 */
} ClassCtorArgs;

extern char data_ov093_020bc320;  /* the path string */

const ClassCtorArgs data_ov093_020bc2b0 = {
    &data_ov093_020bc320,
    { 3, 0, 0, 0 },
};
