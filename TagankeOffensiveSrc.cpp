//CUSTOMIZE HERE ______________________________________________________________________________________________________________________________________
#define COLOR_STATS 9                                             //COLORS
#define COLOR_DIALOG 16
#define COLOR_INPUT 128
#define COLOR_OPTIONS 9
#define COLOR_INFO 64
#define COLOR_SELECTED 240
#define COLOR_CLEAR 1
#define DIVIDOR_LETTER_TYPER 500                                  //GAME SPEEDS
#define MULTIPLIER_END_TYPER 0
#define DELAY_OPTIONS 500
#define DELAY_INFO 1000
#define SIZE_XFONT 12                                             //FONT
#define SIZE_YFONT 24
#define FONT L"Consolas"
#define FULLSCREEN true                                           //FULLSCREEN
//END _________________________________________________________________________________________________________________________________________________



#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void print(string _content, bool _slowPrint, bool _end = true) {  //types out text in humanoid way
    if (_slowPrint) {
        SetConsoleTextAttribute(hConsole, COLOR_DIALOG);
        for (int i = 0; i < _content.length(); i++) {
            Sleep(rand() / DIVIDOR_LETTER_TYPER);
            cout << _content[i];
        }
        Sleep(_content.length() * MULTIPLIER_END_TYPER);
        if (_end) {
            cout << "\n";
        }
    }
    else {
        SetConsoleTextAttribute(hConsole, COLOR_DIALOG);
        cout << _content;
        if (_end) {
            cout << "\n";
        }
    }
}

class Stats                                                       //manages the infos above the dialog
{
public:
    string location, date;
    void display() {
        SetConsoleTextAttribute(hConsole, COLOR_STATS);
        cout << "Location: " << location << " / Date: " << date << endl;
        cout << "Inventory: " << inv[0] << " " << inv[1] << " " << inv[2] << " " << inv[3] << " " << inv[4] << " " << endl;
        cout << "--------------------------------------" << endl;
        cout << "\n";
    }
    void addItem(string _item) {                                  //add item to inventory
        for (int i = 0; i < sizeof(inv) / sizeof(inv[0]); i++) {
            if (inv[i] == "") {
                inv[i] = _item;
                break;
            }
        }
    }
    void removeItem(string _item) {                               //remove item
        for (int i = 0; i < sizeof(inv) / sizeof(inv[0]); i++) {
            if (inv[i] == _item) {
                inv[i] = "";
                break;
            }
        }
    }
    bool hasItem(string _item) {                                  //check for item
        for (int i = 0; i < sizeof(inv) / sizeof(inv[0]); i++) {
            if (inv[i] == _item) {
                return true;
                break;
            }
        }
        return false;
    }
private:
    string inv[5];
}
stats;

class Dialog                                                      //manages the dialogs and options
{
public:
    int run(bool _initial = 1) {
        if (_initial) {
            selection = 0;
        }
        SetConsoleTextAttribute(hConsole, COLOR_CLEAR);
        system("cls");
        stats.display();
        print(text, _initial);
        cout << "\n";
        if (options[1] == "") {						              //If object is single option, do the typeout stuff
            cout << "->";
            SetConsoleTextAttribute(hConsole, COLOR_INPUT);
            cin >> input;
            if (input == options[0]) {
                return -1;
            }
            else {
                SetConsoleTextAttribute(hConsole, COLOR_INFO);
                cout << "Wrong Input";
                Sleep(DELAY_INFO);
                SetConsoleTextAttribute(hConsole, COLOR_CLEAR);
                system("cls");
                this->run(0);
                return -2;
            }
        }
        else {
            lastSelectionIndex = -1;			                  //print options stuff
            for (int i = 0; i < sizeof(options) / sizeof(options[0]); i++) {
                if (options[i] != "") {
                    if (_initial) {
                        Sleep(DELAY_OPTIONS);
                    }
                    if (selection == i) {
                        SetConsoleTextAttribute(hConsole, COLOR_SELECTED);
                    }
                    else {
                        SetConsoleTextAttribute(hConsole, COLOR_OPTIONS);
                    }
                    cout << options[i];
                    SetConsoleTextAttribute(hConsole, COLOR_CLEAR);
                    cout << " ";
                    lastSelectionIndex++;
                }
            }
            confirmSelection = false;			                  //options selection code
            while (!confirmSelection) {
                switch (_getch()) {
                case 77:
                    if (selection < lastSelectionIndex) {
                        selection++;
                        this->run(0);
                    }
                    break;
                case 75:
                    if (selection > 0) {
                        selection--;
                        this->run(0);
                    }
                    break;
                case 13:
                    confirmSelection = true;
                    break;
                default:
                    break;
                }
            }
            return selection;
        }
    }
    Dialog(string _text, string _option0, string _option1 = "", string _option2 = "", string _option3 = "") {
        text = _text;
        options[0] = _option0;
        options[1] = _option1;
        options[2] = _option2;
        options[3] = _option3;
    }
private:
    string text, options[4], input;
    int lastSelectionIndex, selection = 0;
    bool confirmSelection;
};

