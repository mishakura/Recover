#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

const int unit_of_512 = 512;
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
   if(argc != 2)
   {
    printf("Usage: ./program source\n");
    return 1;
   }
   
   BYTE arr;
   int sizeofmemory = 0;
   int counter = 0;
   bool isnewJPEG = true;
   int JPEGcount = 0;
   char filename[8];
   int count = 0;
   
   // Checking size of the memory card.
   FILE *file = fopen(argv[1] , "r");
   
   while(fread(&arr, sizeof(BYTE), 1, file))
   {
    sizeofmemory++;
   }
   
   fclose(file);
   
   // Open the memory card.
     FILE *card = fopen(argv[1] , "r");
    if(card == NULL)
    {
     return 1;
    }
   BYTE buffer[unit_of_512];
   
   while(counter < sizeofmemory)
   {
    // Reading 512 bytes into an array.
    if(count == 0)
    {
    fread(&buffer, sizeof(BYTE),unit_of_512, card);
    }
     // Checking for JPEG.
      if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0)== 0xe0)
    {
    // Checking for new JPEG.
     if(isnewJPEG == true)
     {
      
      // Naming the JPEG. 
      sprintf(filename, "%03i.jpg",JPEGcount);
      
      FILE *newJPEG = fopen(filename, "w");
      if (newJPEG == NULL)
      {
       return 1;
      }
      
      fwrite(&buffer, sizeof(BYTE),unit_of_512, newJPEG);
     
      counter = counter + 512;
      JPEGcount++;
      isnewJPEG = false;
     
      count = 0;
      fclose(newJPEG);
      
     }
     else
     {
      
      isnewJPEG = true;
      count = 1;
      
     }
     
    }
   // 
    else
    {
     FILE *sameJPEG = fopen(filename, "a");
     if(sameJPEG == NULL)
     {
     return 1;
     }
     
     fwrite(&buffer, sizeof(BYTE),unit_of_512, sameJPEG);
     counter = counter + 512;
     count = 0;
     fclose(sameJPEG);
    }
   }
   
      fclose(card);
      return 0;
}