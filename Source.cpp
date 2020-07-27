#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int checkBox(int** hArray, int** vArray, int size, int boxSize)
{
    int boxCount = 0;
    bool box = false;

    for (int i = 0; i < size - boxSize; i++)
    {
        for (int j = 0; j < size - boxSize; j++)
        {
            box = true;
            for (int k = 0; k < boxSize; k++)
            {
                if (hArray[i][j] != 1 || hArray[i + boxSize][j] != 1)
                    box = false;
                if (vArray[j][i] != 1 || vArray[j + boxSize][i] != 1)
                    box = false;
            }
            if (box)
                boxCount++;
        }
    }
    return boxCount;
}

int main()
{
    int problemCount = 1;
    string outputStr = "";
    /////////Opening File////////
    ifstream iFile("input.txt");
    if (!iFile.is_open())
    {
        cout << "input.txt dosyasi bulunamadi. Lutfen kaynak kodla ayni dosyada oldugundan emin olun." << endl;
        return 0;
    }
    /////////////////////////////

    while (true)
    {
        ///////Creating Matrixes//////
        int size = 0;
        iFile >> size;

        if (size == 0)
            break;

        //Horizontal lines
        int** hArray = new int* [size];
        for (int i = 0; i < size; i++)
        {
            hArray[i] = new int[size - 1];
            for (int j = 0; j < size - 1; j++)
                hArray[i][j] = 0; //default: no line => value 0
        }

        //Vertical lines
        int** vArray = new int* [size];
        for (int i = 0; i < size; i++)
        {
            vArray[i] = new int[size - 1];
            for (int j = 0; j < size - 1; j++)
                vArray[i][j] = 0; //default: no line => value 0
        }
        //////////////////////////////

        ////////Determining Lines///////
        int lineCount = 0;
        iFile >> lineCount;

        char hv = '0';
        int k;
        int l;

        for (int i = 0; i < lineCount; i++)
        {
            iFile >> hv >> k >> l; //Getting line

            if (hv == 'H')
            {
                hArray[k - 1][l - 1]++; //if there is line so value is 1
            }
            else
            {
                vArray[k - 1][l - 1]++; //if there is line so value is 1
            }
        }
        /////////////////////////////////

        /////////checking boxes//////////
        int boxCount;
        string boxCountStr = "";
        bool found = false;

        for (int i = 1; i < size; i++)
        {
            boxCount = checkBox(hArray, vArray, size, i);

            if (boxCount == 0)
                continue;
            else
                found = true;

            boxCountStr += boxCount + 48;
            boxCountStr += " square (s) of size ";
            boxCountStr += i + 48;
            boxCountStr += "\n";
        }

        if (!found)
            boxCountStr = "No completed squares can be found.\n";
        //////////////////////////////////

        ///////Editing output string///////
        outputStr += "Problem #";
        outputStr += problemCount + 48;
        outputStr += "\n\n";
        outputStr += boxCountStr;
        outputStr += "\n*******************************************\n\n";
        problemCount++;
    }
    iFile.close();

    ofstream oFile("output.txt");
    oFile << outputStr;
    oFile.close();

    return 0;
}