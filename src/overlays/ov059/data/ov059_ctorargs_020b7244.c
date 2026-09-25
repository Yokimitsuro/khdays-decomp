/* ov059 constructor argument block data_ov059_020b7244, 0x020b7244-0x020b7258 (.rodata).
 *
 * Five words handed to a class constructor: the resource path of the object's archive
 * ('ba/ch/ma/li_e2.p.z') and four parameters the constructor reads.  Used by func_ov059_020b6068.
 */

typedef struct ClassCtorArgs {
    const char *pszResource;  /* 0x00 */
    int aParam[4];            /* 0x04 */
} ClassCtorArgs;

extern char data_ov059_020b7260;  /* the path string */

const ClassCtorArgs data_ov059_020b7244 = {
    &data_ov059_020b7260,
    { 1, 0, 0, 0 },
};
