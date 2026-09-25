/* ov091 constructor argument block data_ov091_020bc118, 0x020bc118-0x020bc12c (.rodata).
 *
 * Five words handed to a class constructor: the resource path of the object's archive
 * ('ba/ch/so/li_e1.p.z') and four parameters the constructor reads.  Used by func_ov091_020bafd0.
 */

typedef struct ClassCtorArgs {
    const char *pszResource;  /* 0x00 */
    int aParam[4];            /* 0x04 */
} ClassCtorArgs;

extern char data_ov091_020bc180;  /* the path string */

const ClassCtorArgs data_ov091_020bc118 = {
    &data_ov091_020bc180,
    { 1, 0, 0, 0 },
};
