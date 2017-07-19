#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "format.h"

void show_end_message();
void show_intro();
void show_start_message();
void command_line_help();
FILE *open_input_file(char *name);
FILE *create_output_file(char *name);
void go_offset(FILE *file, unsigned long int offset);
unsigned long int get_file_size(FILE *file);
void data_dump(FILE *input, FILE *output, unsigned long int length);
void write_output_file(FILE *input, char *name, unsigned long int length);
char *get_string_memory(unsigned long int length);
unsigned long int get_extension_position(char *source);
char *get_short_name(char *name);
char* get_name(char *name, char *ext);
FNT read_fnt_head(FILE *file);
void work(char *fnt_file_name);

int main(int argc, char *argv[])
{
 show_intro();
 if (argc<2)
 {
  command_line_help();
 }
 else
 {
  work(argv[1]);
 }
 return 0;
}

void show_end_message()
{
 puts(" ");
 puts("Work finish");
}

void show_intro()
{
 puts(" ");
 puts("FNT EXTRACT");
 puts("Version 2.1.9");
 puts("Mugen font decompiler by Popov Evgeniy Alekseyevich, 2008-2016 year");
 puts("This program distributed under GNU GENERAL PUBLIC LICENSE");
}

void show_start_message()
{
 puts(" ");
 puts("Extracting a font data...");
}

void command_line_help()
{
 puts(" ");
 puts("You must give a target file name as command line argument!");
}

FILE *open_input_file(char *name)
{
 FILE *file;
 file=fopen(name,"rb");
 if (file==NULL)
 {
  puts(" ");
  puts("File operation error");
  exit(2);
 }
 return file;
}

FILE *create_output_file(char *name)
{
 FILE *file;
 file=fopen(name,"wb");
 if (file==NULL)
 {
  puts(" ");
  puts("File operation error");
  exit(2);
 }
 return file;
}

void go_offset(FILE *file, unsigned long int offset)
{
 fseek(file,offset,SEEK_SET);
}

unsigned long int get_file_size(FILE *file)
{
 unsigned long int length;
 fseek(file,0,SEEK_END);
 length=ftell(file);
 rewind(file);
 return length;
}

void data_dump(FILE *input, FILE *output, unsigned long int length)
{
 unsigned char single_byte;
 unsigned long int index;
 unsigned char *buffer=NULL;
 buffer=(unsigned char*)calloc(length,1);
 if (buffer==NULL)
 {
  for(index=0;index<length;index++)
  {
   fread(&single_byte,1,1,input);
   fwrite(&single_byte,1,1,output);
  }

 }
 else
 {
  fread(buffer,length,1,input);
  fwrite(buffer,length,1,output);
  free(buffer);
 }

}

void write_output_file(FILE *input, char *name, unsigned long int length)
{
 FILE *output;
 output=create_output_file(name);
 data_dump(input,output,length);
 fclose(output);
}

char *get_string_memory(unsigned long int length)
{
 char *memory=NULL;
 memory=(char*)calloc(length+1,1);
 if(memory==NULL)
 {
  puts(" ");
  puts("Can't allocate memory");
  exit(1);
 }
 return memory;
}

unsigned long int get_extension_position(char *source)
{
 unsigned long int index;
 for(index=strlen(source);index>0;index--)
 {
  if(source[index]=='.')
  {
   break;
  }

 }
 if (index==0) index=strlen(source);
 return index;
}

char *get_short_name(char *name)
{
 unsigned long int length;
 char *result=NULL;
 length=get_extension_position(name);
 result=get_string_memory(length);
 strncpy(result,name,length);
 return result;
}

char* get_name(char *name, char *ext)
{
  char *result=NULL;
  unsigned short int length;
  length=strlen(name)+strlen(ext);
  result=get_string_memory(length);
  strcpy(result,name);
  return strcat(result,ext);
}

FNT read_fnt_head(FILE *file)
{
 FNT fnt;
 fread(&fnt,sizeof(FNT),1,file);
 if (strcmp(fnt.signature,"ElecbyteFnt")!=0)
 {
  puts(" ");
  puts("Bad signature of a font file");
  exit(3);
 }
 return fnt;
}

void work(char *fnt_file_name)
{
 FILE *fnt_file;
 char *output_file_name;
 char *short_name=NULL;
 FNT fnt;
 fnt_file=open_input_file(fnt_file_name);
 fnt=read_fnt_head(fnt_file);
 show_start_message();
 go_offset(fnt_file,fnt.pcx_offset);
 short_name=get_short_name(fnt_file_name);
 output_file_name=get_name(short_name,".pcx");
 write_output_file(fnt_file,output_file_name,fnt.pcx_size);
 free(output_file_name);
 output_file_name=get_name(short_name,".txt");
 go_offset(fnt_file,fnt.text_offset);
 write_output_file(fnt_file,output_file_name,fnt.text_size);
 free(output_file_name);
 free(short_name);
 show_end_message();
}