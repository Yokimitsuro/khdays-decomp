/* ov022 constructor argument block data_ov022_020b2640, 0x020b2640-0x020b2654 (.rodata).
 *
 * Five words handed to a class constructor: the resource path of the object's archive
 * ('ba/ef/hx.p.z') and four parameters the constructor reads.  Used by func_ov022_0209cac0.
 */

typedef struct ClassCtorArgs {
    const char *pszResource;  /* 0x00 */
    int aParam[4];            /* 0x04 */
} ClassCtorArgs;

extern char data_ov022_020b2c6c;  /* the path string */

const ClassCtorArgs data_ov022_020b2640 = {
    &data_ov022_020b2c6c,
    { 6, 0, 0, 5 },
};
