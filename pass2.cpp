#include <bits/stdc++.h>
using namespace std;
class Pass2
{
public:
    void execute()
    {
        ifstream symb;
        symb.open("symbol2.txt");
        string line, word;
        map<string, string> SYMTAB;

        while (getline(symb, line))
        {
            stringstream st(line);
            st >> word;
            string symnumber = word;
            st >> word;
            st >> word;
            SYMTAB[symnumber] = word;
        }

        map<string, string> LITTAB;
        ifstream lit;
        lit.open("literal2.txt");

        while (getline(lit, line))
        {
            stringstream st(line);
            st >> word;
            string litnumber = word;
            st >> word;
            st >> word;
            LITTAB[litnumber] = word;
        }

        ofstream machineCode("machine_code.txt");
        ifstream input;
        int lc = -1;
        input.open("IC2.txt");
        while (getline(input, line))
        {
            stringstream st(line);
            st >> word;
            word = word.substr(1, 2);
            if (word == "AD")
            {
                st >> word;
                string word1 = "";
                for (int i = 0; i < word.length(); i++)
                {
                    if (word[i] >= '0' && word[i] <= '9')
                    {
                        word1 += word[i];
                    }
                }
                word = word1;
                if (word == "01")
                {
                    st >> word;
                    st >> word;
                    word1 = "";
                    int i = 0;
                    while (word[i] != ')')
                    {
                        word1 += word[i];
                        i++;
                    }

                    lc = stoi(word1);
                    machineCode << "\n";
                }
                else if (word == "02")
                {
                    machineCode << endl;
                }
                else if (word == "03")
                {
                    st >> word;
                    st >> word;
                    string word1 = "";
                    int i = 0;
                    while (word[i] != ')')
                    {
                        word1 += word[i];
                        i++;
                    }
                    if (SYMTAB.count(word1) > 0)
                    {               // Check if the symbol exists in the symbol table
                        st >> word; // Read the '+' or '-'
                        int offset;
                        st >> offset; // Read the offset value

                        if (word == "+")
                        {
                            // Handle positive offset
                            int new_value = stoi(SYMTAB[word1]) + offset;
                            lc = (new_value);
                        }
                        else if (word == "-")
                        {
                            // Handle negative offset
                            int new_value = stoi(SYMTAB[word1]) - offset;
                            lc = (new_value);
                        }

                        machineCode << endl;
                    }
                    else
                    {
                        cout << "NO ENTRY FOUND IN SYMBOL TABLE" << endl;
                    }
                }
                else if (word == "04")
                {
                    machineCode << endl;
                }
                else
                {
                    continue;
                }
            }
            else if (word == "IS")
            {
                st >> word;
                string word1 = "";
                for (int i = 0; i < word.length(); i++)
                {
                    if (word[i] >= '0' && word[i] <= '9')
                    {
                        word1 += word[i];
                    }
                }
                word = word1;
                word1 = "";
                string temp = word;
                if (word == "00")
                {
                    machineCode << lc++ << "|\t" << word << "\t"
                                << "0\t"
                                << "000\n";
                    continue;
                }
                else if (word == "10" || word == "09")
                {
                    machineCode << lc++ << "|\t" << word << "\t"
                                << "0\t";
                }
                else
                {
                    machineCode << lc++ << "|\t" << word << "\t";
                }
                if (temp != "10" || temp != "09")
                {
                    st >> word;

                    for (int i = 0; i < word.length(); i++)
                    {
                        if (word[i] >= '0' && word[i] <= '9')
                        {
                            word1 += word[i];
                        }
                    }
                    word = word1;
                    word1 = "";
                    machineCode << word << "\t";
                }
                st >> word;
                for (int i = 0; i < word.length(); i++)
                {
                    if (word[i] >= 'A' && word[i] <= 'Z')
                    {
                        word1 += word[i];
                    }
                }
                word = word1;
                word1 = "";
                string offset;
                st >> offset;
                int i = 0;

                for (int i = 0; i < offset.length(); i++)
                {
                    if (offset[i] >= '0' && offset[i] <= '9')
                    {
                        word1 += offset[i];
                    }
                }

                if (word == "S")
                {
                    if (SYMTAB.count(word1) > 0)
                    {
                        machineCode << SYMTAB[word1];
                    }
                }
                else if (word == "L")
                {
                    if (LITTAB.count(word1) > 0)
                    {
                        machineCode << LITTAB[word1];
                    }
                }
                machineCode << endl;
            }
            else if (word == "DL")
            {
                st >> word;
                word = word.substr(0, 2);
                if (word == "01")
                {
                    machineCode << lc++ << "|\t";
                    st >> word;
                    st >> word;
                    string word1 = "";
                    int i = 0;
                    for (int i = 0; i < word.length(); i++)
                    {
                        if (word[i] >= '0' && word[i] <= '9')
                        {
                            word1 += word[i];
                        }
                    }
                    machineCode << "00"
                                << "\t"
                                << "0"
                                << "\t" << word1 << endl;
                }
                else if (word == "02")
                {

                    st >> word;
                    st >> word;
                    string word1 = "";
                    int i = 0;
                    while (word[i] != ')')
                    {
                        word1 += word[i];
                        i += 1;
                    }
                    int count = stoi(word1);
                    while (count--)
                    {
                        machineCode << lc++ << "|\t" << endl;
                    }
                }
            }
        }
    }
};

int main()
{

    Pass2 p;

    p.execute();
}
