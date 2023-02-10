#include <iostream>
#include <climits>
#include "admin.h"

// The function opens the file, inserts the content line by line into the "data" vector,
// drops the phone numbers into the "phone" vector,
// puts numbers representing the lengths of all parameters into the "lengths" vector, 
// closes the file, greets the user, finally calls the show_main_menu() function
void Admin::start()
{   
	fin.open("phone_book.txt", std::ios::in);
    if (!fin.is_open()) {
        std::cout << std::endl << "The file \"phone_book.txt\" is not opened, please, try again.";
        exit(0);
    }
    else {
		std::string line{}; // to store the information line by line
        Contact obj;
        while (std::getline(fin, line)) {
			data.push_back(line);
            int size{};
            obj = string_to_Contact(line);
            phone.push_back(obj.get_phone_number());
            lengths.push_back(obj.get_name().size());
            lengths.push_back(obj.get_surname().size());
            lengths.push_back(obj.get_phone_number().size());
            lengths.push_back(obj.get_address().size());
            for (int i{}; i < lengths.size(); ++i) {
                if (lengths[i] > size) {
                    size = lengths[i];
                }
            }
            m_size = size > m_size ? size : m_size;            
		}
		fout.close();
		std::cout << std::endl << "========== WELLCOME ==========" << std::endl;
		show_main_menu();
    }
}

// the function presents to the user the actions (with corresponding codes) that the program supports, 
// accepts code from user, checks for validity,
// finally calls the menu_functions(short) function
void Admin::show_main_menu()
{
    std::cout   << std::endl << std::endl 
                << "==========================" << std::endl;
    std::cout   << "[0]______show all contacts\n"
                << "[1]――――――――add new contact\n"  								
                << "[2]―――――――――――edit contact\n"				
                << "[3]―――――――――remove contact\n"				
                << "[4]―――――――――search contact\n"
                << "[5]――――――exit from program\n"
                << "==========================\n"
                << "\nyour choise: ___\b\b";
    int key;
    do{       
        if(!(std::cin >> key) || (key < 0 || key > 5))
        {
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
            std::cerr << std::endl << "your input is not correct, please, input an integer from [0;5].\n";
        }        
    }while (key < 0 || key > 5);
    menu_functions(key);
}

// organizes the completion of the project
void Admin::exit_from_program()
{
	std::cout << std::endl << "are you sure, you really want to exit from program?(y / n) \n";
	std::string key;
	do {
		std::cin >> key;	
		if (key != "y" && key != "n"){
			std::cout << "your input is not correct. Please, input 'y' or 'n'\n";	
		}
	}while(key != "y" && key != "n");				
		if(key == "y"){
			std::cout << "\n\n===========  BYE  ==========\n\n";
			exit(0);
		}else if(key == "n"){
			show_main_menu();					
		}
}

// receiving the code from user calls the corresponding function
void Admin::menu_functions(short key)
{
    switch(key){
        case 0: {show_all_contacts();}
            break;
        case 1: {add_new_contact();}
            break;		
        case 2: {std::cout << std::endl << "Please, input the contact name to edit" << std::endl;
            std::string name;
            std::cin.ignore();
            std::getline(std::cin, name);
            find_to_edit_contact(name);}
            break;
        case 3: {std::cout << std::endl << "Please, input the contact name to remove :  "   ;
            std::string name;
            std::cin.ignore();
            std::getline(std::cin, name);
            find_to_remove_contact(name);}
            break;
        case 4: {find_to_show_contact();}
            break;
        case 5: { exit_from_program(); }
            break;
        default :{std::cout << std::endl << "your input is not correct. Please, input numbers from diapazone [0;5]" << std::endl;
            show_main_menu();
        }	
    }
}

// Parsing the string gets an object of type Contact and returns that object
Contact Admin::string_to_Contact(std::string str)
{
    Contact new_obj;
    int current_index;
    std::string name{};
    std::string surname{};
    std::string phone_number{};
    std::string address{};
    for (int i{7}; str[i] != '|'; ++i) {
        name += str[i];
        current_index = i + 15;
    }
    new_obj.set_name(name);
    for (int i{current_index}; str[i] != '|'; ++i) {
        surname += str[i];
        current_index = i + 20;
    }
    new_obj.set_surname(surname);
    for (int i{current_index}; str[i] != '|'; ++i) {
        phone_number += str[i];
        current_index = i + 15;
    }
    new_obj.set_phone_number(phone_number);
    for (int i{current_index}; str[i] != '|'; ++i) {
        address += str[i];
    }
    new_obj.set_address(address);
    return new_obj;
}

