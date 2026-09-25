/* ov077 constructor argument block data_ov077_020b9a6c, 0x020b9a6c-0x020b9a80 (.rodata).
 *
 * Five words handed to a class constructor: the resource path of the object's archive
 * ('ba/ch/le/li_e3.p.z') and four parameters the constructor reads.  Used by func_ov077_020b8700.
 */

typedef struct ClassCtorArgs {
    const char *pszResource;  /* 0x00 */
    int aParam[4];            /* 0x04 */
} ClassCtorArgs;

extern char data_ov077_020b9aa0;  /* the path string */

const ClassCtorArgs data_ov077_020b9a6c = {
    &data_ov077_020b9aa0,
    { 3, 0, 0, 0 },
};
