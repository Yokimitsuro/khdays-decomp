/* ov087 constructor argument block data_ov087_020b9a24, 0x020b9a24-0x020b9a38 (.rodata).
 *
 * Five words handed to a class constructor: the resource path of the object's archive
 * ('ba/ch/r2/li_e2.p.z') and four parameters the constructor reads.  Used by func_ov087_020b893c.
 */

typedef struct ClassCtorArgs {
    const char *pszResource;  /* 0x00 */
    int aParam[4];            /* 0x04 */
} ClassCtorArgs;

extern char data_ov087_020b9b00;  /* the path string */

const ClassCtorArgs data_ov087_020b9a24 = {
    &data_ov087_020b9b00,
    { 4, 0, 0, 0 },
};