//THE TEXT ADVENTURE "ENGINE" CODE ENDS HERE, NOW THE MINIGAME:

class MiniGame {
private:
    //laurins first c++ project: 2d console type engine
    //
    //e: part of 2d engine
    //s: stuff you can use for scripting
    //u: user made stuff inside scripting

    //constants & setup
    const static int frameDelay = 0;                    //delay between frames (ms)
    const static int pixelSizeY = SIZE_YFONT / 2;         //sizeY of pixels & font
    const static int pixelSizeX = SIZE_XFONT;           //sizeX of pixels & font
    const static int rowLenght = 120;                   //screen row lenght
    const static int vertLenght = 30;                   //screen vert lenght

    //some variables
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int eLastColor = 1000;
    int sFrameCounter = 0;                              //frames played since start
    int eImg[vertLenght][rowLenght] = {};               //image (draw to this, when done put it on the screen with sDrawImage)
    int eLevelImg[vertLenght][rowLenght] = {
        120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,0,0,0,255,0,255,0,255,0,0,255,255,1,255,255,255,1,255,255,1,1,255,1,255,1,255,1,255,255,1,1,255,1,1,1,255,1,255,255,1,255,1,1,1,255,1,1,1,255,1,1,1,255,1,255,255,255,255,255,255,255,255,255,1,1,255,255,255,255,255,255,255,255,1,255,1,255,255,255,255,255,255,255,255,255,255,255,1,1,1,1,255,255,1,255,255,1,1,255,1,1,1,255,1,255,255,1,255,1,1,1,255,1,255,255,1,1,255,120,120,0,255,0,255,0,255,0,255,0,255,0,255,1,255,255,255,1,255,1,255,255,255,1,255,1,255,1,255,1,255,255,255,1,255,1,255,1,1,255,1,255,255,1,255,255,1,255,1,255,1,255,1,255,1,255,255,255,255,255,255,255,1,255,255,1,1,1,255,255,1,255,255,255,1,255,1,1,255,255,255,1,1,1,1,1,1,1,1,255,255,1,1,1,1,255,1,255,255,255,1,255,1,255,1,1,255,1,255,1,255,255,255,1,255,1,255,255,255,120,120,0,0,0,255,0,255,0,255,0,0,255,255,1,255,255,255,1,255,1,255,255,255,1,255,1,255,1,255,1,255,255,255,1,255,1,255,1,1,1,1,255,255,1,255,255,1,1,1,255,1,255,1,255,1,255,255,255,255,255,255,255,1,255,255,255,255,1,255,255,1,1,1,1,1,255,255,1,1,255,1,1,255,255,255,255,255,255,255,255,255,255,255,255,1,255,1,255,255,255,1,255,1,255,1,1,1,1,255,1,1,255,255,1,255,1,255,1,1,120,120,0,255,255,255,0,255,0,255,0,255,0,255,1,255,255,255,1,255,1,255,255,255,1,255,1,255,1,255,1,255,255,255,1,255,1,255,1,255,1,1,255,255,1,255,255,1,1,255,255,1,255,1,255,1,255,255,255,255,255,255,255,1,255,255,1,1,1,255,255,255,1,255,255,255,255,255,255,1,1,1,255,255,255,255,1,1,1,1,255,255,1,1,1,1,255,1,255,255,255,1,255,1,255,1,255,1,1,255,1,255,255,255,1,255,1,255,255,1,120,120,0,255,255,255,1,0,1,255,0,0,255,255,1,1,1,255,1,255,255,1,1,255,1,255,255,255,1,255,255,1,1,255,1,1,1,255,1,255,255,1,255,255,1,255,255,1,255,1,255,1,1,1,255,1,1,1,255,255,255,255,255,1,255,255,1,255,255,255,255,255,1,255,255,1,255,255,255,255,255,255,255,255,255,255,1,255,255,1,255,255,1,1,255,1,255,255,1,1,255,1,1,1,255,1,255,255,1,255,1,255,255,255,1,255,255,1,1,255,120,120,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,1,255,1,255,1,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,1,255,255,1,255,255,255,255,255,1,255,255,1,255,255,255,255,1,1,1,1,1,1,1,255,255,1,255,255,255,1,255,1,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,120,120,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,1,255,1,255,1,255,255,255,255,255,255,255,255,255,255,1,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,1,255,1,1,255,255,1,1,1,1,255,255,1,255,255,1,1,1,255,255,255,255,255,1,255,255,1,1,255,255,1,255,1,255,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,120,120,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,1,255,1,255,1,255,255,1,1,1,1,255,255,255,1,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,1,255,1,255,255,255,255,255,255,255,255,255,1,1,1,1,255,255,255,255,255,255,1,1,255,255,255,1,1,255,1,255,1,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,120,120,255,255,1,1,1,1,1,1,1,1,1,1,1,1,1,255,255,255,255,255,255,255,1,255,1,255,1,255,255,1,16,255,255,255,255,1,1,1,1,1,1,1,1,1,1,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,1,255,1,1,1,1,1,1,1,1,255,255,1,1,255,255,255,1,1,1,1,1,255,1,255,255,255,255,1,255,1,255,1,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,120,120,255,255,1,255,255,255,255,255,255,255,255,255,255,255,1,255,255,255,255,255,255,255,1,255,1,255,1,255,255,1,1,1,1,255,255,255,1,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,1,255,255,255,255,255,255,1,1,1,255,1,1,255,255,255,1,1,255,255,255,255,255,255,255,255,255,255,255,255,255,255,1,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,120,120,255,255,1,255,255,255,255,1,1,1,255,255,255,255,1,255,255,255,255,255,255,255,1,255,1,255,1,255,255,255,255,255,255,255,255,255,255,1,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,1,1,1,1,1,255,255,255,255,255,255,1,255,255,255,255,1,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,1,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,120,120,255,255,1,255,255,255,1,255,255,1,1,255,255,255,1,255,255,255,255,255,255,255,1,255,1,255,1,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,1,1,1,1,1,1,1,1,1,1,1,1,1,255,255,1,1,1,255,1,1,1,1,1,1,1,1,1,1,1,1,1,1,255,255,255,255,255,255,255,255,255,1,1,1,1,1,1,1,1,1,1,255,255,255,255,255,120,120,255,255,1,255,255,1,255,255,255,1,1,1,255,255,1,255,255,255,255,255,255,255,1,255,1,255,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,1,255,255,255,255,255,255,1,255,255,255,255,255,255,255,1,255,255,255,255,255,255,255,255,255,1,255,255,255,255,255,255,255,255,1,255,255,255,255,255,120,120,255,255,1,255,1,255,1,255,255,1,1,255,1,255,1,255,255,255,255,255,255,255,1,255,1,255,255,255,1,255,1,255,255,255,1,1,1,1,255,255,1,1,255,255,255,255,255,1,1,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,1,1,1,1,1,1,1,1,1,255,1,1,1,1,255,255,255,255,255,32,255,255,255,255,255,255,255,255,255,1,255,255,255,1,1,1,255,255,1,255,255,255,255,255,120,120,255,255,1,255,1,255,1,1,255,255,1,255,1,255,1,255,255,255,255,255,255,255,1,255,1,255,1,255,1,255,1,1,255,255,255,255,255,255,255,255,255,1,1,1,255,255,1,1,255,255,255,255,255,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,255,255,255,255,1,1,255,255,255,255,255,255,1,255,255,255,255,255,1,255,255,255,255,255,32,255,255,255,255,255,255,255,255,255,1,255,255,1,1,255,255,1,255,1,255,255,255,255,255,120,120,255,255,1,255,1,255,1,1,255,1,255,255,1,255,1,255,255,255,255,255,255,255,1,255,1,255,1,255,1,255,255,255,255,255,255,1,1,1,255,255,255,255,255,255,255,255,1,1,1,255,255,255,1,1,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,1,1,255,255,255,255,255,255,255,255,1,1,1,255,255,1,255,255,255,255,255,1,255,255,255,255,255,255,255,255,255,1,255,1,255,255,255,255,1,255,1,255,255,255,255,255,120,120,255,255,1,255,255,1,255,255,255,1,1,1,255,255,1,255,255,255,255,255,255,255,1,255,1,255,1,255,1,1,255,255,255,1,255,255,255,1,1,255,255,255,255,255,255,255,255,255,255,1,1,1,1,255,255,255,255,255,255,255,255,255,1,1,1,1,255,255,1,1,1,1,255,255,255,255,255,255,255,255,255,1,1,1,1,1,255,1,255,255,1,1,1,1,255,255,255,255,255,255,255,255,255,1,255,1,255,1,1,255,1,255,1,255,255,255,255,255,120,120,255,255,1,255,255,255,1,255,1,1,1,255,255,255,1,255,255,255,255,255,255,255,1,255,1,255,1,255,1,1,255,255,255,1,255,1,255,255,1,1,1,1,1,1,1,1,255,255,255,255,1,1,255,255,255,255,1,1,1,1,1,1,1,255,255,1,1,255,255,255,1,1,255,255,255,255,255,255,255,1,1,1,255,255,255,255,255,1,255,255,255,255,255,1,255,255,255,255,255,255,255,255,255,1,255,1,255,255,255,255,1,255,1,255,255,255,255,255,120,120,255,255,1,255,255,255,255,1,1,1,255,255,255,255,1,255,255,255,255,255,255,255,1,255,1,255,1,255,1,1,1,255,1,1,255,1,255,255,1,1,255,255,255,255,255,255,1,1,255,255,255,255,255,255,255,1,1,255,255,255,255,255,1,255,255,255,255,255,255,255,255,1,1,1,1,255,1,1,255,1,255,255,255,1,1,1,1,1,1,255,255,255,255,1,255,255,255,255,255,255,255,255,255,1,255,1,255,1,1,255,1,255,1,255,255,255,255,255,120,120,255,255,1,255,255,255,255,255,255,255,255,255,255,255,1,255,255,255,255,255,255,255,255,255,1,255,1,255,255,255,1,1,1,255,1,1,255,255,255,255,255,1,1,1,255,255,255,255,1,1,1,1,1,1,1,1,255,255,255,255,1,255,1,1,255,255,255,1,1,1,255,255,255,255,255,255,255,1,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,1,255,255,255,255,255,255,255,255,255,1,255,1,255,255,255,255,1,255,1,255,255,255,255,255,120,120,255,255,1,1,1,1,1,1,1,1,1,1,1,1,1,255,255,255,255,255,255,255,1,255,1,255,1,255,1,255,255,1,1,255,1,255,255,255,255,255,1,1,255,1,1,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,1,255,255,1,1,255,255,255,255,255,1,255,255,255,255,255,255,1,1,255,255,255,255,255,255,255,255,255,255,255,255,255,255,1,255,255,255,255,255,255,255,255,255,1,255,1,255,255,255,255,1,255,1,255,255,255,255,255,120,120,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,1,255,1,255,1,255,1,255,255,1,1,1,1,255,255,255,1,1,255,255,255,255,1,1,255,255,255,1,1,1,1,1,255,1,1,1,1,1,1,255,255,255,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,255,255,255,255,255,255,255,255,255,1,255,255,1,1,1,1,255,255,1,255,255,255,255,255,120,120,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,1,255,1,255,1,255,1,255,1,1,255,255,255,1,1,1,1,255,255,255,1,255,255,1,1,1,1,1,255,255,255,255,1,1,255,255,1,1,255,255,255,255,255,1,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,1,255,255,255,255,255,255,255,255,255,1,255,255,255,255,255,255,255,255,1,255,255,255,255,255,120,120,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,1,255,1,255,1,255,1,255,255,255,255,255,255,255,255,1,255,255,1,1,1,1,255,255,255,255,255,255,255,1,1,1,1,255,255,1,1,255,255,255,255,255,255,1,255,255,1,1,255,1,255,1,255,255,1,1,255,1,1,1,255,1,1,1,255,1,255,255,255,1,255,1,255,255,255,255,255,255,255,255,255,1,1,1,1,1,1,1,1,1,1,255,255,255,255,255,120,120,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,1,255,1,255,1,255,1,255,255,255,1,255,1,1,1,1,255,255,1,1,1,1,1,1,255,255,255,255,255,255,255,255,255,255,1,1,255,255,255,1,1,1,255,1,255,1,255,255,255,255,1,255,255,1,255,255,255,255,1,255,255,1,255,255,255,1,1,255,1,1,255,1,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,120,120,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,1,255,1,255,1,255,1,255,255,1,1,1,1,255,255,255,255,1,1,1,1,1,255,1,1,1,255,255,255,255,1,1,1,1,1,255,255,255,1,1,255,1,255,1,255,255,1,255,255,255,1,255,255,255,1,255,255,255,1,255,255,1,1,1,255,1,255,1,255,1,255,1,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,120,120,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,1,255,1,255,1,255,1,255,1,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,1,1,255,255,255,255,255,255,255,255,255,1,1,255,255,1,1,1,255,255,255,1,255,255,1,255,255,255,255,1,255,255,1,255,255,1,255,255,255,1,255,1,255,1,255,1,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,120,120,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,1,255,1,255,1,255,1,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,1,1,1,1,1,1,1,1,1,1,1,255,255,255,255,255,1,255,1,1,255,255,255,1,255,255,1,1,255,255,255,1,255,255,1,1,1,255,1,255,255,255,1,255,1,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120
    };
    int key = 0;

