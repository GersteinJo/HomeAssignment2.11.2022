//in this program I used PhoneBook.txt to extract phone data about people
//I use a container map that automatically sorts the content by key, which is name
//Names are to be unique otherwise it would be useless to search for a particular number by name

#include <iostream>
#include <map>
#include <unordered_map>
#include <iterator>
#include <experimental/random>
#include <fstream>

class PhoneBook
{
private:
    std::map<std::string, std::string> person_Phone;
public:
    PhoneBook() = default;
    //this one exists for demonstration
    PhoneBook(std::map<std::string, std::string> person_Phone)
    {
        for(auto [person, phone]: person_Phone) this->person_Phone[person]=phone;
    };
    //this one suggests having a file storing phone numbers and extracting em for further use
    PhoneBook(std::istream& in)
    {
        while(in)
        {
            std::string person, phone;
            std::getline(in,person,'+');
            std::getline(in,phone);
            phone = "+" + phone;
            if(person != "") person_Phone[person] = phone;
        }
    }

    ~PhoneBook() = default;

    //func that returns a sorted list
    std::map<std::string,std::string> SortedList()
    {
        return person_Phone;
    }

    //func that allows to get a number by the name, looks for exact identity, otherwise returns pair
    //nothing was found
    std::pair<std::string, std::string> FindUser(std::string user)
    {
        return person_Phone[user] != ""? std::make_pair(user, person_Phone[user]):
        std::make_pair("nothing","was found");
    }

    //func that generates random Name and grants access to it uses previous funk
    std::pair<std::string, std::string> GetRandomUser()
    {
        int n = std::experimental::randint(0, (int)person_Phone.size());
        std::map<std::string, std::string>::iterator out = person_Phone.begin();
        std::advance(out,n);
        return FindUser(out->first);
    }

    void AddPhoneNumber(std::string person, std::string phone)
    {
        person_Phone[person] = phone;
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
    std::map<std::string, std::string> phoneBook;//first name, second number
    phoneBook["Gregory McMilan"] = "+1 268 567 0890";
    phoneBook["Jesus Gomez"] = "+54 567 6540";
    phoneBook["Niclas Michelson"] = "+47 457 8463";

    PhoneBook myPhoneBook(phoneBook);
    myPhoneBook.AddPhoneNumber("Jeniffer Chang", "+81 912 4563");
    std::map<std::string, std::string> SortedList = myPhoneBook.SortedList();
    std::cout << myPhoneBook;
    std::cout<<"\n"<<myPhoneBook.FindUser("Jeniffer Chang").first<<" "
            <<myPhoneBook.FindUser("Jeniffer Chang").second<<"\n";

    std::cout<<"\n"<<myPhoneBook.FindUser("Jenifer Chang").first<<" "
             <<myPhoneBook.FindUser("Jenifer Chang").second<<"\n";

    std::ifstream phoneBookFile;
    phoneBookFile.open("PhoneBook.txt");
    PhoneBook myFilePhoneBook(phoneBookFile);
    phoneBookFile.close();

    std::cout<<"\n"<<myFilePhoneBook;
    return 0;


}
