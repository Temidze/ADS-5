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
    TStack  <char, 100> stack1;
    std::string out;
    for (int i = 0; i < inf.length(); i++) {
        //циферки
        if (5 == HelpF(inf[i])) {
            out += inf[i];
            while (5 == HelpF(inf[i + 1]) && (i + 1) < inf.length()) {
                out += inf[i + 1];
                i += 1;
            }
            out += ' ';
        }
        //Не циферки как не странно
        else {
            if (HelpF(inf[i]) == 0) {
                stack1.push(inf[i]);
            }
            else if (HelpF(inf[i]) > HelpF(stack1.get())) {
                stack1.push(inf[i]);
            }
            else if (stack1.isEmpty()) {
                stack1.push(inf[i]);
            }
            else if (HelpF(inf[i]) == 1) {
                while (0 != HelpF(stack1.get())) {
                    out += stack1.get();
                    out += ' ';
                    stack1.pop();
                }
                stack1.pop();
            }
            else if (HelpF(inf[i]) <= HelpF(stack1.get())) {
                while (!stack1.isEmpty() && 1 < HelpF(stack1.get())) {
                    out += stack1.get();
                    out += ' ';
                    stack1.pop();
                }
                stack1.push(inf[i]);
            }
        }
    }
    while (stack1.isEmpty() == false) {
        out += stack1.get();
        out += ' ';
        stack1.pop();
    }
    out.pop_back();
    return out;
}

int eval(std::string pref) {
    TStack<int, 100> stack2;
    std::string output;
    int c = 0;
    for (int i = 0; i < pref.length(); i++) {
        std::string check = "";
        while (5 == pr(pref[i])) {
            check += pref[i];
            i += 1;
        }
        if (check != "") {
            stack2.push(std::stoi(check));
        }
        if (2 == pr(pref[i]) || 3 == pr(pref[i])) {
            int a = stack2.get();
            stack2.pop();
            int b = stack2.get();
            stack2.pop();
            if ('-' == pref[i]) {
                c = b - a;
                stack2.push(c);
            }
            else if ('+' == pref[i]) {
                c = a + b;
                stack2.push(c);
            }
            else if ('*' == pref[i]) {
                c = a * b;
                stack2.push(c);
            }
            else if ('/' == pref[i]) {
                c = b / a;
                stack2.push(c);
            }
        }
    }
    return stack2.get();
}
