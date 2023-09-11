#ifndef IP_FILTER_H
#define IP_FILTER_H

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <fstream>


//функция разделения строки с разделителем
std::vector<std::string> split(const std::string &str, char devider);

//функция обмена местами двух соседних членов вектора с ip адресами
void exchange(std::vector<std::vector<uint8_t>> &data, size_t a, size_t  b);

//функция ввода данных в формате задания и формирования вектора ip адресов  std::vector<std::vector<uint8_t>>
void input_data(std::vector<std::vector<uint8_t>> &numeric_data);

//функция отображения списка ip адресов . Строка отображается только если соответствует условию
void show (std::vector<std::vector<uint8_t>> &numeric_data, bool(*sort_func)(std::vector<uint8_t>));

//функция лексиграфической сортировки списка ip адресов
void work_hard (std::vector<std::vector<uint8_t>> &numeric_data, bool reverse);


#endif // IP_FILTER_H
