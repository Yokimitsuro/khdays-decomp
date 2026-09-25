/* ov056 constructor argument block data_ov056_020b7510, 0x020b7510-0x020b7524 (.rodata).
 *
 * Five words handed to a class constructor: the resource path of the object's archive
 * ('ba/ch/la/li_e0.p.z') and four parameters the constructor reads.  Used by func_ov056_020b6398.
 */

typedef struct ClassCtorArgs {
    const char *pszResource;  /* 0x00 */
    int aParam[4];            /* 0x04 */
} ClassCtorArgs;

extern char data_ov056_020b7580;  /* the path string */

const ClassCtorArgs data_ov056_020b7510 = {
    &data_ov056_020b7580,
    { 3, 0, 0, 0 },
};