// Converts an object of type Contact to a string and returns that string
std::string Admin::Contact_to_string(Contact& obj)
{
    std::string str_contact{};
    str_contact += "name : ";
    str_contact += obj.get_name();
    str_contact += "|   surname : ";
    str_contact += obj.get_surname();
    str_contact += "|   phone_number : ";
    str_contact += obj.get_phone_number();
    str_contact += "|   address : ";
    str_contact += obj.get_address();
    str_contact += "|";
    return str_contact;
}

// Displays all contact data in the console as a table
void Admin::show_all_contacts()
{   
    Contact obj;
    std::string table{};
    std::cout << std::endl;
    for (int i{} ; i < 4 * (m_size + 2) + 5; ++ i) {
        table += "_";
    }
    table += "\n|";
    for (int j{}; j < 4; ++j) {
        for (int i{} ; i < m_size + 2; ++ i) {
            table += " ";
        }
        table += "|";
    }
    table += "\n|";
    for (int i{}; i < (m_size - 4) / 2 + 1; ++i) {
        table += " ";
    }
    table += "name";
    for (int i{}; i < m_size - 4 - (m_size - 4) / 2 + 1; ++i) {
        table += " ";
    }
    table += "|";
    for (int i{}; i < (m_size - 7) / 2 + 1; ++i) {
        table += " ";
    }
    table += "surname";
    for (int i{}; i < m_size - 7 - (m_size - 7) / 2 + 1; ++i) {
        table += " ";
    }
    table += "|";
    for (int i{}; i < (m_size - 12) / 2 + 1; ++i) {
        table += " ";
    }
    table += "phone number";
    for (int i{}; i < m_size - 12 - (m_size - 12) / 2 + 1; ++i) {
        table += " ";
    }
    table += "|";
    for (int i{}; i < (m_size - 7) / 2 + 1; ++i) {
        table += " ";
    }
    table += "address";
    for (int i{}; i < m_size - 7 - (m_size - 7) / 2 + 1; ++i) {
        table += " ";
    }
    table += "|\n|";
    for (int j{}; j < 4; ++j) {
        for (int i{} ; i < m_size + 2; ++ i) {
            table += "_";
        }
        table += "|";
    }
    table += "\n|";
    for (int j{}; j < 4; ++j) {
        for (int i{} ; i < m_size + 2; ++ i) {
            table += " ";
        }
        table += "|";
    }
    std::cout << table;
    std::cout << std::endl;
    for (int i{}; i < data.size(); ++i) {
        obj = string_to_Contact(data[i]);
        Contact_to_short_string(obj);
    }
    std::cout << "|";
    for (int j{}; j < 4; ++j) {
        for (int i{} ; i < m_size + 2; ++ i) {
            std::cout << "_";
        }
        std::cout << "|";
    }
    std::cout << std::endl;
    show_main_menu();
}

// The function receives an object of type Contact, converts it to a table view string
void Admin::Contact_to_short_string(Contact obj)
{
    int new_size = m_size;
    for (int i{}; i < lengths.size(); ++i) {
        if (lengths[i] > new_size) {
            new_size = lengths[i];
        }
    }
    m_size = new_size;
    std::string str_contact{};
    str_contact += "| ";
    str_contact += obj.get_name();
    for (int i{}; i < m_size - obj.get_name().size() + 1; ++i) {
        str_contact += " ";
    }
    str_contact += "| ";
    str_contact += obj.get_surname();
    for (int i{}; i < m_size - obj.get_surname().size() + 1; ++i) {
        str_contact += " ";
    }
    str_contact += "| ";
    str_contact += obj.get_phone_number();
    for (int i{}; i < m_size - obj.get_phone_number().size() + 1; ++i) {
        str_contact += " ";
    }
    str_contact += "| ";
    str_contact += obj.get_address();
    for (int i{}; i < m_size - obj.get_address().size() + 1; ++i) {
        str_contact += " ";
    }
    str_contact += "|";
    std::cout << str_contact << std::endl;    
}

// The function creates a new Contact object, converts it to a string, adds both to the data vector and to the file
void Admin::add_new_contact()
{
    tmpfout.open("tmp.txt", std::ios::out | std::ios::app);
    if (!tmpfout.is_open()) {
        std::cout << std::endl << "file handling error" <<std::endl;
    }
    else {
        Contact new_contact = create_contact();
        std::string string_contact = Contact_to_string(new_contact);
        data.push_back(string_contact);
        for (int i{}; i < data.size(); ++i) {
            tmpfout << data[i] << std::endl;
        }
        remove("phone_book.txt");
        rename("tmp.txt", "phone_book.txt");
        tmpfout.close();
        std::cout << std::endl << "contact created and saved successfully" << std::endl;	
    }
    show_main_menu();
}

