// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int HelpF(char Th) {
    switch (Th)
    {
    case '(':
        return 0;
        break;
    case ')':
        return 1;
        break;
    case '+':
        return 2;
        break;
    case '-':
        return 2;
        break;
    case '*':
        return 3;
        break;
    case '/':
        return 3;
        break;
    case ' ':
        return 4;
    default:
        return 5;
    }
    return -1;
}

std::string infx2pstfx(std::string inf) {
  TStack<char, 100> stack;
  std::string output;
  int i = 0;
  for (; i < inf.length(); i++) {
    if (5 == pr(inf[i])) {
      output += inf[i];
      while (5 == pr(inf[i + 1]) && (i + 1) < inf.length()) {
        output += inf[i + 1];
        i += 1;
      }
      output += ' ';
    } else {
      if (0 == pr(inf[i])) {
        stack.push(inf[i]);
      } else if (pr(inf[i]) > pr(stack.get())) {
        stack.push(inf[i]);
      } else if (stack.isEmpty()) {
        stack.push(inf[i]);
      } else if (1 == pr(inf[i])) {
        while (0 != pr(stack.get())) {
          output += stack.get();
          output += ' ';
          stack.pop();
        }
        stack.pop();
      } else if (pr(inf[i]) <= pr(stack.get())) {
        while (!stack.isEmpty() && 1 < pr(stack.get())) {
          output += stack.get();
          output += ' ';
          stack.pop();
        }
        stack.push(inf[i]);
      }
    }
  }
  while (!stack.isEmpty()) {
    output += stack.get();
    output += ' ';
    stack.pop();
  }
  output.pop_back();
  return output;
}

int eval(std::string pref) {
    TStack<int, 100> stackT;
    std::string output;
    int c = 0;
    for (int i = 0; i < pref.length(); i++) {
        std::string check = "";
        while (5 == pr(pref[i])) {
            check += pref[i];
            i += 1;
        }
        if (check != "") {
            stackT.push(std::stoi(check));
        }
        if (2 == pr(pref[i]) || 3 == pr(pref[i])) {
            int a = stackT.get();
            stackT.pop();
            int b = stackT.get();
            stackT.pop();
            if ('-' == pref[i]) {
                c = b - a;
                stackT.push(c);
            }
            else if ('+' == pref[i]) {
                c = a + b;
                stackT.push(c);
            }
            else if ('*' == pref[i]) {
                c = a * b;
                stackT.push(c);
            }
            else if ('/' == pref[i]) {
                c = b / a;
                stackT.push(c);
            }
        }
    }
    return stackT.get();
}
