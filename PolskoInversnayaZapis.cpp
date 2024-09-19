using namespace std;
#include <iostream>
#include <vector>
#include <iomanip>
#include <string> 

// определяет приоритет знака у символа
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

// выводит строку таблицы, вызывается после каждого шага
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
    getline(cin, inputStr);
    cout << "\n";
    inputStr.erase(std::remove(inputStr.begin(), inputStr.end(), ' '), inputStr.end());
    vector<char> input(inputStr.begin(), inputStr.end()); // переведем входную строку в вектор чаров, чтобы с ней было проще работать

    if (count(input.begin(), input.end(), '(') != count(input.begin(), input.end(), ')')) {
        cout << "Должно быть равное количество элементов ( и )!\n";
        return 0;
    }

    string output = "";
    vector<char> stack;

    //вывод шапки таблицы
    string head[]{ "Шаг", "Входная строка", "Стек", "Выходная строка" };
    cout << head[0] << setw(5 - head[0].length()) << " | " << head[1] << setw(40 - head[1].length()) << " | " << head[2] << setw(40 - head[2].length()) << " | " << head[3] << '\n';

    outTypeString(-1, input, stack, output);

    for (int i = 0; i < input.size(); i++) {
        const char inputSymbol = input[i];
        const int priority = getPriority(inputSymbol);
        // все переменные и числа сразу пеносим в выходную строку
        if (priority == -1) { 
            output = output + inputSymbol;
            outTypeString(i, input, stack, output);
            continue;
        }
        // "(" добавляем в конец стека всегда 
        if (priority == 0) {
            stack.push_back(inputSymbol);
            outTypeString(i, input, stack, output);
            continue;
        }

        // обработка ")"
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

        // обработка всех остальных случаев с обычными знаками
        while (stack.size() > 0 && priority <= getPriority(stack[stack.size() - 1]) && stack[stack.size() - 1] != '(') {
            output = output + stack[stack.size() - 1];
            stack.pop_back();
        }
        stack.push_back(inputSymbol);
        outTypeString(i, input, stack, output);
    }

    // после обработки входной строки, переносим в выходную стек
    int i = input.size();
    while (stack.size() > 0){
        output = output + stack[stack.size() - 1];
        stack.pop_back();
        outTypeString(i, input, stack, output);
        i++;
    }
    cout << "\n\n\n\n\n\n Введите любую клавишу для выхода.\n";
    cin >> inputStr;
    return 0;
}

