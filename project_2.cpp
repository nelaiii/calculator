#include <iostream>
#include <cstdlib>
#include <vector>
#include <windows.h>
#include <map>
#include <cmath>
#include <iterator>
#include <chrono>
#include <cassert>

using namespace std;
using namespace chrono;
const vector <int> tested_set_prime_perfect = {1, 2, 3, 4, 62, 6, 28, 211, 503, 496, 8128};
const vector <pair<int, int>> tested_set_gcd_lcm = {{5, 25}, {62, 64}, {4, 1257}, {3, 3}, {51, 249}, {3, 4}, {88, 98}, {66, 666}, {589350, 209580202}, {98267592, 8020851}, {200111444, 201010202}};
const vector <pair<int, int>> tested_set_ca_1 = {{1, 2}, {3, 62}, {1, 2}, {1, 2}, {2, 3}, {12, 6}, {1, 8}, {1, 8}, {3, 4}, {3, 4}, {425, 64}};
const vector <pair<int, int>> tested_set_ca_2 = {{1, 3}, {2, 64}, {1, 2}, {2, 3}, {1, 3}, {4, 3}, {2, 3}, {2, 3}, {1, 4}, {1, 4}, {646, 32}};
const vector <char> tested_set_char = {'+', '+', '-', '-', '+', '+', '+', '-', '+', '-', '-'};
const vector <pair<string, string>> prime_and_perfect_check = {{"простое", "не совершенное"}, {"простое", "не совершенное"}, {"простое", "не совершенное"},
                                                         {"не простое", "не совершенное"}, {"не простое", "не совершенное"}, {"не простое", "совершенное"},
                                                         {"не простое", "совершенное"}, {"простое", "не совершенное"}, {"простое", "не совершенное"},
                                                         {"не простое", "совершенное"}, {"не простое", "совершенное"},};
const vector <pair<int, long long int>> gcd_and_lcm_check = {{5, 25}, {2, 1984}, {1, 5028}, {3, 3}, {3, 4233}, {1, 12}, {2, 4312}, {6, 7326}, {2, 61758046024350},{3, 262729904520264},{2, 20112220890475844}};
const vector <pair<long long int,long long int>> calc_check = {{5, 6}, {79, 992}, {0, 2}, {-1, 6}, {1, 1}, {10, 3}, {19, 24}, {-13, 24}, {1, 1}, {1, 2}, {-867, 64}};

vector<int> find_or_add_div(int value, map<int, vector<int>> &divs) {
    vector<int> divisors;
    if (divs.find(value) != divs.end()) {//если делители есть в map:
        return divs[value];//возвращаем массив с делителем
    } else {
        for (int i = 1; i <= value; i++) {
            if (value % i == 0) {
                divisors.push_back(i);
            }
        }
    }
    return divisors;
}

pair<string, string> is_prime_and_perfect(int value, map<int, vector<int>> &divs) {
    pair<string, string> parameters;
    vector<int> array_divs = find_or_add_div(value, divs);
    int sum = 0;
    parameters.first = (array_divs.size() > 2) ? "не простое" : "простое";
    for (int i = 0; i < array_divs.size() - 1; i++) {
        sum += array_divs[i];
    }
    parameters.second = (sum == value) ? "совершенное" : "не совершенное";
    return parameters;
}

int gcd(pair<int, int> values, map<int, vector<int>> &divs) { // greatest common divisor
    vector<int> divs_1 = find_or_add_div(abs(values.first), divs);
    vector<int> divs_2 = find_or_add_div(abs(values.second), divs);
    for (auto it = divs_1.end() - 1; it >= divs_1.begin(); --it) {
        if (find(divs_2.begin(), divs_2.end(), *it) != divs_2.end()) {
            return *it;
        }
    }
    return 1;
}

long long int lcm(pair<int, int> values, map<int, vector<int>> &divs) { // lowest common multiple
    int value_1 = abs(values.first), value_2 = abs(values.second);
    auto lcm_res = (long long int) ((((double) value_1) / ((double) gcd(values, divs))) * (double) value_2);
    return lcm_res;
}

