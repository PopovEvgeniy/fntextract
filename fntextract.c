#include "fntextract.h"
#include "format.h"
#include "exitcode.h"

void show_intro();
void show_error(const char *message);
FILE *open_input_file(const char *name);
FILE *create_output_file(const char *name);
void read_data(void *data,const size_t length,FILE *input);
void write_data(const void *data,const size_t length,FILE *output);
void go_offset(FILE *target,const unsigned long int offset);
char *get_memory(const size_t length);
void check_signature(const char *signature);
void data_dump(FILE *input,FILE *output,const size_t length);
void fast_data_dump(FILE *input,FILE *output,const size_t length);
void write_output_file(FILE *input,const char *name,const size_t length);
size_t get_name_without_extension_length(const char *source);
char *get_name_without_extension(const char *name);
char *get_name(const char *name,const char *extension);
FNT read_fnt_head(FILE *target);
void work(const char *fnt_file_name);

int main(int argc, char *argv[])
{
 show_intro();
 if (argc<2)
 {
  puts("You must give a target file name as the command-line argument!");
  exit(COMMAND_LINE_ARGUMENTS_ERROR);
 }
 else
 {
  puts("Working...");
  work(argv[1]);
  puts("The work has been finished");
 }
 return 0;
}

void show_intro()
{
 putchar('\n');
 puts("FNT EXTRACT");
 puts("Version 2.5.7");
 puts("Mugen font decompiler by Popov Evgeniy Alekseyevich, 2008-2026 years");
 puts("This program is distributed under the GNU GENERAL PUBLIC LICENSE");
 putchar('\n');
}

void show_error(const char *message)
{
 fputc('\n',stderr);
 fputs(message,stderr);
 fputc('\n',stderr);
}

FILE *open_input_file(const char *name)
{
 FILE *target=NULL;
 if (name==NULL)
 {
  show_error("Can't open the input file");
  exit(OPEN_FILE_ERROR);
 }
 target=fopen(name,"rb");
 if (target==NULL)
 {
  show_error("Can't open the input file");
  exit(OPEN_FILE_ERROR);
 }
 return target;
}

FILE *create_output_file(const char *name)
{
 FILE *target=NULL;
 if (name==NULL)
 {
  show_error("Can't create the ouput file");
  exit(CREATE_FILE_ERROR);
 }
 target=fopen(name,"wb");
 if (target==NULL)
 {
  show_error("Can't create the ouput file");
  exit(CREATE_FILE_ERROR);
 }
 return target;
}

void read_data(void *data,const size_t length,FILE *input)
{
 if (fread(data,sizeof(char),length,input)<length)
 {
  show_error("Can't read data!");
  exit(READ_DATA_ERROR);
 }

}

void write_data(const void *data,const size_t length,FILE *output)
{
 if (fwrite(data,sizeof(char),length,output)<length)
 {
  show_error("Can't write data!");
  exit(WRITE_DATA_ERROR);
 }

}

void go_offset(FILE *target,const unsigned long int offset)
{
 if (fseek(target,offset,SEEK_SET)!=0)
 {
  show_error("Can't jump to the target offset");
  exit(SET_FILE_POSITION_ERROR);
 }

}

char *get_memory(const size_t length)
{
 char *memory=NULL;
 memory=(char*)calloc(length,sizeof(char));
 if(memory==NULL)
 {
  show_error("Can't allocate memory");
  exit(MEMORY_ALLOCATION_ERROR);
 }
 return memory;
}

void check_signature(const char *signature)
{
 if (strncmp(signature,"ElecbyteFnt",12)!=0)
 {
  show_error("The invalid format");
  exit(INVALID_FORMAT_ERROR);
 }

}

void data_dump(FILE *input,FILE *output,const size_t length)
{
 char *buffer=NULL;
 size_t current=0;
 size_t elapsed=0;
 size_t block=4096;
 buffer=get_memory(block);
 for (current=0;current<length;current+=block)
 {
  elapsed=length-current;
  if (elapsed<block)
  {
   block=elapsed;
  }
  read_data(buffer,block,input);
  write_data(buffer,block,output);
 }
 free(buffer);
}

void fast_data_dump(FILE *input,FILE *output,const size_t length)
{
 char *buffer=NULL;
 buffer=(char*)malloc(length);
 if (buffer==NULL)
 {
  data_dump(input,output,length);
 }
 else
 {
  read_data(buffer,length,input);
  write_data(buffer,length,output);
  free(buffer);
 }

}

void write_output_file(FILE *input,const char *name,const size_t length)
{
 FILE *output=NULL;
 output=create_output_file(name);
 fast_data_dump(input,output,length);
 fclose(output);
}

size_t get_name_without_extension_length(const char *source)
{
 size_t index=0;
 size_t position=0;
 size_t length=0;
 if (source!=NULL)
 {
  length=strlen(source);
 }
 for (index=length;index>0;--index)
 {
  position=index-1;
  if (source[position]==DIRECTORY_SEPARATOR)
  {
   break;
  }
  if (source[position]=='.')
  {
   if (position>0)
   {
    if ((source[position-1]!=DIRECTORY_SEPARATOR) && (source[position-1]!='.'))
    {
     length=position;
     break;
    }

   }

  }

 }
 return length;
}

char *get_name_without_extension(const char *name)
{
 char *result=NULL;
 size_t length=0;
 length=get_name_without_extension_length(name);
 if (length>0)
 {
  result=get_memory(length+1);
  strncpy(result,name,length);
 }
 return result;
}

char *get_name(const char *name,const char *extension)
{
  char *result=NULL;
  char *name_without_extension=NULL;
  size_t name_length=0;
  size_t extension_length=0;
  name_without_extension=get_name_without_extension(name);
  if (name_without_extension!=NULL)
  {
   name_length=strlen(name_without_extension);
  }
  if (extension!=NULL)
  {
   extension_length=strlen(extension);
  }
  if ((name_length>0) && (extension_length>0))
  {
   result=get_memory(name_length+extension_length+1);
   strncpy(result,name_without_extension,name_length);
   strncat(result,extension,extension_length);
  }
  free(name_without_extension);
  return result;
}

FNT read_fnt_head(FILE *target)
{
 FNT fnt;
 read_data(&fnt,sizeof(FNT),target);
 check_signature(fnt.signature);
 return fnt;
}

void work(const char *fnt_file_name)
{
 FILE *fnt_file=NULL;
 char *output_file_name=NULL;
 FNT fnt;
 fnt_file=open_input_file(fnt_file_name);
 fnt=read_fnt_head(fnt_file);
 go_offset(fnt_file,fnt.pcx_offset);
 output_file_name=get_name(fnt_file_name,".pcx");
 write_output_file(fnt_file,output_file_name,(size_t)fnt.pcx_size);
 free(output_file_name);
 output_file_name=get_name(fnt_file_name,".txt");
 go_offset(fnt_file,fnt.text_offset);
 write_output_file(fnt_file,output_file_name,(size_t)fnt.text_size);
 fclose(fnt_file);
 free(output_file_name);
}