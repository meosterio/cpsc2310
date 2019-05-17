#include <stdio.h>
#include <string.h>
#include <assert.h>

int prepareKey(char *key);
void encode(char *message, char *key, char *encr);
void decode(char *message, char *key, char *decr);

int main()
{
   char str0[60] = "attack at dawn";
   char str1[60] = "this is a test of the encoding algorithm";

   char key1[35] = "trailblazers";
   char key2[35] = "letsgotigersgofightwin";

   char e[60];
   char d[60];

   int k;
   k = prepareKey(key1);
   assert(k != 0);

   printf("\nstring: trailblazers\n");
   printf("key:    %s\n", key1);
   printf("---------------------------\n");
   printf("original:  %s\n", str0);
   encode(str0, key1, e);
   printf("encoded:   %s\n", e);
   decode(e, key1, d);
   printf("decoded:   %s\n", d);

   printf("\nstring: trailblazers\n");
   printf("key:    %s\n", key1);
   printf("---------------------------\n");
   printf("original:  %s\n", str1);
   encode(str1, key1, e);
   printf("encoded:   %s\n", e);
   decode(e, key1, d);
   printf("decoded:   %s\n", d);


   k = prepareKey(key2);
   assert(k != 0);
   printf("\nstring: letsgotigersgofightwin\n");
   printf("key:    %s\n", key2);
   printf("------------------------------------\n");
   printf("original:  %s\n", str0);
   encode(str0, key2, e);
   printf("encoded:   %s\n", e);
   decode(e, key2, d);
   printf("decoded:   %s\n", d);

   printf("\nstring: letsgotigersgofightwin\n");
   printf("key:    %s\n", key2);
   printf("------------------------------------\n");
   printf("original:  %s\n", str1);
   encode(str1, key2, e);
   printf("encoded:   %s\n", e);
   decode(e, key2, d);
   printf("decoded:   %s\n", d);

   return 0;
}
