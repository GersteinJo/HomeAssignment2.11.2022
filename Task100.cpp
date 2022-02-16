//in this program I used PhoneBook.txt to extract phone data about people
//I use a container map that automatically sorts the content by key, which is name
//Names are to be unique otherwise it would be useless to search for a particular number by name

#include <iostream>
#include <map>
#include <iterator>
#include <experimental/random>
#include <fstream>

class PhoneBook
{
private:
    std::multimap<std::string, std::string> person_Phone;
public:
    PhoneBook() = default;
    //this one exists for demonstration
    PhoneBook(const std::multimap<std::string, std::string>& person_Phone)
    {
        for(auto [person, phone]: person_Phone)
            this->person_Phone.insert(std::make_pair(person,phone));
    };
    //this one suggests having a file storing phone numbers and extracting em for further use
    PhoneBook(std::istream& in)
    {
        while(in)
        {
            std::string person, phone;
            std::getline(in,person,'+');
            std::getline(in,phone);
            if(!person.empty()) person_Phone.insert(std::make_pair(person,"+" + phone));
        }
    }

    ~PhoneBook() = default;

    //func that returns a sorted list
    std::multimap<std::string,std::string> SortedList()
    {
        return person_Phone;
    }

    //func that allows to get a number by the name, looks for exact identity, otherwise returns pair
    //nothing was found
    std::multimap<std::string, std::string> FindUser(std::string user)
    {
        auto[left, right] = person_Phone.equal_range(user);
        std::multimap<std::string, std::string> searchRequest;
        for(auto it = left; it != right; it++)
            searchRequest.insert(std::make_pair(it->first, it->second));
        return searchRequest;
    }

    //func that generates random Name and grants access to it uses previous funk
    std::pair<std::string, std::string> GetRandomUser()
    {
        int n = std::experimental::randint(0, (int)person_Phone.size());
        auto out = person_Phone.begin();
        std::advance(out,n);
        return std::make_pair(out->first, out->second);
    }

    void AddPhoneNumber(std::string person, std::string phone)
    {
        person_Phone.insert(std::make_pair(person, phone));
    }

    friend std::ostream& operator <<(std::ostream& out,
                                     const PhoneBook& outPhoneBook)
    {
        for(auto [person, phone]: outPhoneBook.person_Phone) out<<person<<": "<<phone<<"\n";
        return out;
    }
};

int main()
{
    std::multimap<std::string, std::string> phoneBook;//first name, second number
    phoneBook.insert(std::make_pair("Gregory McMilan", "+1 268 567 0890"));
    phoneBook.insert(std::make_pair("Jesus Gomez", "+54 567 6540"));
    phoneBook.insert(std::make_pair("Niclas Michelson", "+47 457 8463"));


    PhoneBook myPhoneBook(phoneBook);
    myPhoneBook.AddPhoneNumber("Jeniffer Chang", "+81 912 4563");
    myPhoneBook.AddPhoneNumber("Jeniffer Chang", "+44 928 2020");
    std::multimap<std::string, std::string> SortedList = myPhoneBook.SortedList();
    std::cout << myPhoneBook;
    std::multimap<std::string,std::string> searchResult(myPhoneBook.FindUser("Jeniffer Chang"));

    for(auto [user, phone]: searchResult) std::cout<<user<<": "<<phone<<"\n";

    std::ifstream phoneBookFile;
    phoneBookFile.open("PhoneBook.txt");
    PhoneBook myFilePhoneBook(phoneBookFile);
    phoneBookFile.close();

    std::cout<<"\n"<<myFilePhoneBook;

    return 0;
}
