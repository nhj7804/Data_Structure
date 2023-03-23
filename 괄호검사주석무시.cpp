#include <iostream>
#include <stack>
#include <string>

void checkMatching(const std::string &str)
{
  std::stack<char> s;
  int line_count = 1;
  int bracket_count = 0;
  bool is_comment = false;
  bool is_string = false;
  char string_start = ' ';

  for (int i = 0; i < str.length(); i++)
  {
    char c = str[i];

    if (is_comment)
    {
      if (c == '\n')
      {
        line_count++;
      }
      continue;
    }
    else if (c == '/' && i + 1 < str.length() && str[i + 1] == '/')
    {
      is_comment = true;
      i++;
      continue;
    }
    else if (c == '/' && i + 1 < str.length() && str[i + 1] == '*')
    {
      is_comment = true;
      i++;
      continue;
    }

    if (!is_comment)
      if (c == '*' && i + 1 < str.length() && str[i + 1] == '/')
      {
        is_comment = false;
        i++;
        continue;
      }

    if (is_string)
    {
      if (c == string_start)
      {
        is_string = false;
      }
      continue;
    }
    else if (c == '\'' || c == '\"')
    {
      is_string = true;
      string_start = c;
      continue;
    }

    if (is_comment || is_string)
      continue;

    if (c == '(' || c == '[' || c == '{')
    {
      s.push(c);
    }
    else if (c == ')' || c == ']' || c == '}')
    {
      if (s.empty())
      {
        std::cout << "Error, Line_count : " << line_count << ", bracket_count : " << bracket_count << std::endl;
        return;
      }
      char top = s.top();
      s.pop();
      bracket_count++;
      if ((top == '(' && c != ')') || (top == '[' && c != ']') || (top == '{' && c != '}'))
      {
        std::cout << "Error, Line_count : " << line_count << ", bracket_count : " << bracket_count << std::endl;
        return;
      }
    }
    else if (c == '\n')
    {
      line_count++;
    }
  }

  if (!s.empty())
  {
    std::cout << "Error, Line_count : " << line_count << ", bracket_count : " << bracket_count << std::endl;
    return;
  }

  std::cout << "OK, Line_count : " << line_count - 1 << ", bracket_count : " << bracket_count << std::endl;
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
