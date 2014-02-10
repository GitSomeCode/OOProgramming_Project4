#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <vector>

using namespace std;

map<string,string>E; //map
map<string,string>::iterator E_It;  //map iterator

void InitMap(){
E["prefix"] = "1111";
E["$"] = "10110101";
E["0"] = "0000";
E["1"] = "0001";
E["2"] = "0010";
E["3"] = "0011";
E["4"] = "0100";
E["5"] = "0101";
E["6"] = "0110";
E["7"] = "0111";
E["8"] = "1000";
E["9"] = "1001";
E["10"] = "1010";
E["11"] = "1011";
E["12"] = "1100";
E["13"] = "1101";
E["14"] = "1110";
E["15"] = "1111";
}

class Code{

   public:
   Code(){}
   Code(string s){input = s; at = &before;} //take in user string
   void storeInput(); //put user string in vector
   void storeFinal(string final);
   void printbefore();

   protected:
   string input;
   vector<string> before;
   vector<string> encoded;
   vector<string>* at;

};

void Code::storeInput()
{
    stringstream ss;
    string s;
    for(int j = 0; j < input.length(); j++)
    {
        //convert char to string first
        ss.clear(); //clear stream at each iteration of loop
        ss << input[j];
        ss >> s;

        //store in vector
        before.push_back(s);
    }
}

void Code::storeFinal(string final)
{
    stringstream ss;
    string s;
    for(int j = 0; j < final.length(); j++)
    {
        //convert char to string first
        ss.clear(); //clear stream at each iteration of loop
        ss << final[j];
        ss >> s;

        //store in vector
        encoded.push_back(s);
    }
}

void Code::printbefore()
{
    for(int i = 0; i < before.size(); i++)
    cout << before[i];
}
////////////////////////////////////////////////////////////
class HalfByte: public Code{

   public:
   HalfByte(string s):Code(s){input = s; length = input.length();
   storeInput(); at2 = &binary;}
   void getBinary();
   void printBinary();
   void storeFinal(); //put final encoded in vector
   void printFinal();

   private:
   string input;
   int length; //length of user input
   vector<string> binary;
   vector<string>* at2; // for binary vector
   vector<string> final;

};

//stores binary values of before vector into binary vector
void HalfByte::getBinary()
{
    for(int i = 0; i < length; i++)
    {
       E_It = E.find((*at)[i]);

       if(E_It != E.end())
       at2->push_back(E_It->second);
    }
}

void HalfByte::printBinary()
{
    for(int i = 0; i < binary.size(); i++)
    cout << binary[i] << " ";
}

void HalfByte::storeFinal()
{
    stringstream ss;
    ss.clear();
    string s;
    s = "";

    //first store ebcdic special symbol
    E_It = E.find("$");
    if(E_It != E.end())
    final.push_back(E_It->second);

    //second store ebcdic prefix
    E_It = E.find("prefix");
    if(E_It != E.end())
    final.push_back(E_It->second);

    //third store binary value for how many times prefix is repeated
    ss << length;
    ss >> s;
    E_It = E.find(s);
    if(E_It != E.end())
    final.push_back(E_It->second);

    //fourth store the binary values for user input

    for(int i = 0; i < binary.size(); i++)
    {
        //store in vector
        final.push_back(binary[i]);
    }
}

void HalfByte::printFinal()
{
    cout << endl << "Encoded string: ";
    for(int i = 0; i < final.size(); i++)
    cout << final[i] << " ";
}
//////////////////////////////////////////////////////////
bool validateHBP(string s)
{
    if(s.length() > 15)
    return false;

    for(int i = 0; i < s.length(); i++)
    {
        if(!isdigit(s[i]))
        return false;
    }

    return true;
}
////////////////////////////////////////////////////////////
class RunLength: public Code{

    public:
    RunLength(string s){input = s; length = input.length();}
    void GetRepeated();
    void store(); // pass to base class vector
    void printFinal();

    private:
    string input, FINAL;
    int length, counter;
};