// The function creates an object of type Contact and after checking
// the appropriate parameters given by the user, sets the contact
Contact Admin::create_contact()
{
    Contact contact;    
    std::string name;
    do {
        std::cout << std::endl << "Enter the name of contact  :  ";
        std::cin.ignore();
        std::getline(std::cin, name);
    } while (!check_name(name));    
    contact.set_name(name);
    lengths.push_back(name.size());
    if (name.size() > m_size) {
        m_size = name.size();
    }
    std::string surname;
    do {
        std::cout << std::endl << "Enter the surname of contact  :  ";
        std::getline(std::cin, surname);
    } while (!check_surname(surname));
    contact.set_surname(surname);
    lengths.push_back(surname.size()); 
    if (surname.size() > m_size) {
        m_size = surname.size();
    }
    std::string phone_number;
    do {
        std::cout << std::endl << "Enter the phone_number of contact  :  ";
        std::getline(std::cin, phone_number);
    } while (!check_phone_number(phone_number));
    phone.push_back(phone_number);
    contact.set_phone_number(phone_number); 
    lengths.push_back(phone_number.size());
    if (phone_number.size() > m_size) {
        m_size = phone_number.size();
    }
    std::string address;
    do {
        std::cout << std::endl << "Enter the address of contact  :  ";
        std::getline(std::cin, address);
    } while (!check_address(address));
    contact.set_address(address);
    lengths.push_back(address.size());
    if (address.size() > m_size) {
        m_size = address.size();
    }
    return contact;
}

// Gets a string representing the name, checks for validation, returns the appropriate boolean value
bool Admin::check_name(std::string& name) const
{
    // prevent entering more than 30 characters
    if (name.length() > 31) {
        std::cout << std::endl << "The length of the entered name must be less or aqual to 30. Please enter a shorter name" << std::endl;
        return false;
    } 
    // The entered name must consist of only Latin letters. It is also allowed to use a space.
    for (int i{}; i < name.length(); ++i) {
        if (!(name[i] >= 'a' && name[i] <= 'z') 
                && !(name[i] >= 'A' && name[i] <= 'Z') 
                && name[i] != ' ') {
            std::cout << std::endl << "Your input is not valid. Please, input the correct name." << std::endl;
            return false;
        }
    }        
    // Prevent input of only spaces or an empty string
    bool is_empty_name{true};
    for (int i{}; i < name.length(); ++i) {
        if (name.length() > 0 && name[i] != ' ') {
            is_empty_name = false;
            break;
        }
    }
    if (is_empty_name) {
        std::cout << std::endl << "Please, input any correct name." << std::endl;
        return false;
    }
    return true;
}

// Gets a string representing the surname, checks for validation, returns the appropriate boolean value
bool Admin::check_surname(std::string& surname) const
{
    // prevent entering more than 30 characters
    if (surname.length() > 30) {
        std::cout << std::endl << "The length of the entered surname must be less or aqual to 30. Please enter a shorter surname" << std::endl;
        return false;
    }
    // The entered name must consist of only Latin letters. It is also allowed to use a space.
    for (int i{}; i < surname.length(); ++i) {
        if (!(surname[i] >= 'a' && surname[i] <= 'z') 
                && !(surname[i] >= 'A' && surname[i] <= 'Z') 
                && surname[i] != ' ') {
            std::cout << std::endl << "Your input is not valid. Please, input the correct surname." << std::endl;
            return false;
        }
    }        
    // Prevent input of only spaces or an empty string
    bool is_empty_surname{true};
    for (int i{}; i < surname.length(); ++i) {
        if (surname.length() > 0 && surname[i] != ' ') {
            is_empty_surname = false;
            break;
        }
    }
    if (is_empty_surname) {
        std::cout << std::endl << "Please, input any correct surname." << std::endl;
        return false;
    }
    return true;
}

// Gets a string representing the phone number, checks for validation, returns the appropriate boolean value
bool Admin::check_phone_number(std::string& phone_number) const
{
    // prevent entering more than 30 characters
    if (phone_number.length() > 30) {
        std::cout << std::endl << "The length of the entered number must be less or aqual to 30. Please enter a shorter number" << std::endl;
        return false;
    }
    // The entered number must consist of digits only
    for (int i{}; i < phone_number.length(); ++i) {
        if (!(phone_number[i] >= '0' && phone_number[i] <= '9')) {
            std::cout << std::endl << "Your input is not valid. Please, input the correct phone number." << std::endl;
            return false;
        }
    }
    // The number must not be repeated
    for (int i{}; i < phone.size(); ++i) {
        if (phone[i] == phone_number) {
            std::cout << std::endl << "that phone_numer already exists. Please, input another number" << std::endl;
            return false;
        }
    }
    return true;
}

