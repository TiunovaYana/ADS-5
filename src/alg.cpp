// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"
int prior(char op) {
    switch (op) {
    case '(': return 0;
    case ')': return 1;
    case '-': return 2;
    case '+': return 2;
    case '*': return 3;
    case '/': return 3;
    default: return -1;
    }
}
std::string infx2pstfx(std::string inf) {
std::string str1 = "";
    TStack<char, 100> stack;
    for (int i = 0; i < inf.length(); i++) {
        if ((inf[i] >= '0') && (inf[i] <= '9')) {
            if (str1 != "") {
                if (!((inf[i - 1] >= '0') && (inf[i - 1] <= '9'))) {
                    str1 += ' ';
                }
            }
            str1 += inf[i];
        } else {
            int pr = prior(inf[i]);
            bool fl = false;
            if ((stack.isEmpty()) || (pr > prior(stack.get()))) {
                fl = true;
            }
            if (((pr == 0) || fl) && (pr != 1)) {
                stack.push(inf[i]);
            } else {
                if (pr != 1) {
                    while ((prior(stack.get()) >= pr) && !(stack.isEmpty())) {
                        str1 += ' ';
                        str1 += stack.get();
                        stack.pop();
                    }
                    stack.push(inf[i]);
                } else {
                    while (prior(stack.get())) {
                        str1 += ' ';
                        str1 += stack.get();
                        stack.pop();
                    }
                    stack.pop();
                }
            }
        }
    }
    while (!(stack.isEmpty())) {
        str1 += ' ';
        str1 += stack.get();
        stack.pop();
    }
    return str1;
}

int eval(std::string pref) {
    TStack<int, 100> stack2;
    std::string str2 = "";
    int p = 0;
    for (int i = 0; i < pref.length(); i++) {
        if ((pref[i] >= '0') && (pref[i] <= '9')) {
            p = 1;
            str2 += pref[i];
        } else {
            if (p == 1) {
                stack2.push(std::stoi(str2));
                p = 0;
                str2 = "";
            }
            if (pref[i] != ' ') {
                int a = stack2.get();
                stack2.pop();
                int b = stack2.get();
                stack2.pop();
                switch (pref[i]) {
                case '-':
                    stack2.push(b - a);
                    break;
                case '+':
                    stack2.push(a + b);
                    break;
                case '*':
                    stack2.push(a * b);
                    break;
                case '/':
                    stack2.push(b / a);
                    break;
                }
            }
        }
    }
    int result = stack2.get();
    return result;
}
