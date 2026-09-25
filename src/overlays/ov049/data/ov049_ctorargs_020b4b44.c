/* ov049 constructor argument block data_ov049_020b4b44, 0x020b4b44-0x020b4b58 (.rodata).
 *
 * Five words handed to a class constructor: the resource path of the object's archive
 * ('ba/ch/r2/li_e2.p.z') and four parameters the constructor reads.  Used by func_ov049_020b3a5c.
 */

typedef struct ClassCtorArgs {
    const char *pszResource;  /* 0x00 */
    int aParam[4];            /* 0x04 */
} ClassCtorArgs;

extern char data_ov049_020b4c20;  /* the path string */

const ClassCtorArgs data_ov049_020b4b44 = {
    &data_ov049_020b4c20,
    { 4, 0, 0, 0 },
};