    //functions
    void ePrintImage(bool clear) {
        int counter = 0;
        sFrameCounter++;
        if (frameDelay != 0) {
            Sleep(frameDelay);
        }
        if (clear) {
            system("CLS");
        }
    }

    void eSetPixleSize(int _y = pixelSizeY, int _x = pixelSizeX) {
        CONSOLE_FONT_INFOEX cfi;
        cfi.cbSize = sizeof(cfi);
        cfi.nFont = 0;
        cfi.dwFontSize.X = _x;
        cfi.dwFontSize.Y = _y;
        cfi.FontFamily = FF_DONTCARE;
        cfi.FontWeight = FW_NORMAL;
        wcscpy_s(cfi.FaceName, L"Consolas");//font type
        SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
    }

    void eDrawPixle(int color) {
        SetConsoleTextAttribute(hConsole, color);
        /*if (color = !eLastColor) //unfinished optimization attempt
        {
            SetConsoleTextAttribute(hConsole, color);
        }*/
        cout << " ";
        eLastColor = color;
        //Sleep(1); //to see whats going on with the rendering
    }

    void eDrawRow(int draws[rowLenght], bool finalRow) {
        for (int i = 0; i < rowLenght; i++) {
            eDrawPixle(draws[i]);
        }
        if (finalRow == false) {
            cout << "\n";
        }
    }

