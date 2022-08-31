#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void RemoveDups(char* str)
{
  size_t strLength = strlen(str);

  if (!strLength)
  {
    return;
  }

  size_t iter = 0;
  size_t insertIter = 1;
  size_t countOfCopies = 0;

  while (iter < strLength)
  {
    size_t aim = iter++;

    while (iter < strLength)
    {
      if (str[iter] != str[aim])
      {
        break;
      }

      ++iter;
      ++countOfCopies;
    }

    str[insertIter++] = str[iter];
    aim = iter;
  }
}

int main()
{
  char data[]="AAA BBB CCC";
  char data1[] = "";
  char data2[] = " AA";
  char data3[] = "A";
  char data4[] = "A BC L00";
  RemoveDups(data);
  RemoveDups(data1);
  RemoveDups(data2);
  RemoveDups(data3);
  RemoveDups(data4);
  printf("%s\n", data);
  printf("%s\n", data1);
  printf("%s\n", data2);
  printf("%s\n", data3);
  printf("%s\n", data4);

  return 0;
}

