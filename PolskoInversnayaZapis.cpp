using namespace std;
#include <iostream>
#include <vector>
#include <iomanip>
#include <string> 

int getPriority(char symbol) {
    if (symbol == '(') {
        return 0;
    }
    if (symbol == '=' || symbol == ')') {
        return 1;
    }
    if (symbol == '+' || symbol == '-') {
        return 2;
    }
    if (symbol == '*' || symbol == '/') {
        return 3;
    }
    return -1; // не знак
}

void outTypeString(int step, vector<char> input, vector<char> stack, string  output) {
    string stackStr(stack.begin(), stack.end());
    vector<char> newInput;
    for (int i = step+1; i < input.size(); i++)
    {
        newInput.push_back(input[i]);
    }
    string inputStr(newInput.begin(), newInput.end());
    string stepStr = to_string(step+1);
    cout << step+1 << setw(5-stepStr.length()) << "|" << inputStr << setw(40 - inputStr.length()) << "|" << stackStr << setw(40 - stackStr.length()) << "|" << output << '\n';
}

int main()
{
    system("chcp 1251");
    system("cls");
    cout << "Входная строка: ";
    string inputStr;
    cin >> inputStr;
    cout << "\n";
    vector<char> input(inputStr.begin(), inputStr.end());

    if (count(input.begin(), input.end(), '(') != count(input.begin(), input.end(), ')')) {
        cout << "Должно быть равное количество элементов ( и )!\n";
        return 0;
    }


    string output = "";
    vector<char> stack;

    string head[]{ "Шаг", "Входная строка", "Стек", "Выходная строка" };
    cout << head[0] << setw(5 - head[0].length()) << " | " << head[1] << setw(40 - head[1].length()) << " | " << head[2] << setw(40 - head[2].length()) << " | " << head[3] << '\n';

    //a+b*d/c=0
    // a/b*d+c
    // a+b*(d-e)=0
    // a+(b*(d-e))



    outTypeString(-1, input, stack, output);



    for (int i = 0; i < input.size(); i++) {
        const char inputSymbol = input[i];
        const int priority = getPriority(inputSymbol);
        if (priority == -1) {
            output = output + inputSymbol;
            outTypeString(i, input, stack, output);
            continue;
        }

        if (priority == 0) {
            stack.push_back(inputSymbol);
            outTypeString(i, input, stack, output);
            continue;
        }

        if (inputSymbol == ')') {
            if (count(input.begin(), input.end(), '(') == 0) {
                cout << ") не может стоять перед (!\n";
                return 0;
            }
            while (stack[stack.size() - 1] != '(') {
                output = output + stack[stack.size() - 1];
                stack.pop_back();
            }
            stack.pop_back();
            outTypeString(i, input, stack, output);
            continue;
        }

        while (stack.size() > 0 && priority <= getPriority(stack[stack.size() - 1]) && stack[stack.size() - 1] != '(') {
            output = output + stack[stack.size() - 1];
            stack.pop_back();
        }
        stack.push_back(inputSymbol);
        outTypeString(i, input, stack, output);
    }
    int i = input.size();
    while (stack.size() > 0){
        output = output + stack[stack.size() - 1];
        stack.pop_back();
        outTypeString(i, input, stack, output);
        i++;
    }
    cout << "\n\n\n\n\n\n";
}

