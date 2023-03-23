#include <iostream>
#include <stack>
#include <string>

void checkMatching(const std::string &str)
{
  std::stack<char> s;
  int line_count = 0;
  int bracket_count = 0;
  bool inQuote = false;

  for (int i = 0; i < str.length(); i++)
  {
    char c = str[i];

    if (c == '\n')
    {
      line_count++;
    }
    if (c == '\"')
    {
      inQuote = !inQuote;
    }
    if (inQuote && c == '\n')
    {
      line_count++;
    }

    if (!inQuote && (c == '(' || c == '[' || c == '{'))
    {
      s.push(c);
    }
    else if (!inQuote && (c == ')' || c == ']' || c == '}'))
    {

      if (s.empty())
      {
        std::cout << "Error, Line_count : " << line_count << ", bracket_count : " << bracket_count << std::endl;
        return;
      }
      char top = s.top();
      s.pop();
      if ((top == '(' && c != ')') || (top == '[' && c != ']') || (top == '{' && c != '}'))
      {
        std::cout << "Error, Line_count : " << line_count << ", bracket_count : " << bracket_count << std::endl;
        return;
      }
      bracket_count++;
    }
  }

  if (!s.empty())
  {
    std::cout << "Error, Line_count : " << line_count << ", bracket_count : " << bracket_count << std::endl;
    return;
  }

  std::cout << "OK, Line_count : " << line_count << ", bracket_count : " << bracket_count << std::endl;
}

int main()
{
  std::string Str, temp;
  while (true)
  {
    std::getline(std::cin, temp);
    if (temp == "EOF")
      break;
    Str.append(temp);
    Str.append("\n");
    std::cin.clear();
  }
  checkMatching(Str);

  return 0;
}