// Gets a string representing the address, checks for validation, returns the appropriate boolean value
bool Admin::check_address(std::string& address) const
{
    // prevent entering more than 30 characters
    if (address.length() > 30) {
        std::cout << std::endl << "The length of the entered address must be less or aqual to 30. Please enter a shorter address" << std::endl;
        return false;
    }
    // The address must contain Latin letters, numbers, and some special symbols.
    // An empty or spaces-only string is also accepted
    for (int i{}; i < address.length(); ++i) {
        if (!(address[i] >= 'a' && address[i] <= 'z') 
                && !(address[i] >= 'A' && address[i] <= 'Z') 
                && !(address[i] >= '0' && address[i] <= '9') 
                && address[i] != '/' && address[i] != '-' 
                && address[i] != '_' && address[i] != ' ') {
            std::cout << std::endl << "Your input is not valid. Please, input the correct address." << std::endl;
            return false;
        }
    }
    return true;    
}

// the function enables the user to find the contact by providing appropriate parameters
void Admin::find_to_edit_contact(std::string& name)
{
    std::vector<std::string> same_name_vec{}; // for contacts with the same name
    std::vector<std::string> same_surname_vec{}; // for contacts with the same first and last name
    int contact_count{}; // number of contacts found
    for (int i{}; i < data.size(); ++i) { // loop over all data elements
        Contact obj = string_to_Contact(data[i]);
        if (obj.get_name() == name) {
            contact_count++; // number of matches
            same_name_vec.push_back(data[i]);
        }
    }
    for (int i{}; i < same_name_vec.size(); ++i) {
        Contact obj = string_to_Contact(same_name_vec[i]);
        Contact_to_short_string(obj);
    }
    if (!contact_count) {
        std::cout << std::endl << "No contact found with that name!!" << std::endl;
        show_main_menu();
    }
    else if (contact_count == 1) { // if we have exactly one match
        edit_contact(same_name_vec[0]);
    }
    else { // in case of more than one match
        std::cout << std::endl << "It is not clear which contact you want to change.\n\nPLease, input the surname  :  ";
        std::string surname;
        do {
            std::getline(std::cin, surname);
            contact_count = 0;
            for (int i{}; i < same_name_vec.size(); ++i) {
                Contact obj = string_to_Contact(same_name_vec[i]);
                if (obj.get_surname() == surname) {
                    contact_count++; // number of matches
                    same_surname_vec.push_back(same_name_vec[i]);
                }
            }
            for (int i{}; i < same_surname_vec.size(); ++i) {
                Contact obj = string_to_Contact(same_surname_vec[i]);
                Contact_to_short_string(obj);
            }
            if (!contact_count) {
                std::cout << std::endl << "No contact found with that surname!!" << std::endl;
                for (int i{}; i < same_name_vec.size(); ++i) {
                    std::cout << same_name_vec[i] << std::endl;
                }
                std::cout << std::endl << "choose and input surname again to edit the correct conact." << std::endl;
            }
        } while (!contact_count);
        if (contact_count == 1) {
            edit_contact(same_surname_vec[0]);
        }
        else { // in case of more than one match
            int contact_index; // The index of the contact to look up in the same_surname_vec vector
            std::cout << std::endl << "again it is not clear which contact you want to change.\n\nPLease, input the phone_number  :  ";
            std::string phone_number{};
            do {
                std::cin >> phone_number;
                    contact_count = 0;
                    for (int i{}; i < same_surname_vec.size(); ++i) {
                    Contact obj = string_to_Contact(same_surname_vec[i]);
                        if (obj.get_phone_number() == phone_number) {
                            contact_count++;
                            std::cout << same_surname_vec[i] << std::endl;
                            contact_index = i; // we fix the index of the found contact
                        }
                    }
                    if (!contact_count) {
                        std::cout << std::endl << "No contact found with that phone_number!!" << std::endl;
                        for (int i{}; i < same_surname_vec.size(); ++i) {
                            std::cout << same_surname_vec[i] << std::endl;
                        }
                        std::cout << std::endl << "choose and input phone_number again to edit the correct conact.\n" << std::endl;
                    }
            }while (!contact_count);
            if (contact_count == 1) {
                edit_contact(same_surname_vec[contact_index]);
            }
            // more than one match for a phone number is excluded
        }
    }
}

