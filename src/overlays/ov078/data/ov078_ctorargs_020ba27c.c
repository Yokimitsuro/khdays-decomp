/* ov078 constructor argument block data_ov078_020ba27c, 0x020ba27c-0x020ba290 (.rodata).
 *
 * Five words handed to a class constructor: the resource path of the object's archive
 * ('ba/ch/lu/li_e1.p.z') and four parameters the constructor reads.  Used by func_ov078_020b8c10.
 */

typedef struct ClassCtorArgs {
    const char *pszResource;  /* 0x00 */
    int aParam[4];            /* 0x04 */
} ClassCtorArgs;

extern char data_ov078_020ba420;  /* the path string */

const ClassCtorArgs data_ov078_020ba27c = {
    &data_ov078_020ba420,
    { 2, 0, 0, 0 },
};
