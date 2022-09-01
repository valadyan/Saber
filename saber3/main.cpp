#include "List.h"

int main()
{
  List list;

  list.PushBack("afsdf");
  list.PushBack("af");
  list.PushBack("");
  list.PushBack("afsdf33333");
  list.PushBack("afsdf");
  list.PushBack("afsdfds");
//  list.Print();

//  return 0;

  const char path[] = "./file";

  FILE* file = fopen(path, "wb");
  if (file){
    list.Serialize(file);
    }

  fclose(file);

  List list2;
  file = fopen(path, "rb");
  if (file){
    list2.Deserialize(file);
    }

  fclose(file);
  list2.Print();

  return 0;
}