// function allows the user to select what he wants to change in a given contact and calls the appropriate function
void Admin::edit_contact(std::string& str)
{
    std::cout   << "What do you want to change?\n\n";
    std::cout   << "'n'_____________edit name" << std::endl
                << "'s'__________edit surname" << std::endl
                << "'p'_____edit phone_number" << std::endl
                << "'a'__________edit address" << std::endl
                << "'x'_____________main menu" << std::endl <<
    std::endl   << "your choice  ։  ";
    char symbol;
    std::cin >> symbol;
    std::cin.ignore(INT_MAX, '\n');
    switch (symbol) {
        case 'n': { edit_name(str); }
            break;                
        case 's' : { edit_surname(str); }
            break;
        case 'p' : { edit_phone_number(str); }
            break;
        case 'a' : { edit_address(str); }
            break;
        case 'x' : { show_main_menu(); }
            break;
        default : { 
            std::cout << std::endl << "your input is not correct.";
            show_main_menu();
        }
    }
}

// changes contact name, commits change to file
void Admin::edit_name(std::string& str)
{
    tmpfout.open("tmp.txt", std::ios::out | std::ios::app);
    if (!tmpfout.is_open()) {
        std::cout << std::endl << "file handling error!!!" << std::endl;
        edit_contact(str);
    }
    else {
        std::string new_name;
        do {
            std::cout << std::endl << "Enter the name of contact  :  ";
            std::getline(std::cin, new_name);
        } while (!check_name(new_name));    
        // after checking the validation of the new name, we turn the string into an object
        Contact contact = string_to_Contact(str);
        // we delete the data of the contact's old name from the "lengths" vector
        for (int i{}; i < lengths.size(); ++i) {
            if (lengths[i] == contact.get_name().size()) {
                lengths.erase(lengths.begin() + i);
                break;
            }
        }
        lengths.push_back(new_name.size());
        // if we deleted the data with the maximum value, we find the next maximum
        if (m_size == contact.get_name().size()) {
            int new_size = 14;
            for (int i{}; i < lengths.size(); ++i) {
                if (lengths[i] > new_size) {
                    new_size = lengths[i];
                }
            }
            m_size = new_size;
        }
        // change the name
        contact.set_name(new_name);
        std::string str_contact = Contact_to_string(contact); // convert back to string
        // delete the old contact from data
        for (int i{}; i < data.size(); ++i) {
            if (str == data[i]) {
                data.erase(data.begin() + i);
            }
        }
        // insert the updated one into the data vector
        data.push_back(str_contact);
        for (int i{}; i < data.size(); ++i) {
            tmpfout << data[i] << std::endl;
        }
        remove("phone_book.txt");
        rename("tmp.txt", "phone_book.txt");
        tmpfout.close();
        std::cout << std::endl << "name updated." << std::endl << std::endl;
        edit_contact(str_contact); // give the opportunity to change the parameter again
    }
}

// changes contact surname, commits change to file
void Admin::edit_surname(std::string& str)
{
    tmpfout.open("tmp.txt", std::ios::out | std::ios::app); 
    if (!tmpfout.is_open()) {
        std::cout << std::endl <<"file handling error!!!" << std::endl;
        edit_contact(str);
    }
    else {
        std::string new_surname;
        do {
            std::cout << std::endl << "Enter new surname  :  ";
            std::getline(std::cin, new_surname);
        } while (!check_name(new_surname)); 
	// after checking the validation of the new surname, we turn the string into an object
        Contact contact = string_to_Contact(str);
        
        // we delete the data of the contact's old surname from the "lengths" vector
        for (int i{}; i < lengths.size(); ++i) {
            if (lengths[i] == contact.get_surname().size()) {
                lengths.erase(lengths.begin() + i);
                break;
            }
        }
        // drop the length of the new data into the corresponding vector
        lengths.push_back(new_surname.size());
        // if we deleted the data with the maximum value, we find the next maximum
        if (m_size == contact.get_surname().size()) {
            int new_size = 14;
            for (int i{}; i < lengths.size(); ++i) {
                if (lengths[i] > new_size) {
                    new_size = lengths[i];
                }
            }
            m_size = new_size;
        }
        contact.set_surname(new_surname);
        std::string str_contact = Contact_to_string(contact); // convert back to string
        // delete the old contact from data
        for (int i{}; i < data.size(); ++i) {
            if (str == data[i]) {
                data.erase(data.begin() + i);
            }
        }
        // insert the updated one into the data vector
        data.push_back(str_contact);   
        for (int i{}; i < data.size(); ++i) {
            tmpfout << data[i] << std::endl;
        }
        remove("phone_book.txt");
        rename("tmp.txt", "phone_book.txt");
        tmpfout.close();
        std::cout << std::endl << "surname updated." << std::endl << std::endl;
        edit_contact(str_contact); // give the opportunity to change the parameter again
    }
}

