
#include "ip_filter.h"


int main()
{

    try
    {

        std::vector<std::vector<uint8_t>> numeric_data;

        input_data(numeric_data);


        work_hard (numeric_data, true);


        //Вывод результатов
        show (numeric_data, [](std::vector<uint8_t>){return true;});
        show (numeric_data, [](std::vector<uint8_t> x){if (x[0]==1) return true; else return false;});
        show (numeric_data, [](std::vector<uint8_t> x){if ((x[0]==46) && (x[1]==70)) return true; else return false;});
        show (numeric_data, [](std::vector<uint8_t> x){for (int i=0; i<4; i++) if (x[i]==46) return true; return false;});


    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }


   
    return 0;
}
