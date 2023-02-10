#include <iostream>
#include "contact.h"

 std::string Contact::get_name() const
 {
     return m_name;
 }

std::string Contact::get_surname() const
{
    return m_surname;
}

std::string Contact::get_phone_number() const
{
    return m_phone_number;
}

std::string Contact::get_address() const
{
    return m_address;
}

void Contact::set_name(const std::string& name)
{
    m_name = name;    
}

void Contact::set_surname(const std::string& surname)
{
    m_surname = surname;    
}

void Contact::set_phone_number(const std::string& phone_number)
{
    m_phone_number = phone_number; 
}

void Contact::set_address(const std::string& address)
{
    m_address = address; 
}