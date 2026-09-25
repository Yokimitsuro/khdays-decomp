/* ov035 constructor argument block data_ov035_020b4b78, 0x020b4b78-0x020b4b8c (.rodata).
 *
 * Five words handed to a class constructor: the resource path of the object's archive
 * ('ba/ch/so/li_e1.p.z') and four parameters the constructor reads.  Used by func_ov035_020b3a30.
 */

typedef struct ClassCtorArgs {
    const char *pszResource;  /* 0x00 */
    int aParam[4];            /* 0x04 */
} ClassCtorArgs;

extern char data_ov035_020b4be0;  /* the path string */

const ClassCtorArgs data_ov035_020b4b78 = {
    &data_ov035_020b4be0,
    { 1, 0, 0, 0 },
};