// changes contact phone number, commits change to file
void Admin::edit_phone_number(std::string& str)
{
    tmpfout.open("tmp.txt", std::ios::out | std::ios::app);
    if (!tmpfout.is_open()) {
        std::cout << std::endl << "file handling error!!!" << std::endl;
        edit_contact(str);
    }
    else {
        Contact contact = string_to_Contact(str);
        std::string new_phone_number;
        do {
            std::cout << std::endl << "Enter new phone number  :  ";
            std::getline(std::cin, new_phone_number);
        } while (!check_phone_number(new_phone_number));
        // delete the old number from the vector
        for (int i{}; i < phone.size(); ++i) {
            if (contact.get_phone_number() == phone[i]) {
                phone.erase(phone.begin() + i);
            }
        } 
        // delete the length of the old phone number from the "lengths" vector
        for (int i{}; i < lengths.size(); ++i) {
            if (lengths[i] == contact.get_phone_number().size()) {
                lengths.erase(lengths.begin() + i);
                break;
            }
        }
        // drop the length of the new data into the corresponding vector
        lengths.push_back(new_phone_number.size());
        // if we deleted the data with the maximum value, we find the next maximum
        if (m_size == contact.get_phone_number().size()) {
            int new_size = 14;
            for (int i{}; i < lengths.size(); ++i) {
                new_size = lengths[i] > new_size ? lengths[i] : new_size;
            }
            m_size = new_size;
        }
        phone.push_back(new_phone_number);
        contact.set_phone_number(new_phone_number); 
        std::string str_contact = Contact_to_string(contact); // convert back to string
        // delete the old contact from data
        for (int i{}; i < data.size(); ++i) {
            if (str == data[i]) {
                data.erase(data.begin() + i);
            }
        }
        // put the string of the updated contact into the data vector
        data.push_back(str_contact);        
        for (int i{}; i < data.size(); ++i) {
            tmpfout << data[i] << std::endl;
        }
        remove("phone_book.txt");
        rename("tmp.txt", "phone_book.txt");
        tmpfout.close();
        std::cout << std::endl << "phone_number updated." << std::endl << std::endl;
        edit_contact(str_contact); // give the opportunity to change the parameter again
    }
}

// changes contact address, commits change to file
void Admin::edit_address(std::string& str)
{
    tmpfout.open("tmp.txt", std::ios::out | std::ios::app);
    if (!tmpfout.is_open()) {
        std::cout << std::endl << "file handling error!!!" << std::endl;
        edit_contact(str);
    }
    else {
        std::string new_address;
        do {
            std::cout << std::endl << "Enter new address  :  ";
            std::getline(std::cin, new_address);
        } while (!check_address(new_address));
        Contact contact = string_to_Contact(str);
        // delete the length of the old surname from the lengths vector
        for (int i{}; i < lengths.size(); ++i) {
            if (lengths[i] == contact.get_address().size()) {
                lengths.erase(lengths.begin() + i);
                break;
            }
        }
        // drop the length of the new data into the corresponding vector
        lengths.push_back(new_address.size());
        // if we deleted the data with the maximum value, we find the next maximum
        if (m_size == contact.get_address().size()) {
            int new_size = 14;
            for (int i{}; i < lengths.size(); ++i) {
                new_size = lengths[i] > new_size ? lengths[i] : new_size;
            }
            m_size = new_size;
        }
        contact.set_address(new_address);
        std::string str_contact = Contact_to_string(contact); // convert back to string
        // delete the old contact from data
        for (int i{}; i < data.size(); ++i) {
            if (str == data[i]) {
                data.erase(data.begin() + i);
            }
        }
        // insert the updated one into the data vector
        data.push_back(str_contact);    
        for (int i{}; i < data.size(); ++i) {
            tmpfout << data[i] << std::endl;
        }
        remove("phone_book.txt");
        rename("tmp.txt", "phone_book.txt");
        tmpfout.close();
        std::cout << std::endl << "address updated." << std::endl << std::endl;
        edit_contact(str_contact); // give the opportunity to change the parameter again
    }
}

