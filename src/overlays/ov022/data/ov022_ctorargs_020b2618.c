/* ov022 constructor argument block data_ov022_020b2618, 0x020b2618-0x020b262c (.rodata).
 *
 * Five words handed to a class constructor: the resource path of the object's archive
 * ('ba/ef/appe.p.z') and four parameters the constructor reads.  Used by func_ov022_0209cac0.
 */

typedef struct ClassCtorArgs {
    const char *pszResource;  /* 0x00 */
    int aParam[4];            /* 0x04 */
} ClassCtorArgs;

extern char data_ov022_020b2c8c;  /* the path string */

const ClassCtorArgs data_ov022_020b2618 = {
    &data_ov022_020b2c8c,
    { 1, 0, 0, 5 },
};
