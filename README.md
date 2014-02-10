OOProgramming_Project4
======================

void About()
{
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
}