// function finds the correct contact, sends to delete
void Admin::find_to_remove_contact(std::string& name)
{
    std::vector<std::string> same_name_vec{}; // for contacts with the same name
    std::vector<std::string> same_surname_vec{}; // for contacts with the same first and last name
    int contact_count{};
    std::string contact_name{};
    for (int i{}; i < data.size(); ++i) { // loop over all elements of "data"
        Contact obj = string_to_Contact(data[i]);
        if (obj.get_name() == name) { // compares with the entered name
            contact_count++; // number of matches
            same_name_vec.push_back(data[i]);
        }
    }
    for (int i{}; i < same_name_vec.size(); ++i) {
        Contact obj = string_to_Contact(same_name_vec[i]);
        Contact_to_short_string(obj);
    }
    if (!contact_count) {
        std::cout << std::endl << "No contact found with that name!!" << std::endl;
        show_main_menu();
    }
    else if (contact_count == 1) { // if we have exactly one match
        remove_contact(same_name_vec[0]);
    }
    else {//if (contact_count > 1)
        std::cout << std::endl << "It is not clear which contact you want to remove.\n\nPLease, input the surname  :  ";
        std::string surname;
        do {
            std::getline(std::cin, surname);
            contact_count = 0;
            for (int i{}; i < same_name_vec.size(); ++i) {
                Contact obj = string_to_Contact(same_name_vec[i]);
                if (obj.get_surname() == surname) {
                    contact_count++; // number of matches
                    same_surname_vec.push_back(same_name_vec[i]);
                }
            }
            std::cout << std::endl;
            for (int i{}; i < same_surname_vec.size(); ++i) {
                Contact obj = string_to_Contact(same_surname_vec[i]);
                Contact_to_short_string(obj);
            }
            if (!contact_count) {
                std::cout << std::endl << "No contact found with that surname!!" << std::endl;
                for (int i{}; i < same_name_vec.size(); ++i) {
                    std::cout << same_name_vec[i] << std::endl;
                }
                std::cout << std::endl << "choose and input surname again to remove the correct contact." << std::endl;
            }
        } while (!contact_count);
        if (contact_count == 1) {
            remove_contact(same_surname_vec[0]);
        }
        else { //  if (contact_count > 1)
            int contact_index; // the index of the contact to be searched for in the same_surname vec vector
            std::cout << std::endl << "again it is not clear which contact you want to remove.\n\nPLease, input the phone_number  :  ";
            std::string phone_number{};
            do {
                std::cin >> phone_number;
                contact_count = 0;
                for (int i{}; i < same_surname_vec.size(); ++i) {
                    Contact obj = string_to_Contact(same_surname_vec[i]);
                    if (obj.get_phone_number() == phone_number) {
                        contact_count++;
                        std::cout << same_surname_vec[i] << std::endl;
                        contact_index = i; // found the contact index
                    }
                }
                if (!contact_count) {
                    std::cout << std::endl << "No contact found with that phone_number!!" << std::endl;
                    for (int i{}; i < same_surname_vec.size(); ++i) {
                        std::cout << same_surname_vec[i] << std::endl;
                    }
                    std::cout << std::endl << "choose and input phone_number again to remove the correct conact." << std::endl;
                }
            }while (!contact_count);
            if (contact_count == 1) {
                remove_contact(same_surname_vec[contact_index]);
            }
            // more than one match for a phone number is excluded
        }
    }
}

// the function deletes the passed contact from the "data" vector,
// also deletes it from the file, and deletes the phone number from the phone
void Admin::remove_contact(std::string& str)
{
    tmpfout.open("tmp.txt", std::ios::out | std::ios::app);
    if (!tmpfout.is_open()) {
        std::cout << "file handling error!!!" << std::endl;
        show_main_menu();
    }
    else {
        for (int i{}; i < data.size(); ++i) {
            if (str == data[i]) {
                data.erase(data.begin() + i);
            }
        }
        Contact obj = string_to_Contact(str);
        for (int i{}; i < phone.size(); ++i) {
            if (obj.get_phone_number() == phone[i]) {
                phone.erase(phone.begin() + i);
                break;
            }
        }
        for (int i{}; i < lengths.size(); ++i) {
            if (lengths[i] == obj.get_name().size()) {
                lengths.erase(lengths.begin() + i);
                break;
            }
        }
        // if we deleted the data with the maximum value, we find the next maximum
        if (m_size == obj.get_name().size()) {
            int new_size = 0;
            for (int i{}; i < lengths.size(); ++i) {
                new_size = lengths[i] > new_size ? lengths[i] : new_size;
            }
            m_size = new_size;
        }
        for (int i{}; i < lengths.size(); ++i) {
            if (lengths[i] == obj.get_surname().size()) {
                lengths.erase(lengths.begin() + i);
                break;
            }
        }
        // if we deleted the data with the maximum value, we find the next maximum
        if (m_size == obj.get_surname().size()) {
            int new_size = 0;
            for (int i{}; i < lengths.size(); ++i) {
                new_size = lengths[i] > new_size ? lengths[i] : new_size;
            }
            m_size = new_size;
        }
        for (int i{}; i < lengths.size(); ++i) {
            if (lengths[i] == obj.get_phone_number().size()) {
                lengths.erase(lengths.begin() + i);
                break;
            }
        }
        // if we deleted the data with the maximum value, we find the next maximum
        if (m_size == obj.get_phone_number().size()) {
            int new_size = 0;
            for (int i{}; i < lengths.size(); ++i) {
                new_size = lengths[i] > new_size ? lengths[i] : new_size;
            }
            m_size = new_size;
        }
        for (int i{}; i < lengths.size(); ++i) {
            if (lengths[i] == obj.get_address().size()) {
                lengths.erase(lengths.begin() + i);
                break;
            }
        }
        // if we deleted the data with the maximum value, we find the next maximum
        if (m_size == obj.get_address().size()) {
            int new_size = 0;
            for (int i{}; i < lengths.size(); ++i) {
                new_size = lengths[i] > new_size ? lengths[i] : new_size;
            }
            m_size = new_size;
        }
        for (int i{}; i < data.size(); ++i) {
            tmpfout << data[i] << std::endl;
        }
        remove("phone_book.txt");
        rename("tmp.txt", "phone_book.txt");
    }
    tmpfout.close();
    std::cout << std::endl << "contact removed saccessfully!!" << std::endl << std::endl;
    show_main_menu();
}

