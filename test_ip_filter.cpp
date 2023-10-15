#define BOOST_TEST_MODULE test_ip_filter


#include <boost/test/unit_test.hpp>

#include "ip_filter.h"
#include <sstream>

BOOST_AUTO_TEST_SUITE(test_ip_filter)

//Тест функции std::vector<std::string> split(const std::string &str, char devider)
BOOST_AUTO_TEST_CASE(test_split)
{
    std::string str="one. two.three ";
    auto res=split(str, '.');
    bool test_res=true;
    if ( (res[0]!="one") || (res[1]!=" two") || (res[2]!="three ") ) test_res=false;
    BOOST_CHECK (test_res);
}

//Тест функции void exchange(std::vector<std::vector<uint8_t>> &data, size_t a, size_t  b)
BOOST_AUTO_TEST_CASE(test_exchange)
{
    std::vector<uint8_t> v1, v2, v3, v4;
    for (uint8_t i=0; i<4; i++) v1.push_back(i);
    bool test_res=true;

    std::vector<std::vector<uint8_t>> data;
    std::vector<std::vector<uint8_t>> etalon;

    //test incorrect input data
    data.push_back(v1);
    etalon=data;
    exchange(data, 1, 2);
    if (etalon!=data) test_res=false;

    //test incorrect index
    for (int i=1; i<4; i++) data.push_back(v1);
    etalon=data;

    exchange(data, 3, 4);
    if (etalon!=data) test_res=false;

    //test with correct parameters
    exchange(data, 1, 2);
    if ((data[1]!=etalon[2]) || (data[2]!=etalon[1]) ) test_res=false;

    BOOST_CHECK (test_res);

}

//Тест функции void input_data(std::vector<std::vector<uint8_t>> &numeric_data)
BOOST_AUTO_TEST_CASE(test_input_data)
{
        bool test_res=true;
        std::vector<std::vector<uint8_t>> numeric_data;


        std::string str= "12.234.3.5\taaaaa\tbbbbb\n1.24.15\tcccc\tdddd\n";
        std::stringstream sbuf(str);
        std::streambuf *buf_ptr=std::cin.rdbuf(); //запомним старый буффер
        std::cin.rdbuf(sbuf.rdbuf()); //перенаправляем строку данных в cin

        //test with correct input data
        input_data(numeric_data);
        if ( numeric_data.size()==0) test_res=false;

        else
        {
            if ((numeric_data[0].size()!=4) || (numeric_data[1].size()!=3))
            {
                test_res=false;
            }
            else if (    (   numeric_data[0][0]!=12)
                     || (numeric_data[0][1]!=234)
                     || (numeric_data[0][2]!=3)
                     || (numeric_data[0][3]!=5)
                     || (numeric_data[1][0]!=1)
                     || (numeric_data[1][1]!=24)
                     || (numeric_data[1][2]!=15)
                     ) test_res=false;
        }
        std::cin.rdbuf(buf_ptr); //возвращаем cin

        // Не проводим тестты с некорректными данными, поскольку по условиям контрольной входные данные корректны
    BOOST_CHECK (test_res);
}



//Тест функции void show (std::vector<std::vector<uint8_t>> &numeric_data, bool(*sort_func)(std::vector<uint8_t>))
BOOST_AUTO_TEST_CASE(test_show)
{
    bool test_res=true;
    std::vector<uint8_t> v1{1, 2, 3, 4};
    std::vector<uint8_t> v2{5, 6, 7, 8};
    std::vector<std::vector<uint8_t>> numeric_data {v1,v2};

    std::string str;
    std::stringstream sbuf;
    std::streambuf *buf_ptr=std::cout.rdbuf(); //запомним старый буффер
    std::cout.rdbuf(sbuf.rdbuf()); //перенаправляем весь cout в строку

    //test whith correct input data
    show (numeric_data, [](std::vector<uint8_t> x){if (x[0]==1) return true; else return false;});
    sbuf>>str;
    std::cout.rdbuf(buf_ptr); //возвращаем cout
    if (str!="1.2.3.4") test_res=false;

    BOOST_CHECK (test_res);
}

//Тест функции void work_hard (std::vector<std::vector<uint8_t>> &numeric_data, bool reverse)
BOOST_AUTO_TEST_CASE(test_work_hard)
{
    uint8_t in_data[5][4] {{1, 12, 2, 4},{1, 61, 7, 8},{2, 61, 75, 8},{1, 61, 75, 8},{1, 61, 75, 18}};
    uint8_t etalon_data[5][4] {{2, 61, 75, 8},{1, 61, 75, 18},{1, 61, 75, 8},{1, 61, 7, 8},{1, 12, 2, 4}};
    bool test_res=true;

    std::vector<std::vector<uint8_t>> numeric_data;
    for (int i=0; i<5;i++)
    {
        std::vector<uint8_t> temp;
        for (int j=0;j<4;j++) temp.push_back(in_data[i][j]);
        numeric_data.push_back(temp);
    }

    //Лексиграфическая сортировка тестового массива ip адресов
    work_hard(numeric_data,true);


    if ( numeric_data.size()!=5) test_res=false;

    else
    {
        if (       (numeric_data[0].size()!=4)
                || (numeric_data[1].size()!=4)
                || (numeric_data[2].size()!=4)
                || (numeric_data[3].size()!=4)
                || (numeric_data[4].size()!=4))
            {
                test_res=false;
            }
            else
            {
                bool res=true;
                for (int i=0; i<5;i++)
                {
                    for (int j=0;j<4;j++) if (numeric_data[i][j]!=etalon_data[i][j]) res=false;
                }
                if (!res) test_res=false;
            }
    }
    BOOST_CHECK (test_res);
}

BOOST_AUTO_TEST_SUITE_END()
