
#include "ip_filter.h"


std::vector<std::string> split(const std::string &str, char devider)
{
    std::vector<std::string> result;
    std::string temp_str="";

    for (std::string::const_iterator it=str.begin(); it!=str.end(); it++)
    {
        auto simb=*it;
        if (simb!=devider) temp_str+=simb;
            else
        {
            result.push_back(temp_str);
            temp_str="";
        }
    }
    result.push_back(temp_str);
    return result;
}

void exchange(std::vector<std::vector<uint8_t>> &data, size_t a, size_t  b)
{
    //Функция меняет местами два элемента вектора
    if (data.size()<2) return;
    if (a>=data.size()) return;
    if (b>=data.size()) return;
    if (a==b) return;

    auto temp=data[a];
    data[a]=data[b];
    data[b]=temp;
}

bool logical_exchange(std::vector<std::vector<uint8_t>> &data, size_t  a, size_t  b, int param_sort)
{
    //Функция проверяет можно ли совершать обмен или нет в зависимости от значения предыдущего поля ip адреса
    bool usl=true;
    int t_int=param_sort;

    while (--t_int>=0) usl=(data[a][t_int] == data[b][t_int])? usl : false;

    if (usl)
    {
        exchange(data, a, b);
        return true;
    }
    else return false;
}

void lecsical_sort(std::vector<std::vector<uint8_t>> &data, int param_sort, bool reverse)
{
    //param_sort - определяет индекс внутреннего вектора по которому проведем сортировку
    //reverse - прямая или обратная сортировка

    bool did_exchange=true;
    while (did_exchange)
    {
        did_exchange=false;
        for (size_t i=0; i<data.size()-1; i++)
        {
            if (reverse)
            {
                if (data[i][param_sort] < data[i+1][param_sort])
                {
                    did_exchange=(logical_exchange(data, i, i+1, param_sort))? true : did_exchange;
                }
            }
            else
            {
                if (data[i][param_sort] > data[i+1][param_sort])
                    did_exchange=(logical_exchange(data, i, i+1, param_sort))? true : did_exchange;
            }
        }
    }
}


void show (std::vector<std::vector<uint8_t>> &numeric_data, bool(*sort_func)(std::vector<uint8_t>))
{
    //Отображение результатов с применением условий
    for(auto x: numeric_data)
    {
        int count=0;
        if (sort_func(x))
        for(auto y : x)
        {
            char divider=(count<3)? '.' : '\n';
             std::cout << static_cast<int>(y) <<divider;
            count++;
        }
    }
}

void work_hard (std::vector<std::vector<uint8_t>> &numeric_data, bool reverse)
{
    for (int param_sort=0; param_sort<4; param_sort++) lecsical_sort(numeric_data, param_sort, reverse);
}


void input_data(std::vector<std::vector<uint8_t>> &numeric_data)
{
    std::vector<std::vector<std::string>> data;
    for(std::string line; std::getline(std::cin, line);)
    {
        auto v = split(line, '\t');
        data.push_back(split(v.front(), '.'));
    }

    for (auto x: data)
    {
        std::vector<uint8_t> temp(0);
        for (auto y: x) temp.push_back(static_cast<uint8_t>(std::stoi(y)));
        numeric_data.push_back(temp);
    }
}


