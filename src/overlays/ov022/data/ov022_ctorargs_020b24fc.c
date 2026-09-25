/* ov022 constructor argument block data_ov022_020b24fc, 0x020b24fc-0x020b2510 (.rodata).
 *
 * Five words handed to a class constructor: the resource path of the object's archive
 * ('/ba/ef/sh.p.z') and four parameters the constructor reads.  Used by func_ov022_02092e8c.
 */

typedef struct ClassCtorArgs {
    const char *pszResource;  /* 0x00 */
    int aParam[4];            /* 0x04 */
} ClassCtorArgs;

extern char data_ov022_020b2bbc;  /* the path string */

const ClassCtorArgs data_ov022_020b24fc = {
    &data_ov022_020b2bbc,
    { 5, 0, 0, 0 },
};