void analyzer(pair<int, int> values, map<int, vector<int>> &divs) {
    system_clock::time_point start = system_clock::now();
    pair<string, string> str_1 = is_prime_and_perfect(values.first, divs);
    pair<string, string> str_2 = is_prime_and_perfect(values.second, divs);
    cout << "Первое число = " << values.first << " " << str_1.first << ", " << str_1.second << endl;
    cout << "Второе число = " << values.second << " " << str_2.first << ", " << str_2.second << endl;
    cout << "Наибольший общий делитель: " << gcd(values, divs) << endl;
    cout << "Наименьшее общее кратное: " << lcm(values, divs) << endl << endl;
    system_clock::time_point end = system_clock::now();
    duration<double> sec = end - start;
    cout << "Время выполнения:" << sec.count() << endl;
}

pair<long long int,long long int> calc(pair<int, int> value1, pair<int, int> value2, char s, map<int, vector<int>> &divs) {
    int denominator = lcm({value1.second, value2.second}, divs);
    value1.first *= (denominator / value1.second);
    value2.first *= (denominator / value2.second);
    pair<long long int,long long int> result;
    if (s == '+') result.first = value1.first + value2.first;
    else result.first = value1.first - value2.first;
    result.second = denominator;
    if (result.first!=0){
        int reduce = gcd(result, divs);
        result.first /= reduce;
        result.second /= reduce;
    }
    return result;
}
void testing_function(map<int, vector<int>> &divs) {
    system_clock::time_point start = system_clock::now();
    for (int i = 0; i < tested_set_prime_perfect.size(); i ++) {
        assert(is_prime_and_perfect(tested_set_prime_perfect[i], divs) == prime_and_perfect_check[i]);
        assert((gcd(tested_set_gcd_lcm[i], divs) == gcd_and_lcm_check[i].first) && (lcm(tested_set_gcd_lcm[i], divs) == gcd_and_lcm_check[i].second));
        assert(calc(tested_set_ca_1[i], tested_set_ca_2[i], tested_set_char[i], divs) == calc_check[i]);
    }
    cout << "Тесты пройдены!"<< endl;
    system_clock::time_point end = system_clock::now();
    duration<double> sec = end - start;
    cout << "Время выполнения:" << sec.count() << endl;
}
int check_and_run(int func) {
    map<int, vector<int>> divs; int flag = 1;
    if (func == 1) {
        cout << "Вы запустили АНАЛИЗАТОР" << endl << "Введите два положительных целых числа" << endl;
        pair<int, int> values;
        cin >> values.first >> values.second;
        analyzer(values, divs);
        flag = 0;
    } else if (func == 2) {
        cout << "Вы запустили КАЛЬКУЛЯТОР" << endl << "Введите желаемое выражение вида a/m + b/n  или  a/m - b/n " << endl;
        pair<int, int> value1; pair<int, int> value2; char c, fraction;
        cin >> value1.first >> fraction >> value1.second >> c >> value2.first >> fraction >> value2.second;
        system_clock::time_point start = system_clock::now();
        cout << to_string(value1.first) << "/" << to_string(value1.second) << " " << c << " " << to_string(value2.first) << "/" << to_string(value2.second) << " = ";
        pair<long long int,long long int> result = calc(value1, value2, c, divs);
        if (result.first % result.second == 0) cout << result.first << endl << endl;
        else cout << result.first << '/' << result.second << endl << endl;
        system_clock::time_point end = system_clock::now();
        duration<double> sec = end - start;
        cout << "Время выполнения:" << sec.count() << endl;
        flag = 0;
    } else if (func == 3){testing_function(divs);}
    else cout << "Введено неверное значение. Попробуйте снова." << endl;
    return flag;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    int func, flag, flag_1 = 1;
    while (flag_1) {
        flag = 1;
        while (flag) {
            cout << "Если хотите запустить анализатор - введите 1." << endl
                 << "Если хотите запустить калькулятор - введите 2." << endl
                 << "Если хотите запустить тестирующую функцию - введите 3." << endl
                << "Если хотите завершить программу - введите 4." << endl;
            cin >> func;
            if (func == 4) {
                flag = 0;
                flag_1 = 0;
            } else if (func == 1 or func == 2 or func == 3) { flag = check_and_run(func); }
            else cout << "Введено неверное значение. Попробуйте снова." << endl;
        }
    }
}
