/* ov094 constructor argument block data_ov094_020bc12c, 0x020bc12c-0x020bc140 (.rodata).
 *
 * Five words handed to a class constructor: the resource path of the object's archive
 * ('ba/ch/le/li_e3.p.z') and four parameters the constructor reads.  Used by func_ov094_020badc0.
 */

typedef struct ClassCtorArgs {
    const char *pszResource;  /* 0x00 */
    int aParam[4];            /* 0x04 */
} ClassCtorArgs;

extern char data_ov094_020bc160;  /* the path string */

const ClassCtorArgs data_ov094_020bc12c = {
    &data_ov094_020bc160,
    { 3, 0, 0, 0 },
};
