// Copyright 2021 NNTU-CS
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
    TStack<char, 100> stackO;
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
                stackO.push(inf[i]);
            }
            else if (HelpF(inf[i]) > HelpF(stackO.get())) {
                stackO.push(inf[i]);
            }
            else if (stackO.isEmpty()) {
                stackO.push(inf[i]);
            }
            else if (HelpF(inf[i]) == 1) {
                while (0 != HelpF(stackO.get())) {
                    out += stackO.get();
                    out += ' ';
                    stackO.pop();
                }
                stackO.pop();
            }
            else if (HelpF(inf[i]) <= HelpF(stackO.get())) {
                while (!stackO.isEmpty() && 1 < HelpF(stackO.get())) {
                    out += stackO.get();
                    out += ' ';
                    stackO.pop();
                }
                stackO.push(inf[i]);
            }
        }
    }
    while (stackO.isEmpty() == false) {
        out += stackO.get();
        out += ' ';
        stackO.pop();
    }
    out.pop_back();
    return out;
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
            int F = stackT.get();
            stackT.pop();
            int S = stackT.get();
            stackT.pop();
            if ('-' == pref[i]) {
                c = S - F;
                stackT.push(c);
            }
            else if ('+' == pref[i]) {
                c = F + S;
                stackT.push(c);
            }
            else if ('*' == pref[i]) {
                c = F * S;
                stackT.push(c);
            }
            else if ('/' == pref[i]) {
                c = S / F;
                stackT.push(c);
            }
        }
    }
    return stackT.get();
}
