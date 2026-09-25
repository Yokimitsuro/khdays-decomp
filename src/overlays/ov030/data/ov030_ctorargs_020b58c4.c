/* ov030 constructor argument block data_ov030_020b58c4, 0x020b58c4-0x020b58d8 (.rodata).
 *
 * Five words handed to a class constructor: the resource path of the object's archive
 * ('ba/ch/ro/li_e3.p.z') and four parameters the constructor reads.  Used by func_ov030_020b4b9c.
 */

typedef struct ClassCtorArgs {
    const char *pszResource;  /* 0x00 */
    int aParam[4];            /* 0x04 */
} ClassCtorArgs;

extern char data_ov030_020b5984;  /* the path string */

const ClassCtorArgs data_ov030_020b58c4 = {
    &data_ov030_020b5984,
    { 3, 0, 0, 0 },
};
