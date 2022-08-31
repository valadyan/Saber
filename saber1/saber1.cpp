#include <stdio.h>
#include <string.h>

void PrintBin(long source)
{
  printf("%ld is ", source);

  if (source < 0)
  {
    printf("-");
    source *= -1;
  }

  const int countOfBinaries = sizeof(long) * 8;
  char binaries[countOfBinaries];
  memset(binaries, '0', countOfBinaries);

  int bitPointer = countOfBinaries - 1;
  bool hasRemainder = false;

  while (source >= 1)
  {
    hasRemainder = source % 2;
    source /= 2;

    if (hasRemainder)
    {
      binaries[bitPointer--] = '1';
      continue;
    }

    --bitPointer;
  }

  printf("%s \n", binaries);
}

int main()
{
  PrintBin(342);
  PrintBin(-222);
  PrintBin(0);
  PrintBin(1);

  return 0;
}
