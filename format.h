typedef struct
{
 char signature[12];
 unsigned char version[4];
 unsigned int pcx_offset;
 unsigned int pcx_size;
 unsigned int text_offset;
 unsigned int text_size;
 char comment[40];
} FNT;