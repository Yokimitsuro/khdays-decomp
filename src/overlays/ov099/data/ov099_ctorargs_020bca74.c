/* ov099 constructor argument block data_ov099_020bca74, 0x020bca74-0x020bca88 (.rodata).
 *
 * Five words handed to a class constructor: the resource path of the object's archive
 * ('ba/ch/ro/li_e3.p.z') and four parameters the constructor reads.  Used by func_ov099_020bbd70.
 */

typedef struct ClassCtorArgs {
    const char *pszResource;  /* 0x00 */
    int aParam[4];            /* 0x04 */
} ClassCtorArgs;

extern char data_ov099_020bcb50;  /* the path string */

const ClassCtorArgs data_ov099_020bca74 = {
    &data_ov099_020bcb50,
    { 3, 0, 0, 0 },
};
