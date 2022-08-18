#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "format.h"

void show_intro();
void show_message(const char *message);
FILE *open_input_file(const char *name);
FILE *create_output_file(const char *name);
void go_offset(FILE *file,const unsigned long int offset);
unsigned long int get_file_size(FILE *file);
void data_dump(FILE *input,FILE *output,const size_t length);
void fast_data_dump(FILE *input,FILE *output,const size_t length);
void write_output_file(FILE *input,const char *name,const size_t length);
char *get_string_memory(const size_t length);
size_t get_extension_position(const char *source);
char *get_short_name(const char *name);
char* get_name(const char *name,const char *ext);
void check_signature(const char *signature);
FNT read_fnt_head(FILE *file);
void work(const char *fnt_file_name);

int main(int argc, char *argv[])
{
 show_intro();
 if (argc<2)
 {
  show_message("You must give a target file name as command line argument!");
 }
 else
 {
  show_message("Extracting a font data...");
  work(argv[1]);
  show_message("Work finish");
 }
 return 0;
}

void show_intro()
{
 putchar('\n');
 puts("FNT EXTRACT");
 puts("Version 2.3");
 puts("Mugen font decompiler by Popov Evgeniy Alekseyevich, 2008-2022 years");
 puts("This program distributed under GNU GENERAL PUBLIC LICENSE");
}

void show_message(const char *message)
{
 putchar('\n');
 puts(message);
}

FILE *open_input_file(const char *name)
{
 FILE *target;
 target=fopen(name,"rb");
 if (target==NULL)
 {
  putchar('\n');
  puts("Can't open input file");
  exit(1);
 }
 return target;
}

FILE *create_output_file(const char *name)
{
 FILE *target;
 target=fopen(name,"wb");
 if (target==NULL)
 {
  putchar('\n');
  puts("Can't create ouput file");
  exit(2);
 }
 return target;
}

void go_offset(FILE *file,const unsigned long int offset)
{
 if (fseek(file,offset,SEEK_SET)!=0)
 {
  putchar('\n');
  puts("Can't jump to target offset");
  exit(3);
 }

}

unsigned long int get_file_size(FILE *file)
{
 unsigned long int length;
 fseek(file,0,SEEK_END);
 length=ftell(file);
 rewind(file);
 return length;
}

void data_dump(FILE *input,FILE *output,const size_t length)
{
 unsigned char data;
 size_t index;
 data=0;
 for (index=0;index<length;++index)
 {
  fread(&data,sizeof(unsigned char),1,input);
  fwrite(&data,sizeof(unsigned char),1,output);
 }

}

void fast_data_dump(FILE *input,FILE *output,const size_t length)
{
 unsigned char *buffer=NULL;
 buffer=(unsigned char*)calloc(length,sizeof(unsigned char));
 if (buffer==NULL)
 {
  data_dump(input,output,length);
 }
 else
 {
  fread(buffer,sizeof(unsigned char),length,input);
  fwrite(buffer,sizeof(unsigned char),length,output);
  free(buffer);
 }

}

void write_output_file(FILE *input,const char *name,const size_t length)
{
 FILE *output;
 output=create_output_file(name);
 fast_data_dump(input,output,length);
 fclose(output);
}

char *get_string_memory(const size_t length)
{
 char *memory=NULL;
 memory=(char*)calloc(length+1,sizeof(char));
 if(memory==NULL)
 {
  putchar('\n');
  puts("Can't allocate memory");
  exit(4);
 }
 return memory;
}

size_t get_extension_position(const char *source)
{
 size_t index;
 for(index=strlen(source);index>0;--index)
 {
  if(source[index]=='.')
  {
   break;
  }

 }
 if (index==0) index=strlen(source);
 return index;
}

char *get_short_name(const char *name)
{
 size_t length;
 char *result=NULL;
 length=get_extension_position(name);
 result=get_string_memory(length);
 strncpy(result,name,length);
 return result;
}

char* get_name(const char *name,const char *ext)
{
  char *result=NULL;
  size_t length;
  length=strlen(name)+strlen(ext);
  result=get_string_memory(length);
  strcpy(result,name);
  return strcat(result,ext);
}

void check_signature(const char *signature)
{
 if (strcmp(signature,"ElecbyteFnt")!=0)
 {
  putchar('\n');
  puts("Bad signature of a font file");
  exit(5);
 }

}

FNT read_fnt_head(FILE *file)
{
 FNT fnt;
 fread(&fnt,sizeof(FNT),1,file);
 check_signature(fnt.signature);
 return fnt;
}

void work(const char *fnt_file_name)
{
 FILE *fnt_file;
 char *output_file_name;
 char *short_name=NULL;
 FNT fnt;
 fnt_file=open_input_file(fnt_file_name);
 fnt=read_fnt_head(fnt_file);
 go_offset(fnt_file,fnt.pcx_offset);
 short_name=get_short_name(fnt_file_name);
 output_file_name=get_name(short_name,".pcx");
 write_output_file(fnt_file,output_file_name,(size_t)fnt.pcx_size);
 free(output_file_name);
 output_file_name=get_name(short_name,".txt");
 go_offset(fnt_file,fnt.text_offset);
 write_output_file(fnt_file,output_file_name,(size_t)fnt.text_size);
 free(output_file_name);
 free(short_name);
}