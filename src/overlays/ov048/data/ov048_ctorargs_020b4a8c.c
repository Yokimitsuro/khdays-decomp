/* ov048 constructor argument block data_ov048_020b4a8c, 0x020b4a8c-0x020b4aa0 (.rodata).
 *
 * Five words handed to a class constructor: the resource path of the object's archive
 * ('ba/ch/go/li_e2.p.z') and four parameters the constructor reads.  Used by func_ov048_020b3934.
 */

typedef struct ClassCtorArgs {
    const char *pszResource;  /* 0x00 */
    int aParam[4];            /* 0x04 */
} ClassCtorArgs;

extern char data_ov048_020b4ac0;  /* the path string */

const ClassCtorArgs data_ov048_020b4a8c = {
    &data_ov048_020b4ac0,
    { 4, 0, 0, 0 },
};
