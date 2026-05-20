//Library
#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

// ========================================
// linked list inventorynya
// ========================================

struct ItemNode
{
    string itemName;
    ItemNode *next;
};

struct Inventory
{
    ItemNode *head;

    void init()
    {
        head = NULL;
    }

    void addItem(string item)
    {
        ItemNode *newItem = new ItemNode;

        newItem->itemName = item;
        newItem->next = NULL;

        if (head == NULL)
        {
            head = newItem;
        }
        else
        {
            ItemNode *temp = head;

            while (temp->next != NULL)
            {
                temp = temp->next;
            }

            temp->next = newItem;
        }
    }

    void showInventory()
    {
        ItemNode *temp = head;

        cout << "ITEM : ";

        if (temp == NULL)
        {
            cout << "KOSONG";
        }

        int nomor = 1;

        while (temp != NULL)
        {
            cout << "[" << nomor << "] " << temp->itemName;

            if (temp->next != NULL)
            {
                cout << " | ";
            }

            temp = temp->next;
            nomor++;
        }

        cout << endl;
    }

    int countItem()
    {
        int total = 0;

        ItemNode *temp = head;

        while (temp != NULL)
        {
            total++;
            temp = temp->next;
        }

        return total;
    }

    bool useSelectedItem(int pilihan, string &item)
    {
        if (head == NULL)
        {
            return false;
        }

        ItemNode *temp = head;
        ItemNode *prev = NULL;

        int nomor = 1;

        while (temp != NULL)
        {
            if (nomor == pilihan)
            {
                item = temp->itemName;

                if (prev == NULL)
                {
                    head = temp->next;
                }
                else
                {
                    prev->next = temp->next;
                }

                delete temp;
                return true;
            }

            prev = temp;
            temp = temp->next;
            nomor++;
        }

        return false;
    }
};

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

