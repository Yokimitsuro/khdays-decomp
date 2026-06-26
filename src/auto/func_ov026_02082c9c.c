struct Box {
    unsigned char pad[0x1c];
    unsigned char x;
    unsigned char y;
    unsigned char w;
    unsigned char h;
};

int func_ov026_02082c9c(int px, int py, struct Box *b) {
    int r = 0;
    if (b->x <= px && px <= b->x + b->w && b->y <= py && py <= b->y + b->h) {
        r = 1;
    }
    return r;
}
