#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>

using namespace std;

int log100(int num) {
    return log(num)/log(100);
}

long long modulopower(long long num, long  pow, long  modulo)
{
    long long res = 1;     // Initialize result
 
    num = num%modulo; // if num > modulo
  
    if (num == 0) return 0; // case num divided by modulo;
 
    while (pow > 0)
    {
        if (pow % 2)
            res = (res*num) % modulo;
        pow = pow/2; 
        num = (num*num) % modulo;
    }
    return res;
}

//this algorithm is sponsored by sal khan
long gcd (long a, long b) {
    if (a == 0) {
        return b;
    }
    return gcd (b%a, a);
}

// Function for extended Euclidean Algorithm 
long gcdextended(long a, long b, long *x, long *y) 
{ 
    if (a == 0) 
    { 
        *y = 1; 
        *x = 0; 
        return b; 
    } 
    long tempx, tempy; 
    long ans = gcdextended(b%a, a, &tempx, &tempy); 
    *y = tempx; 
    *x = tempy - (b/a) * tempx; 
    
    return ans; 
}

int main(int argc, char *argv[]) {
    //p and q accessed
    long p = stol(argv[1]);
    long q = stol(argv[2]);
    int e = 65537;
    long L = (p-1)*(q-1)/gcd(p-1,q-1);
    if (L <= e) {
        cout << "Error: L is smaller than e." << endl;
        return 0;
    }
    //declared for extended gcd
    long d, g;
    long ansT = gcdextended(e, L, &d, &g);
    if (ansT != 1) {
        cout << "No longer guarantee encryption/decryption secure" << endl;
    }
    if (d < 0) {
        d += (p-1) * (q-1) ;
        //does this need to be repeated? in case hella negative
        //no
    }
    //decryption key d calculated

    while (true) {
        cout << endl;
        cout << "Please enter a command: " << endl;
        string command;
        getline(cin,command);
        stringstream ss;
        ss << command;
        ss >> command;
        //command reused cuz im lazy
        if (command == "EXIT") {
            cout << "Exiting program..." << endl;
            return 0;
        } else if (command == "DECRYPT") {
            string inputfile, outputfile;
            ss >> inputfile;
            ss >> outputfile;
            //process input
            ifstream infile(inputfile.c_str());
            if (!infile)
            {
                cout << "Cannot open " << inputfile << "!" << endl;
                return 0;
            }
            string outputMsg = "";
            while (true) {
                long x;
                infile >> x;
                long mDecrypted = modulopower(x,d,p*q);
                string parseM = to_string(mDecrypted);
                //convert to string for easier parsing
                string outputFrag = "";
                for (int i = parseM.size()-1; i >= 0; i -= 2) {
                    string outputTerm = "";
                    //case when size is odd due to leading 0s
                    if (i >= 1) {
                        outputTerm = parseM[i-1];
                        outputTerm += parseM[i];
                    } else {
                        outputTerm = parseM[i];
                    }
                    //string to num, then ascii table processing
                    int iConv = stoi(outputTerm);
                    if (iConv == 0) {
                        outputFrag += " ";
                    } else {
                        char c = iConv + 96;
                        outputFrag += c;
                    }
                }
                outputMsg.insert(0,outputFrag);
                //end of file
                if( infile.eof() )  {
                    break;
                }
            }
            //reverse output due to how i parsed
            string reversedOutput;
            for (int i = outputMsg.size()-1; i >= 0; --i) {
                reversedOutput += outputMsg[i];
            }
            // Create and open a text file
            ofstream MyFile(outputfile);
            // Write to the file
            MyFile << reversedOutput;
            MyFile.close();
            

        } else if (command == "ENCRYPT") {
            string filename, message;
            long n;
            ss >> filename;
            ss >> n;
            //message can have spaces
            getline(ss, message);
            //remove default leading space
            message.erase(0,1);
            if (n < 27) {
                cout << "n is smaller than 27" << endl;
                return 0;
            }
            int x = log100(n/27) +1;
            int explored = 0;
            string outputmsg = "";
            while (explored < message.size()) {
                string tempNum = "";
                //case when in middle of string
                if (x+explored<= message.size()) {
                    for (int i = 0; i < x; ++i) {
                        char c = message[i + explored];
                        if (c == ' ') {
                            tempNum += "00";
                        } else {
                            if (c >= 'a' && c <= 'i') { //01 to 09 case
                                tempNum += "0";
                                int cTemp = c - 96;
                                tempNum += to_string(cTemp);
                            } else {
                                int cTemp = c - 96;
                                tempNum += to_string(cTemp);
                            }
                        }
                    }
                } else {
                    //dealing with case where not enough letters remaining
                    for (int i = explored; i <message.size(); i++) {
                        char c = message[i];
                        if (c == ' ') {
                            tempNum += "00";
                        } else {
                            if (c >= 'a' && c <= 'i') { //01 to 09 case
                                tempNum += "0";
                                int cTemp = c - 96;
                                tempNum += to_string(cTemp);
                            } else {
                                int cTemp = c - 96;
                                tempNum += to_string(cTemp);
                            }
                        }
                    }
                    //trailing spaces
                    for (int i = message.size(); i < explored + x; i++) {
                        tempNum+= "00";
                    }
                }
                explored += x;
                if (outputmsg != "") {
                    outputmsg += " ";
                }
                //encrypting with modular arithmetic
                long outputNum = modulopower(stol(tempNum), e, n);
                string regexP = to_string(outputNum);
                /*
                leading 0's not desired so this is useless
                if (regexP.size() < 2*x) {
                    while (regexP.size() < 2*x) {
                        regexP.insert(0, "0");
                    }
                }
                */
                outputmsg += regexP;
            }
            // output file
            ofstream MyFile(filename);
            MyFile << outputmsg;
            MyFile.close();
            
        } else {
            cout << "That is not a valid command. Terminating Program." << endl;
            return 0;
            /*
            cout << "EXIT - terminate program" << endl;
            cout << "DECRYPT [input] [output] - decrypts input file into output" << endl;
            cout << "ENCRYPT [filename] [n] [message]" << endl;
            */
        }
    }
}