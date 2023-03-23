#include <iostream>
#include <string>
#include <stack>
#include <cstdlib>

using namespace std;

int prec(char ch)
{
  switch (ch)
  {
  case '(':
    return 0;
  case '+':
  case '-':
    return 1;
  case '*':
  case '/':
    return 2;
  }
}

int main()
{
  string input;
  stack<char> st;
  getline(cin, input);

  string postfix = "";
  string num_str = "";
  for (int i = 0; i < input.size(); i++)
  {
    char ch = input[i];
    if (ch == ' ')
    {
      continue;
    }
    switch (ch)
    {
    case '+':
    case '-':
    case '*':
    case '/':
      while (!st.empty() && prec(ch) <= prec(st.top()))
      {
        postfix += st.top();
        st.pop();
      }
      st.push(ch);
      break;

    case '(':
      st.push(ch);
      break;

    case ')':
      while (!st.empty() && st.top() != '(')
      {
        postfix += st.top();
        st.pop();
      }
      st.pop();
      break;

    default:
      while (i < input.size() && input[i] != ' ')
      {
        num_str += input[i++];
      }
      postfix += num_str + " ";
      num_str = "";
      i--;
      break;
    }
  }

  while (!st.empty())
  {
    postfix += st.top();
    st.pop();
  }

  stack<double> operands;
  for (int i = 0; i < postfix.size(); i++)
  {
    char ch = postfix[i];
    if (ch == ' ')
    {
      continue;
    }
    if (ch >= '0' && ch <= '9')
    {
      double num = atof(&postfix[i]);
      while (postfix[i] != ' ')
      {
        i++;
      }
      operands.push(num);
    }
    else
    {
      double operand2 = operands.top();
      operands.pop();
      double operand1 = operands.top();
      operands.pop();
      double result;
      switch (ch)
      {
      case '+':
        result = operand1 + operand2;
        break;
      case '-':
        result = operand1 - operand2;
        break;
      case '*':
        result = operand1 * operand2;
        break;
      case '/':
        if (operand2 == 0)
        {
          cout << "Error : zero division error" << endl;
          return 0;
        }
        result = operand1 / operand2;
        break;
      }
      operands.push(result);
    }
  }

  printf("%.2f\n", operands.top());

  return 0;
}
