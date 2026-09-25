/* ov095 constructor argument block data_ov095_020bc93c, 0x020bc93c-0x020bc950 (.rodata).
 *
 * Five words handed to a class constructor: the resource path of the object's archive
 * ('ba/ch/lu/li_e1.p.z') and four parameters the constructor reads.  Used by func_ov095_020bb2d0.
 */

typedef struct ClassCtorArgs {
    const char *pszResource;  /* 0x00 */
    int aParam[4];            /* 0x04 */
} ClassCtorArgs;

extern char data_ov095_020bcae0;  /* the path string */

const ClassCtorArgs data_ov095_020bc93c = {
    &data_ov095_020bcae0,
    { 2, 0, 0, 0 },
};
