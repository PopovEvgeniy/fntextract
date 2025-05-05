#pragma pack(push, 1)
typedef struct
{
 char signature[12];
 unsigned char version[4];
 unsigned long int pcx_offset:32;
 unsigned long int pcx_size:32;
 unsigned long int text_offset:32;
 unsigned long int text_size:32;
 char comment[40];
} FNT;
#pragma pack(pop)