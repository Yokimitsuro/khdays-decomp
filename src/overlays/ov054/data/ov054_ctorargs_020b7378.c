/* ov054 constructor argument block data_ov054_020b7378, 0x020b7378-0x020b738c (.rodata).
 *
 * Five words handed to a class constructor: the resource path of the object's archive
 * ('ba/ch/so/li_e1.p.z') and four parameters the constructor reads.  Used by func_ov054_020b6230.
 */

typedef struct ClassCtorArgs {
    const char *pszResource;  /* 0x00 */
    int aParam[4];            /* 0x04 */
} ClassCtorArgs;

extern char data_ov054_020b73e0;  /* the path string */

const ClassCtorArgs data_ov054_020b7378 = {
    &data_ov054_020b73e0,
    { 1, 0, 0, 0 },
};
