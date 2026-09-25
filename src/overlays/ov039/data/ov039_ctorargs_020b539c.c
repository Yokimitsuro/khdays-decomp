/* ov039 constructor argument block data_ov039_020b539c, 0x020b539c-0x020b53b0 (.rodata).
 *
 * Five words handed to a class constructor: the resource path of the object's archive
 * ('ba/ch/lu/li_e1.p.z') and four parameters the constructor reads.  Used by func_ov039_020b3d30.
 */

typedef struct ClassCtorArgs {
    const char *pszResource;  /* 0x00 */
    int aParam[4];            /* 0x04 */
} ClassCtorArgs;

extern char data_ov039_020b5540;  /* the path string */

const ClassCtorArgs data_ov039_020b539c = {
    &data_ov039_020b5540,
    { 2, 0, 0, 0 },
};
