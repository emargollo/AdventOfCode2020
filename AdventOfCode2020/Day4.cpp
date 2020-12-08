#include "pch.h"
#include "reader.h"
#include "days.h"

static enum PassportKeys {
	nil,
	byr,
	iyr,
	eyr,
	hgt,
	hcl,
	ecl,
	pid,
	cid,
};

static std::map<std::string, PassportKeys> keyMap;

void initKeyMap() {
	keyMap["byr"] = byr;
	keyMap["iyr"] = iyr;
	keyMap["eyr"] = eyr;
	keyMap["hgt"] = hgt;
	keyMap["hcl"] = hcl;
	keyMap["ecl"] = ecl;
	keyMap["pid"] = pid;
	keyMap["cid"] = cid;
}

class Passport {
	public:
		Passport() {};
		void readLine(std::string line) {
			int start = 0;
			int end = 3;
			while (true) {
				std::string key = line.substr(start, end - start);
				start = end + 1;
				end = line.find(' ', end);
				bool lineEnd = end == std::string::npos;
				std::string info = lineEnd ? line.substr(start, line.size() - start) : line.substr(start, end - start);
				this->saveInfo(key, info);

				if (lineEnd) return;

				start = end + 1;
				end = start + 3;
			}
		}

		bool hasAllFields() {
			return (byr != -1 && iyr != -1 && eyr != -1 && hgt != "" && hcl != "" && ecl != "" && pid != "");
		}

		bool isValid() {
			if (!this->hasAllFields()) { return false; }

			return isBirthYearValid() && isIssueYearValid() && isExpirationYearValid() && isHeightValid() && isHairColorValid() && isEyeColorValid() && isPassportIdValid();
		}

	private:
		void saveInfo(std::string key, std::string info) {
			switch (keyMap[key])
			{
			case PassportKeys::byr:
				byr = std::stoi(info);
				break;
			case PassportKeys::iyr:
				iyr = std::stoi(info);
				break;
			case PassportKeys::eyr:
				eyr = std::stoi(info);
				break;
			case PassportKeys::hgt:
				hgt = info;
				break;
			case PassportKeys::hcl:
				hcl = info;
				break;
			case PassportKeys::ecl:
				ecl = info;
				break;
			case PassportKeys::pid:
				pid = info;
				break;
			case PassportKeys::cid:
				cid = info;
				break;
			default:
				break;
			}
		}

		bool isBirthYearValid() {
			bool valid = byr >= 1920 && byr <= 2002;
			return valid;
		}

		bool isIssueYearValid() {
			return iyr >= 2010 && iyr <= 2020;
		}

		bool isExpirationYearValid() {
			return eyr >= 2020 && eyr <= 2030;
		}

		bool isHeightValid() {
			std::string unit = hgt.substr(hgt.size() - 2, hgt.size());
			int value = std::stoi(hgt.substr(0, hgt.size() - 2));

			if (unit == "cm") {
				return value >= 150 && value <= 193;
			}
			else {
				return value >= 59 && value <= 76;
			}
			return false;
		}

		bool isHairColorValid() {
			std::string value = hcl.substr(1, hcl.size());
			if (hcl[0] == '#' && value.size() == 6) {
				std::stoi(value, 0, 16);
				return true;
			}
			return false;
		}

		bool isEyeColorValid() {
			return ecl == "amb" || ecl == "blu" || ecl == "brn" || ecl == "gry" || ecl == "grn" || ecl == "hzl" || ecl == "oth";
		}

		bool isPassportIdValid() {
			if (pid.size() == 9) {
				std::stoi(pid);
				return true;
			}
			return false;
		}

		int byr = -1;
		int iyr = -1;
		int eyr = -1;
		std::string hgt = "";
		std::string hcl = "";
		std::string ecl = "";
		std::string pid = "";
		std::string cid = "";
};

int day4() {
	std::vector<std::string> test{
		"ecl:gry pid:860033327 eyr:2020 hcl:z",
		"byr:1937 iyr:2017 cid:147 hgt:183cm",
		"",
		"iyr:2013 ecl:amb cid:350 eyr:2023 pid:028048884",
		"byr:1929 hcl:z",
		"",
		"hcl:#ae17e1 iyr:2013",
		"eyr:2024",
		"ecl:brn pid:760753108 byr:1931",
		"hgt:179cm",
		"",
		"hcl:#cfa07d eyr:2025 pid:166559648",
		"iyr:2011 ecl:brn hgt:59in",
	};

	std::vector<std::string> test2{
		"eyr:1972 cid:100",
		"hcl:#18171d ecl:amb hgt:170 pid:186cm iyr:2018 byr:1926",
		"",
		"iyr:2019",
		"hcl:#602927 eyr:1967 hgt:170cm",
		"ecl:grn pid:012533040 byr:1946",
		"",
		"hcl:dab227 iyr:2012",
		"ecl:brn hgt:182cm pid:021572410 eyr:2020 byr:1992 cid:277",
		"",
		"hgt:59cm ecl:zzz",
		"eyr:2038 hcl:74454a iyr:2023",
		"pid:3556412378 byr:2007",
		"",
		"pid:087499704 hgt:74in ecl:grn iyr:2012 eyr:2030 byr:1980",
		"hcl:#623a2f",
		"",
		"eyr:2029 ecl:blu cid:129 byr:1989",
		"iyr:2014 pid:896056539 hcl:#a97842 hgt:165cm",
		"",
		"hcl:#888785",
		"hgt:164cm byr:2001 iyr:2015 cid:88",
		"pid:545766238 ecl:hzl",
		"eyr:2022",
		"",
		"iyr:2010 hgt:158cm hcl:#b6652a ecl:blu byr:1944 eyr:2021 pid:093154719",
	};
	std::ifstream ifs("Day4Input.txt", std::ifstream::in);
	std::vector<std::string> input = read_input(ifs);

	initKeyMap();

	Passport* currentPassport = NULL;
	int valid = 0;
	int allFields = 0;
	int total = 0;
	for (std::string line : input) {
		if (currentPassport == NULL) {
			currentPassport = new Passport();
		}

		if (line == "") {
			total++;
			if (currentPassport->hasAllFields()) { allFields++; }
			if (currentPassport->isValid()) { valid++; }
			currentPassport = NULL;
		}
		else {
			currentPassport->readLine(line);
		}
	}
	total++;
	if (currentPassport->hasAllFields()) { allFields++; }
	if (currentPassport->isValid()) { valid++; }

	std::cout << "Passports with all required fields: " << allFields << std::endl;
	std::cout << "Passports valid: " << valid;

	return 0;
}

/*
* Output:
* Passports with all required fields: 216
* Passports valid: 150
*/