    void sDrawImage(int image[vertLenght][rowLenght], bool clear) {                 //put an image on the screen (render a frame)
        for (int i = 0; i < vertLenght; i++) {
            eDrawRow(image[i], ((i + 1) == vertLenght));
        }
        ePrintImage(clear);
    }

    void sPaint(int image[vertLenght][rowLenght], int color_) {                     //paint the whole image (for background/clearing image)
        for (int v = 0; v < vertLenght; v++) {
            for (int r = 0; r < rowLenght; r++) {
                image[v][r] = color_;
            }
        }
    }

    void sDraw(int image[vertLenght][rowLenght], int color_, int row_, int vert_) { //draw something onto the image
        image[vert_][row_] = color_;
    }

    void sOverwriteImage(int target[vertLenght][rowLenght], int write[vertLenght][rowLenght]) {
        for (int i = 0; i < vertLenght * rowLenght; i++) {
            target[0][i] = write[0][i];
        }
    }

    //uStuff here (your variables & functions)
    int uLocationY = 25;
    int uLocationX = 8;
    int backgroundColor = 255;
    int drawColor = 64;
    bool render = false;
    bool collision = true;

    bool uCanMove(int direction, int image[vertLenght][rowLenght]) {                //collision check
        if (!collision) {
            return 1;
        }
        switch (direction) {
        case 80:
            if (image[uLocationY + 1][uLocationX] == backgroundColor) {
                return  1;
            }
            else {
                return  0;
            }
            break;
        case 72:
            if (image[uLocationY - 1][uLocationX] == backgroundColor) {
                return  1;
            }
            else {
                return  0;
            }
            break;
        case 77:
            if (image[uLocationY][uLocationX + 1] == backgroundColor) {
                return  1;
            }
            else {
                return  0;
            }
            break;
        case 75:
            if (image[uLocationY][uLocationX - 1] == backgroundColor) {
                return  1;
            }
            else {
                return  0;
            }
            break;
        default:
            break;
        }
    }
public:
    //SEQUENCE HERE
    void run() {
        eSetPixleSize();
        ePrintImage(true);
        sOverwriteImage(eImg, eLevelImg);
        sDraw(eImg, drawColor, uLocationX, uLocationY);
        sDrawImage(eImg, false);
        render = false;
        while (!((uLocationX == 94 && uLocationY == 14) || (uLocationX == 94 && uLocationY == 15))) {  //finish condition
            key = _getch();
            switch (key) {
            case 80:
                if (uCanMove(80, eLevelImg)) {
                    uLocationY++;
                    render = true;
                }
                break;
            case 72:
                if (uCanMove(72, eLevelImg)) {
                    uLocationY--;
                    render = true;
                }
                break;
            case 77:
                if (uCanMove(77, eLevelImg)) {
                    uLocationX++;
                    render = true;
                }
                break;
            case 75:
                if (uCanMove(75, eLevelImg)) {
                    uLocationX--;
                    render = true;
                }
                break;
            }
            if (uLocationX == 32 && uLocationY == 9) { //open door on trigger
eLevelImg[14][94] = backgroundColor;
eLevelImg[15][94] = backgroundColor;
            }
            if (render) {
                ePrintImage(true);
                sOverwriteImage(eImg, eLevelImg);
                sDraw(eImg, drawColor, uLocationX, uLocationY);
                sDrawImage(eImg, false);
                render = false;
            }
        }
        eSetPixleSize(SIZE_YFONT, SIZE_XFONT);
    }
}
minigame;