// Allows the user to select the criteria by which to find the contact
void Admin::find_to_show_contact()
{
    std::cout << "\nwhat do you want to find the contact by?" << std::endl << std::endl;
    std::cout << "=========================" << std::endl
              << "'n'_______________by name" << std::endl
              << "'s'____________by surname" << std::endl
              << "'p'_______by phone_number" << std::endl
              << "'a'____________by address" << std::endl
              << "'x'_______go to main menu" << std::endl
              << "=========================" << std::endl <<
    std::endl << "your choise  :  ";
    char symbol;
    std::cin >> symbol;
    std::cin.ignore(INT_MAX, '\n');
    switch (symbol) {
        case 'n': { show_by_name(); }
            break;                
        case 's' : { show_by_surname(); }
            break;
        case 'p' : { show_by_phone_number(); }
            break;
        case 'a' : { show_by_address(); }
            break;
        case 'x' : { show_main_menu(); }
            break;
        default : {
            std::cout << std::endl << "your input is not correct." << std::endl;
        }
    }
    show_main_menu();
}

// The function displays all contacts whose name matches the entered name
void Admin::show_by_name()
{
    std::cout << std::endl << "please, input contact name  :  ";
    std::string name;
    bool find;
    do {
        find = false;
        std::getline(std::cin, name);
        std::cout << std::endl;
        for (int i{}; i < data.size(); ++i) {
           Contact obj = string_to_Contact(data[i]);
           if (obj.get_name() == name) {
               find = true;
               Contact_to_short_string(obj);
           }
        }
        if (!find) {
            std::cout << std::endl << "no contact found with that name. Please, input another name  :  ";
        }
    }while(!find); 
}

// The function displays all contacts whose surname matches the entered surname
void Admin::show_by_surname()
{
    std::cout << std::endl <<"please, input contact surname  :  ";
    std::string surname;
    bool find;
    do {
        find = false;
        std::getline(std::cin, surname);
        std::cout << std::endl;
        for (int i{}; i < data.size(); ++i) {
           Contact obj = string_to_Contact(data[i]);
           if (obj.get_surname() == surname) {
               find = true;
               Contact_to_short_string(obj);
           }
        }
        if (!find) {
            std::cout << std::endl << "no contact found with that surname. Please, input the another surname  :  ";
        }
    }while(!find); 
}

// The function displays the contact corresponding to the entered phone number
void Admin::show_by_phone_number()
{
    std::cout << std::endl << "please, input phone_number  :  ";
    std::string phone_number;
    bool find;
    do {
        find = false;
        std::cin >> phone_number;
        std::cout << std::endl;
        for (int i{}; i < data.size(); ++i) {
           Contact obj = string_to_Contact(data[i]);
           if (obj.get_phone_number() == phone_number) {
               find = true;
               Contact_to_short_string(obj);
               break;
           }
        }
        if (!find) {
            std::cout << std::endl << "no contact found with that phone_number. Please, input another phone_number  :  ";
        }
    }while(!find); 
}

// The function displays all contacts whose address matches the entered address
void Admin::show_by_address()
{
    std::cout << std::endl << "please, input contact address  :  ";
    std::string address;
    bool find;
    do {
        find = false;
        std::getline(std::cin, address);
        std::cout << std::endl;
        for (int i{}; i < data.size(); ++i) {
           Contact obj = string_to_Contact(data[i]);
           std::string main_address{}; // first word of address
           int j{};
           std::string all_address = obj.get_address();
           while (all_address[j] != ' ') {
            main_address += all_address[j];
            ++j;
           }
           if (main_address == address || all_address == address) {
               find = true;
               Contact_to_short_string(obj);
           }
        }
        if (!find) {
            std::cout << std::endl << "no contact found in that address. Please, input another address  :  ";
      	}
    }while(!find); 
}