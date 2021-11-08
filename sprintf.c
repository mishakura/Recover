#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
 int main(void)
 {
     char filename[7];
 int count = 0;
 for(int i = 0; i < 6; i++)
      {
      
  
      sprintf(filename, "%03i.jpg", count);
      printf("%s\n", filename);
      count++;
      }
 }