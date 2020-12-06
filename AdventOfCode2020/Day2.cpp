#include "pch.h"
#include "reader.h"
#include "days.h"

class PasswordInput {
    public:
        PasswordInput(std::string line) {
            int start = 0;
            int end = line.find('-');
            this->min = std::stoi(line.substr(start, end));
            start = end + 1;
            end = line.find(' ');
            this->max = std::stoi(line.substr(start, end - start));
            start = end + 1;
            end = line.find(": ");
            this->requiredChar = line.substr(start, end - start).c_str()[0];
            start = end + 2;
            this->password = line.substr(start, line.size() - start);
        }

        bool isValid() {
            int count = std::count(password.begin(), password.end(), requiredChar);
            if (count >= min && count <= max) return true;
            return false;
        }

        bool isValid2() {
            const char* pwd = password.c_str();

            bool c1 = pwd[min - 1] == requiredChar;
            bool c2 = pwd[max - 1] == requiredChar;

            return c1 ? !c2 : c2;
        }

        std::string toString() {
            std::stringstream ss;
            ss << min << "-" << max << " " << requiredChar << ": " << password;
            return ss.str();
        }
    private:
        std::string password;
        char requiredChar;
        int min;
        int max;
};

int day2()
{
    std::vector<std::string> test{ "1-3 a: abcde", "1-3 b: cdefg", "2-9 c: ccccccccc" };
    std::ifstream ifs("Day2Input.txt", std::ifstream::in);
    std::vector<std::string> input = read_input(ifs);


    int valid = 0;
    int valid2 = 0;
    for (std::string line : input) {
        PasswordInput pwdInput(line);
        if (pwdInput.isValid()) valid++;
        if (pwdInput.isValid2()) valid2++;
    }
    std::cout << "valid passwords: " << valid << std::endl;
    std::cout << "valid passwords: " << valid2 << std::endl;

    return 0;
}

/*
* Output:
* valid passwords: 383
* valid passwords: 272
*/