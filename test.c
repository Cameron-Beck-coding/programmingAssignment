#include <stdio.h>
#include <string.h>
int main(void){
       char str[10] = "hellohello";
       char *ptr;
       int cntV, cntC;
       for(ptr=str; *ptr!='\0'; ptr++){
              // Check whether character pointer finds any vowels
              if (*ptr == 'a' || *ptr == 'e' || *ptr == 'i' || *ptr == 'o' || *ptr == 'u')
              {

                     // If vowel found increment the count
                     cntV++;
              }
       }
       printf("%d",cntV);
}