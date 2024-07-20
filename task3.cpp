#include<iostream>
#include<fstream>
#include<string>

using namespace std;

string readFile(const string &filePath) {
    ifstream file(filePath, ios::in | ios::binary);
    if (!file){
        throw runtime_error("Could not open file for reading.");
    }
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    return content;
}

void writeFile(const string &filePath, const string &data){
    ofstream file(filePath, ios::out | ios::binary);
    if (!file){
        throw runtime_error("Could not open file for writing.");
    }
    file.write(data.c_str(), data.size());
}

string CompressRLE(const string &data){
    string compressed;
    int n = data.size();
    for (int i = 0; i < n; ++i){
        int count = 1;
        while(i+1 < n && data[i] == data[i+1]){
            ++i;
            count++;
        }
        compressed += data[i];
        compressed += to_string(count);
    }
    return compressed;
}

string decompressRLE(const string &data) {
    string decompressed;
    int n = data.size();
    for(int i = 0; i < n; ++i){
        char ch = data[i];
        string countStr;
        while (i+1 < n && isdigit(data[i + 1])){
            countStr += data[++i];
        }
        int count = stoi(countStr);
        decompressed.append(count, ch);
    }
    return decompressed;
}

int main(void) {
    string inPath, outPath;
    char c;

    cout << "Enter the path to the input file: ";
    cin >> inPath;

    cout << "Choose operation: 1. Compress 2. Decompress: ";
    cin >> c;
    switch(c){
        case '1':
            try{
                string data = readFile(inPath);
                string compData = CompressRLE(data);
                outPath = inPath + ".rle";
                writeFile(outPath, compData);
                cout << "File compressed successfully. Output file: " << outPath << endl;
            }
            catch(const exception &e){
                cerr << "Error: " << e.what() << endl;
            }
            break;
        case '2':
            try{
                string data = readFile(inPath);
                string decompData = decompressRLE(data);
                outPath = inPath + ".decompressed";
                writeFile(outPath, decompData);
                cout << "File decompressed successfully. Output file: " << outPath << endl;
            }
            catch(const exception &e){
                cerr << "Error: " << e.what() << endl;
            }
            break;
        default:
            cerr << "Invalid choice, please enter '1' for Compress and '2' for Decompress." << endl;
    }

    return 0;
}
