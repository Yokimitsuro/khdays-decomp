/* ov072 constructor argument block data_ov072_020ba604, 0x020ba604-0x020ba618 (.rodata).
 *
 * Five words handed to a class constructor: the resource path of the object's archive
 * ('ba/ch/xi/li_e2.p.z') and four parameters the constructor reads.  Used by func_ov072_020b9874.
 */

typedef struct ClassCtorArgs {
    const char *pszResource;  /* 0x00 */
    int aParam[4];            /* 0x04 */
} ClassCtorArgs;

extern char data_ov072_020ba6c0;  /* the path string */

const ClassCtorArgs data_ov072_020ba604 = {
    &data_ov072_020ba6c0,
    { 3, 0, 0, 0 },
};
