/* ov082 constructor argument block data_ov082_020ba3b4, 0x020ba3b4-0x020ba3c8 (.rodata).
 *
 * Five words handed to a class constructor: the resource path of the object's archive
 * ('ba/ch/ro/li_e3.p.z') and four parameters the constructor reads.  Used by func_ov082_020b96b0.
 */

typedef struct ClassCtorArgs {
    const char *pszResource;  /* 0x00 */
    int aParam[4];            /* 0x04 */
} ClassCtorArgs;

extern char data_ov082_020ba490;  /* the path string */

const ClassCtorArgs data_ov082_020ba3b4 = {
    &data_ov082_020ba490,
    { 3, 0, 0, 0 },
};
