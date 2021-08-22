#define ALL_COUNTRY "All"
#define CALC_BORDER "border"

enum c_choice { ALL = 1, SINGLE }; // all for all countries, Single for a single country
enum t_choice { BORDER = 1, SENSING_CABLE};

void c_handler(std::string* cflag, char* optarg); // c parameter handler
void t_handler(std::string* tflag, char* optarg); // t parameter handler
t_choice enum_calcType_setter(std::string str);
c_choice enum_countries_setter(std::string str);
std::string stringCapitalizer(char* str);

void c_handler(std::string* cflag, char* optarg)
{
    if (optarg) cflag->assign(stringCapitalizer(optarg));

    if (cflag->length() != 3)
    {
        cflag->assign(ALL_COUNTRY);
    }	
}

void t_handler(std::string* tflag, char* optarg)
{
    if (optarg) tflag->assign(stringCapitalizer(optarg));
}

c_choice enum_countries_setter(std::string str)
{
    c_choice choice;
    if ( str == ALL_COUNTRY ) choice = ALL;
    else choice = SINGLE;
    return choice;
}

t_choice enum_calcType_setter(std::string str)
{
    t_choice choice;
    str == "BORDER" ? choice = BORDER : choice = SENSING_CABLE;
    return choice;
}

std::string stringCapitalizer(char* str)
{
    std::string capitalizedString{};
    while(*str != '\0')
    {
        if(*str >= 97)
            *str = *str - 32;
        capitalizedString.push_back(*str);
        ++(str);
    }
    return capitalizedString;
}