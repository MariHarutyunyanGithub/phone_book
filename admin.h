//Implement a program, that allows to register a contact information 
//(name, surname, phone number, address).
//The program should provide an interface (can be used postman) ,
//where the user is able to add a new contact , edit the contact 
//information of the already existing one and remove one of the contacts.


#ifndef ADMIN_H
#define ADMIN_H

#include <iostream>
#include <fstream>
#include "contact.h"

class Admin
{
public:
    std::ofstream fout;
    std::ofstream tmpfout;
    std::ifstream fin;
    std::vector<std::string> data;//կոնտակտները պահելու համար
    std::vector<std::string> phone;//հեռախոսահամարները պահելու համար
    std::vector<int> lengths;//ներմուծված պարամետրերի երկարությունների համար
private:
    int m_size{14};
public:   
    void start();
private:
    Contact create_contact();
    Contact string_to_Contact(std::string);
    std::string Contact_to_string(Contact&);
    void Contact_to_short_string(Contact);
    void show_main_menu();     
    void menu_functions(short);
    void show_all_contacts();
    void add_new_contact();
    void edit_contact(std::string&);
    void remove_contact(std::string&);
    void exit_from_program(); 
private:
    void edit_name(std::string&);
    void edit_surname(std::string&);
    void edit_phone_number(std::string&);
    void edit_address(std::string&);
private:
    void find_to_edit_contact(std::string&);
    void find_to_remove_contact(std::string&);
    void find_to_show_contact();
private:
    void show_by_name();
    void show_by_surname();
    void show_by_phone_number();
    void show_by_address();
private:
    bool check_name(std::string&) const;
    bool check_surname(std::string&) const;
    bool check_phone_number(std::string&) const;
    bool check_address(std::string&) const;
};

#endif//ADMIN_H