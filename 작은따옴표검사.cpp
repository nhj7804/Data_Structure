#include <iostream>
#include <string>

bool inQuote = false;

int matching(const std::string &Str, int idx)
{
  for (int i = idx + 1; i < Str.length(); ++i)
  {
    if (Str[i] == '\\')
      continue;
    if (Str[i] == '\'')
      return i;
  }
  inQuote = true;
  return -1;
}

int checkMatching(const std::string &Str)
{
  int quoteCount = 0;
  for (int i = 0; i < Str.length(); ++i)
  {
    if (Str[i] == '\\')
      continue;
    else if (Str[i] == '\'')
    {
      int temp = matching(Str, i);

      if (temp == -1)
        return quoteCount;

      quoteCount++;
      i = temp;
    }
  }
  return quoteCount;
}

int main()
{
  std::string temp;
  int lineCnt = 0, quoteCount = 0;

  while (true)
  {
    std::getline(std::cin, temp);
    if (temp == "EOF")
      break;
    lineCnt++;
    quoteCount += checkMatching(temp);
    std::cin.clear();
  }

  if (inQuote)
  {
    std::cout << "Error, Line_count : " << lineCnt << ", quotes_count : " << quoteCount << std::endl;
  }
  else
  {
    std::cout << "OK, Line_count : " << lineCnt << ", quotes_count : " << quoteCount << std::endl;
  }

  return 0;
}