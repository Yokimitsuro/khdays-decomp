/* ov038 constructor argument block data_ov038_020b4b8c, 0x020b4b8c-0x020b4ba0 (.rodata).
 *
 * Five words handed to a class constructor: the resource path of the object's archive
 * ('ba/ch/le/li_e3.p.z') and four parameters the constructor reads.  Used by func_ov038_020b3820.
 */

typedef struct ClassCtorArgs {
    const char *pszResource;  /* 0x00 */
    int aParam[4];            /* 0x04 */
} ClassCtorArgs;

extern char data_ov038_020b4bc0;  /* the path string */

const ClassCtorArgs data_ov038_020b4b8c = {
    &data_ov038_020b4bc0,
    { 3, 0, 0, 0 },
};