//MAKE TEXT ADVENTURE HERE ______________________________________________________________________________________________________________________________________

//DIALOG OBJECTS
Dialog intro("For two years now the USA's toughest Special Forces unit has been trying to invade the Soviet Union,\n"
    "running over forests, mountains through the desert and fighting endless battles, losing some good men along the way,\n"
    "but the two remaining soldiers Captain Johnes and Master Sergeant Miller have achieved their goal....\n"
    "now it's 1982 The Spec ops Delta froces have broken through the enemy lines and are now in a secret camp of the Soviet Union,\n"
    "still searching for the bunker to secure the Big mm and disarm it, putting an end to the war.\n"
    "Now it's your turn, are you ready to sacrifice your life for the freedom of the United Nations\n"
    "together with Captain Johnes and secure the atomic bomb and save all Civilians!\n"
    "Are you Ready Master Sergeant Miller ?", "yes");

Dialog hack("You need to unlock the PC fast, or the humanity is doomed.\n"
    "Then you remember the device that Johnes gave you before the operation, you need to plug it into the computer and\n"
    "start hacking through the lock.", "hack");

Dialog ending("Congratulations Master Sergeant Miller, thanks to your brave efforts you saved the Civilians and the United Nations, you can be proud of yourselve!\n"
    "Your reinforcements captured the Soviet base and helicoptered them to safety, they were dropped off at home,\n"
    "received their medal from the President and can now relax.\n"
    "A week later a report about the two heroes comes on television, but for protection no one knows who the two heroes were, but one knows, you the hero Miller.\n"
    "End.", "[restart]", "[leave]");

