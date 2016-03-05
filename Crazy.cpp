
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

std::string outFileName(std::string inFile);
void crazyToCpp(std::string s);
void executeMode(std::string s);
void interactive();
int index = 0;

const int SIZE = 1000;
int tape[SIZE] = {0};
int* dp = tape;


std::string commands = "";


int main(int argc, char* argv[])
{
    if(argc == 1)
    {
        while(true)
        {
            std::cout << "\n enter command \n";
            std::cin >> commands;
            interactive();
        }
        return 0;
    }
    std::string s = argv[1];
    if (s == "-c")
    {
        crazyToCpp(argv[2]);
    }
    else if(s == "-e")
    {
        executeMode(argv[2]);

        return 0;
    }

}

void crazyToCpp(std::string s)
{
    std::ifstream fin(s.c_str());
    std::string fileName = s;
    s = s+ " ";
    s[s.length()-1] = 'p';
    s[s.length()-2] = 'p';

    std::cout << s << "\n";
    std::ofstream fout(s.c_str());
    char cur;
    std::cout << "#include <iostream> \n";
    std::cout << "const int SIZE = 1000; \n";
    std::cout << "int tape[SIZE] = {0}; \n";
    std::cout << "int *dp = tape; \n";
    std::cout << "int main() { \n";
    fout << "#include <iostream> \n \n";
    fout << "const int SIZE = 1000; \n";
    fout << "int tape[SIZE] = {0}; \n";
    fout << "int *dp = tape; \n";
    fout << "int main() { \n";

    while(!fin.eof())
    {
        fin >> cur;
        switch(cur)
        {
        case '+':
            std:: cout << "++*dp; \n";
            fout << "++*dp; \n";
            break;

        case '-':
            std:: cout << "--*dp; \n";
            fout << "--*dp; \n";
            break;
        case '>':
            std::cout << "++dp; \n";
            fout << "++dp; \n";
            break;
        case '<':
            std::cout << "--dp; \n";
            fout << "--dp; \n";
            break;
        case ':':
            std::cout << "std::cout << *dp; \n";
            fout << "std::cout << *dp; \n";
            break;
        case '.':
            std::cout << "std::cout << ((char) *dp); \n";
            fout << "std::cout << ((char) *dp); \n";
            break;
        case '{':
            std::cout << " while (*dp) { \n";
            fout << " while (*dp) { \n";
            break;
        case '}':
            std::cout << "} \n";
            fout << "} \n";
            break;
        default:
            break;
        }
    }
    // closing print statement
    std::cout << "} \n \n";
    fout << "} \n";


}

void executeMode(std::string s)
{

    std::ifstream fin(s.c_str());
    char cur;

    while(!fin.eof())
    {
        fin >> cur;
        commands += cur;
    }


    char com[commands.size()];
    for(int i = 0; i < commands.size(); i++)
    {
        com[i] = commands[i];
    }
    char* c = com;

    while(*c)
    {
        switch(*c)
        {
        case '+':
            ++(*dp);
            break;
        case '-':
            --(*dp);
            break;
        case '>':
            ++dp;
            break;
        case '<':
            --dp;
            break;
        case ':':
            std::cout << (*dp) << "\n";
            break;
        case '.':
            std::cout << ((char)(*dp)) << "\n";
            break;
        case '{':
        {
            int count = 1;
            if(*dp == 0)
            {
                while(count != 0)
                {
                    c++;
                    if(*c == '{')
                        count++;
                    if(*c == '}')
                        count--;
                }
            }
            break;
        }


        case '}':
        {
            int count = 0;
            do
            {

                if(*c == '{')
                    count++;
                if(*c == '}')
                    count--;

                c--;
            }
            while(count != 0);
        }

        break;

        default:
            break;
        }
        c++;
    }

}

void interactive()
{
    std::string input;

    char com[commands.size()];
    for(int i = 0; i < commands.size(); i++)
    {
        com[i] = commands[i];
    }
    char* c = com;

    while(*c)
    {
        switch(*c)
        {
        case '+':
            ++(*dp);
            break;
        case '-':
            --(*dp);
            break;
        case '>':
            ++dp;
            ++index;
            break;
        case '<':
            --dp;
            --index;
            break;
        case ':':
            std::cout << (*dp) << "\n";
            break;
        case '.':
            std::cout << ((char)(*dp)) << "\n";
            break;
        case '{':
        {
            int count = 1;
            if(*dp == 0)
            {
                while(count != 0)
                {
                    c++;
                    if(*c == '{')
                        count++;
                    if(*c == '}')
                        count--;
                }
            }
            break;
        }


        case '}':
        {
            int count = 0;
            do
            {

                if(*c == '{')
                    count++;
                if(*c == '}')
                    count--;

                c--;
            }
            while(count != 0);
        }

        break;

        default:
            break;
        }
        c++;
    }

    std::cout << std::setw(9) << "Index: ";

    if(index > 3)
    {
        for(int i = index - 3; i <= index + 3; i++)
        {
            std::cout << std::setw(9) <<  i;
        }
        std::cout << "\n" << std::setw(9) <<"int: ";
        for(int i = index - 3; i <= index + 3; i++)
        {
            std::cout << std::setw(9) << tape[i];
        }
        std::cout << "\n" << std::setw(9) << "pointer: ";
        for(int i = index - 3; i < index + 3; i++)
        {
            if(index == i)
            {
                std::cout << std::setw(9) << "^";
            }
            else
            {
                std::cout << std:: setw(9) << " ";
            }
        }
    }
    else if(index > 992)
    {
        for(int i = 993; i < 1000; i++)
        {
            std::cout << std::setw(9) <<  i;
        }
        std::cout << "\n" << std::setw(9) <<"int: ";
        for(int i = 993; i < 1000; i++)
        {
            std::cout << std::setw(9) << tape[i];
        }
        std::cout << "\n" << std::setw(9) << "pointer: ";
        for(int i = 993; i < 1000; i++)
        {
            if(index == i)
            {
                std::cout << std::setw(9) << "^";
            }
            else
            {
                std::cout << std:: setw(9) << " ";
            }
        }
        std::cout << "\n";
    }
    else
    {

        for(int i = 0; i < 7; i++)
        {
            std::cout << std::setw(9) <<  i;
        }
        std::cout << "\n" << std::setw(9) <<"int: ";
        for(int i = 0; i < 7; i++)
        {
            std::cout << std::setw(9) << tape[i];
        }
        std::cout << "\n" << std::setw(9) << "pointer: ";
        for(int i = 0; i < 7; i++)
        {
            if(index == i)
            {
                std::cout << std::setw(9) << "^";
            }
            else
            {
                std::cout << std:: setw(9) << " ";
            }
        }
        std::cout << "\n";
    }
}