/////////////////////////////////////////////////////////
void RunLength::GetRepeated()
{
    char temp;
    FINAL = ""; //string to store encoded value
    stringstream st;
    bool encoded = false;
    for(int i = 0; i < length; i++)
    {
        st.clear();
        counter = 0;
        temp = input[i];
        encoded = false;

        //if char is not last of string
        if(i != length - 1)
        {
            for(int j = i; j < length; j++)
            {
                //if next char is same as current
                if(input[j] == temp)
                   counter++;
                else
                   break;
            }
            //if occurence > 3, encode
            if(counter > 3)
            {
                //first, special symbol
                E_It = E.find("$");
                FINAL += E_It->first;

                //second, digit that is repeated
                FINAL += temp;
                stringstream ss;

                //third, how any times repeated
                ss << counter;
                FINAL += ss.str();

                encoded = true;

                //skip to next diff char
                i+=counter-1;
            }

            if(encoded == false)
            FINAL += input[i];

            st.clear();
        }
        else
        FINAL += input[i];
    }
}

void RunLength::store()
{
    //base class function
    storeFinal(FINAL);
}

void RunLength::printFinal()
{
    cout << endl << "Encoded string: ";
    for(int i = 0; i < encoded.size(); i++)
    cout << encoded[i];
}
//////////////////////////////////////////////////////////
bool validateRL(string s)
{
    for(int i = 0; i < s.length(); i++)
    {
        if(!isdigit(s[i]))
        return false;
    }
    return true;
}
//////////////////////////////////////////////////////////
void About()
{
    cout << endl << endl;
    cout << " ------------------------------------------" << endl;
    cout << "                   ABOUT                   " << endl;
    cout << " ------------------------------------------" << endl;
    cout << " This program performs two data compression" << endl;
    cout << " schemes: Half-Byte Packing and Run Length " << endl;
    cout << " Coding." << endl << endl;
    cout << " This half-byte packing scheme encodes" << endl;
    cout << " numbers from 0-9 using the EBCDIC codes." << endl;
    cout << " The length of strings cannot exceed 15  " << endl;
    cout << " because EBCDIC codes from 0-15 are being used" << endl;
    cout << " The special character is represented by an" << endl;
    cout << " 8-bit EBCDIC code." << endl;
    cout << " Encoded strings are the following format:" << endl;
    cout << " [symbol][prefix][x prefix repeated][digits]...[]" << endl;
    cout << endl << endl;
    cout << " This run-length coding encodes numbers from" << endl;
    cout << " 0-9. " << endl;
    cout << " Character occurence must be greater than 3" << endl;
    cout << " to be utilized by the run-length algorithm." << endl;
    cout << " The special symbol used to denote a repeated" << endl;
    cout << " string is $." << endl;
    cout << " Encoded strings are the following format:" << endl;
    cout << " [$][digit][x digit repeated]" << endl;
    cout << endl << endl;
}
//////////////////////////////////////////////////////////
void Greeting()
{
    cout << "  ******************************************" << endl;
    cout << "  ***********    ENCODER for    ************" << endl;
    cout << "  *********  HALF-BYTE PACKING   ***********" << endl;
    cout << "  **********         &          ************" << endl;
    cout << "  ********   RUN-LENGTH CODING      ********" << endl;
    cout << "  ******************************************" << endl;
}



//////////////////////////////////////////////////////////
int main()
{
    InitMap();
    Greeting();
    About ();
    cout << endl << endl;

    cout << "------------------  HALF-BYTE PACKING   --------------------" << endl;
    cout << endl;
    string u = "123";
    if(validateHBP(u))
    {
        cout << "... encoding HBP with string " << u << endl;
        HalfByte mycode(u);
        mycode.getBinary();
        mycode.storeFinal();
        mycode.printFinal();
    }
    else {cout << u <<" is a faulty string!" << endl;
    cout << "Must be all digits and not more than length 15!" << endl;}



cout << endl << endl << endl << endl;
cout << "------------------  RUN-LENGTH CODING   -------------------" << endl;
cout << endl;
    string p = "112222333888888";
    if(validateRL(p))
    {
        cout << "... encoding RLC with string " << p << endl;
        RunLength rl(p);
        rl.GetRepeated();
        rl.store();
        rl.printFinal();
    }
    else cout << p << " is a faulty string! "<< endl << "Must be all digits!" << endl;


    cout << endl << endl << endl << endl;

    return 0;
}
