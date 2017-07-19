typedef struct
{
 char signature[12];
 unsigned char verhi:8;
 unsigned char verhi2:8;
 unsigned char verlo:8;
 unsigned char verlo2:8;
 unsigned long int pcx_offset:32;
 unsigned long int pcx_size:32;
 unsigned long int text_offset:32;
 unsigned long int text_size:32;
 char comment[40];
} FNT;