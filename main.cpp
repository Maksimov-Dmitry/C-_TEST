#include <iostream>
#include <vector>

#define EXIT_SUCCESS 0
#define INDEX_OUT_OF_RANGE 1

#define CMD_UPDATE '1'
#define CMD_DELETE '2'
#define CMD_INSERT '3'
#define CMD_PRINT  '4'


int add_string(std::vector<std::vector<std::string>>* strings, std::string string_to_add) {
    std::vector<std::string> fields;
    std::string field("");

    size_t string_counter = 0;
    for (size_t i = 0; i != string_to_add.size(); i++) {
        if (string_to_add[i] != '\t') {
            field += string_to_add[i];
        } else {
            fields.emplace_back(field);
            field = "";
        }
    }
    fields.emplace_back(field);
    strings->emplace_back(fields);

    return EXIT_SUCCESS;
}

int update_value(std::vector<std::vector<std::string>>* strings, size_t string_index, size_t field_index, std::string new_value) {
    if (string_index >= strings->size()) {
        return INDEX_OUT_OF_RANGE;
    }
    if (field_index >= (*strings)[string_index].size()) {
        return INDEX_OUT_OF_RANGE;
    }

    (*strings)[string_index][field_index] = new_value;

    return EXIT_SUCCESS;
}

int insert_value(std::vector<std::vector<std::string>>* strings, size_t string_index, size_t field_index, std::string new_value) {
    if (string_index >= strings->size()) {
        return INDEX_OUT_OF_RANGE;
    }
    if (field_index >= (*strings)[string_index].size()) {
        return INDEX_OUT_OF_RANGE;
    }

    size_t fields_size = (*strings)[string_index].size();

    auto it = (*strings)[string_index].begin();
    (*strings)[string_index].insert(it + field_index, new_value);

    return EXIT_SUCCESS;
}

int delete_value(std::vector<std::vector<std::string>>* strings, size_t string_index, size_t field_index) {
    if (string_index >= strings->size()) {
        return INDEX_OUT_OF_RANGE;
    }
    if (field_index >= (*strings)[string_index].size()) {
        return INDEX_OUT_OF_RANGE;
    }

    auto it = (*strings)[string_index].begin();
    (*strings)[string_index].erase(it + field_index, it + field_index + 1);
}

int print_strings(std::vector<std::vector<std::string>>* strings) {
    for (auto& fields : *strings) {
        for (auto& field : fields) {
            std::cout << field << '\t';
        }
        std::cout << std::endl;
    }

    return EXIT_SUCCESS;
}

int main(int argc, char const *argv[]) {
    std::cout << "Please enter strings, CTRL^D for end input" << std::endl;
    std::string input_str("");
    std::vector<std::vector<std::string>> strings;
    while (std::cin) {
        std::getline(std::cin, input_str);
        add_string(&strings, input_str);
    }
    std::cin.clear();

    char command = 0;
    std::cout << "Enter action:" << std::endl;
    std::cout << "1   :  UPDATE" << std::endl;
    std::cout << "2   :  DELETE" << std::endl;
    std::cout << "3   :  INSERT" << std::endl;
    std::cout << "4   :  PRINT" << std::endl;
    while (std::cin >> command) {

        if (command == '1') {
            std::cout << "UPDATE" << std::endl;
            size_t string_index = 0;
            std::cout << "Enter string index:" << std::endl;
            std::cin >> string_index;

            size_t field_index = 0;
            std::cout << "Enter field index:" << std::endl;
            std::cin >> field_index;

            std::string new_field_value("");
            std::cout << "Enter new field value:" << std::endl;
            std::cin >> new_field_value;

            update_value(&strings, string_index, field_index, new_field_value);
        }

        if (command == '2') {
            std::cout << "DELETE" << std::endl;
            size_t string_index = 0;
            std::cout << "Enter string index:" << std::endl;
            std::cin >> string_index;

            size_t field_index = 0;
            std::cout << "Enter field index:" << std::endl;
            std::cin >> field_index;

            delete_value(&strings, string_index, field_index);
        }

        if (command == '3') {
            std::cout << "INSERT" << std::endl;

            size_t string_index = 0;
            std::cout << "Enter string index:" << std::endl;
            std::cin >> string_index;

            size_t field_index = 0;
            std::cout << "Enter field index:" << std::endl;
            std::cin >> field_index;

            std::string new_field_value("");
            std::cout << "Enter new field value:" << std::endl;
            std::cin >> new_field_value;

            insert_value(&strings, string_index, field_index, new_field_value);
        }

        if (command == '4') {
            std::cout << "PRINT" << std::endl;
            print_strings(&strings);
        }
        std::cin.clear();
        std::cout << "Enter action:" << std::endl;
        std::cout << "1   :  UPDATE" << std::endl;
        std::cout << "2   :  DELETE" << std::endl;
        std::cout << "3   :  INSERT" << std::endl;
        std::cout << "4   :  PRINT" << std::endl;
        command = '0';
    }

    return EXIT_SUCCESS;
}