Dialog doors("Fast find the server so you can stop a nuclear disaster.\n"
    "In front of are two doors, which one would you like to pick?", "[storage]", "[server room]");

Dialog item("You have gone into the storage; in it you shoved a few bags of food out of the way to reveal a bunch of wires behind a meat bag.", "[take]", "[go back]");

Dialog broken("You need a wire to connect the server to your device. You must go back to find a wire!", "back");

Dialog emptyRoom("Here is nothing, besides a thew pieces of meat, looks like the food storage. Go back and look in another room.", "back");

//SEQUENCE FUNCTIONS
//prototypes
void fStart();
void fDoors();
void fStorage();
void fServerRoom();
void fEnding();
void fBroken();
void fEmpty();

//definitions
void fStart() {
    stats.location = "Frontline Soviet Union";
    stats.date = "10-30-1982";
    intro.run();
    fDoors();
}

void fDoors() {
    stats.location = "Soviet Nuclear Base";
    stats.date = "10-31-1982";
    if (!stats.hasItem("M4-A1")) {
        stats.addItem("M4-A1");
    }
    switch (doors.run()) {
    case 0:
        fStorage();
    case 1:
        fServerRoom();
    }
}

void fStorage() {
    stats.location = "Storage Room";
    if (!stats.hasItem("Wire")) {
        switch (item.run()) {
        case 0:
            stats.addItem("Wire");
        case 1:
            fDoors();
        }
    }
    else {
        fEmpty();
    }
}

void fServerRoom() {
    stats.location = "Server Room";
    if (stats.hasItem("Wire")) {
        hack.run();
        minigame.run();
        fEnding();
    }
    else {
        fBroken();
    }
}

void fBroken() {
    broken.run();
    fDoors();
}

void fEmpty() {
    emptyRoom.run();
    fDoors();
}

void fEnding() {
    stats.location = "USA";
    stats.date = "11-2-1982";
    stats.removeItem("M4-A1");
    stats.removeItem("Wire");
    stats.addItem("Medal of Honor");
    switch (ending.run()) {
    case 0:
        stats.removeItem("Medal of Honor");
        fStart();
    case 1:
        break;
    }
}

//END _________________________________________________________________________________________________________________________________________________



int main() {                                                    //initialize font, & fullscreen then run start function
    if (FULLSCREEN) {
        SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);
    }
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = SIZE_XFONT;
    cfi.dwFontSize.Y = SIZE_YFONT;
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    wcscpy_s(cfi.FaceName, FONT);
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
    fStart();
}