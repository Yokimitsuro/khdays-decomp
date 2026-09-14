/* Seven resource names and their tag IDs. */
typedef unsigned char u8;

extern char data_ov002_0207f07c;
extern char data_ov002_0207f09c;
extern char data_ov002_0207f070;
extern char data_ov002_0207f084;
extern char data_ov002_0207f08c;
extern char data_ov002_0207f074;
extern char data_ov002_0207f094;

typedef struct {
    const char *name;
    u8 tag;
    u8 pad[3];
} Ov002SurfaceTag;

const Ov002SurfaceTag data_ov002_0207e640[7] = {
    { &data_ov002_0207f07c, 2, {0} },
    { &data_ov002_0207f09c, 3, {0} },
    { &data_ov002_0207f070, 4, {0} },
    { &data_ov002_0207f084, 5, {0} },
    { &data_ov002_0207f08c, 6, {0} },
    { &data_ov002_0207f074, 7, {0} },
    { &data_ov002_0207f094, 8, {0} },
};
