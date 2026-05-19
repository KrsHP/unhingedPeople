//Library
#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

//Fungsi Ngubah Warna UI Battle
void setColor(int warna){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), warna);
}

//Fungsi Ubah Warna UI dan Layout
void changeColor(string text, bool pilihan){
    if(pilihan){
    setColor(12);
    }else{
        setColor(7);
    }

    cout << "====================\n";
    cout << "|                  |\n";

    if (text=="TEMBAK"){
        cout << "|      TEMBAK      |\n";
    }else{
        cout << "|       ITEM       |\n";
    }

    cout << "|                  |\n";
    cout << "====================\n";

    setColor(7);
}


//Fungsi UI Battle
void tampilkanUI(int pilihan)
{
    system("cls");

    cout << "\n\n";
    cout << "            BUCKSHOT ROULLETE\n\n";

    //Baris Atas

    if (pilihan == 0){
        setColor(12);
    }else{
        setColor(7);
    }

    cout << "====================";

    setColor(7);

    cout << "     ";

    if (pilihan == 1){
        setColor(12);
    }
    else{
        setColor(7);
    }

    cout << "====================\n";

    //Baris Padding

    if (pilihan == 0){
        setColor(12);
    }
    else{
        setColor(7);
    }

    cout << "|                  |";

    setColor(7);

    cout << "     ";

    if (pilihan == 1){
        setColor(12);
    }
    else{
        setColor(7);
    }

    cout << "|                  |\n";

    //Text

    if (pilihan == 0){
        setColor(12);
    }else{
        setColor(7);
    }

    cout << "|      TEMBAK      |";

    setColor(7);

    cout << "     ";

    if (pilihan == 1){
        setColor(12);
    }else{
        setColor(7);
    }

    cout << "|       ITEM       |\n";

    //Baris Padding

    if (pilihan == 0){
        setColor(12);
    }else{
        setColor(7);
    }

    cout << "|                  |";

    setColor(7);

    cout << "     ";

    if (pilihan == 1){
        setColor(12);
    }else{
        setColor(7);
    }

    cout << "|                  |\n";

    //Baris Bawah

    if (pilihan == 0){
        setColor(12);
    }else{
        setColor(7);
    }

    cout << "====================";

    setColor(7);

    cout << "     ";

    if (pilihan == 1){
        setColor(12);
    }else{
        setColor(7);
    }

    cout << "====================\n";

    setColor(7);

    cout << "\n";
    cout << "Gunakan PANAH KIRI / KANAN\n";
    cout << "ENTER untuk memilih\n";
}


//Run Game
int main(){

    int pilihan = 0;
    
    //Perulangan Action Battle
    while(true){

        //Get Input User
        tampilkanUI(pilihan);
        int input = _getch();

        if (input == 224){
            input = _getch();

            //Bila panah Kanan
            if (input == 77){
                pilihan++;
                
                if (pilihan > 1){
                    pilihan = 0;
                }
            }
            //Bila Panah Kiri
            else if(input == 75){
                 pilihan --;

                if (pilihan < 0){
                pilihan = 1;
                }
            }
        }

        //Enter
        else if(input == 13){
            system("cls");

            if (pilihan == 0){
                setColor(12);
                cout << "\nKAMU MEMILIH TEMBAK!\n";
            }else{
                setColor(12);
                cout << "\nKAMU MEMILIH ITEM!\n";
            }

            setColor(7);
            system("pause");
        }
    }

    return 0;
}

