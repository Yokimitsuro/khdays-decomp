/* ov103 constructor argument block data_ov103_020bc02c, 0x020bc02c-0x020bc040 (.rodata).
 *
 * Five words handed to a class constructor: the resource path of the object's archive
 * ('ba/ch/go/li_e2.p.z') and four parameters the constructor reads.  Used by func_ov103_020baed4.
 */

typedef struct ClassCtorArgs {
    const char *pszResource;  /* 0x00 */
    int aParam[4];            /* 0x04 */
} ClassCtorArgs;

extern char data_ov103_020bc060;  /* the path string */

const ClassCtorArgs data_ov103_020bc02c = {
    &data_ov103_020bc060,
    { 4, 0, 0, 0 },
};
