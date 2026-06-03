#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>

using namespace std;

// ========================================
// warna buat uinya
// ========================================

void setColor(int warna)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), warna);
}

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
        cout << endl;

        while (temp != NULL)
        {
            cout << "[" << nomor << "] "
                << temp->itemName
                << endl;

            temp = temp->next;
            nomor++;
        }
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

    ItemNode* useSelectedItem(int pilihan, string &item)
    {
        ItemNode *temp = head;
        int nomor = 1;

        while (temp != NULL)
        {
            if (nomor == pilihan)
            {
                item = temp->itemName;
                return temp;
            }

            temp = temp->next;
            nomor++;
        }

        return NULL;
    }

    void removeNode(ItemNode* target)
    {
        if (head == NULL || target == NULL)
        {
            return;
        }

        ItemNode *temp = head;
        ItemNode *prev = NULL;

        while (temp != NULL)
        {
            if (temp == target)
            {
                if (prev == NULL)
                {
                    head = temp->next;
                }
                else
                {
                    prev->next = temp->next;
                }

                delete temp;
                return;
            }

            prev = temp;
            temp = temp->next;
        }
    }

    ItemNode* getRandomNode(string &itemName)
    {
        if (head == NULL)
        {
            return NULL;
        }

        int total = countItem();

        int randomIndex = rand() % total;

        ItemNode* temp = head;

        for (int i = 0; i < randomIndex; i++)
        {
            temp = temp->next;
        }

        itemName = temp->itemName;

        return temp;
    }
};

struct BulletStack
{
    int top;
    int bullet[10];

    void init()
    {
        top = -1;
    }

    bool isEmpty()
    {
        return top == -1;
    }

    void push(int value)
    {
        top++;
        bullet[top] = value;
    }

    int pop()
    {
        int value = bullet[top];
        top--;

        return value;
    }

    int totalBullet()
    {
        return top + 1;
    }

    void peekBullet()
    {   
        cout << "\nSCANNER MEMBACA...\n";

        Sleep(1000);

        if (bullet[top] == 1)
        {
            setColor(12);
            cout << "PELURU TERATAS : LIVE\n";
        }
        else
        {
            setColor(8);
            cout << "PELURU TERATAS : BLANK\n";
        }

        setColor(7);
    }

    void scanRemainingBullet()
    {
        int live = 0;
        int blank = 0;

        // hitung seluruh peluru tersisa

        for (int i = 0; i <= top; i++)
        {
            if (bullet[i] == 1)
            {
                live++;
            }
            else
            {
                blank++;
            }
        }

        cout << "\nPROBABILITY SCANNER MEMBACA...\n";

        Sleep(1000);

        setColor(12);

        cout << "LIVE SHELL  : "
            << live
            << endl;

        setColor(8);

        cout << "BLANK SHELL : "
            << blank
            << endl;

        setColor(7);
    }

    void swapBulletType()
    {
        if (isEmpty())
        {
            return;
        }

        bullet[top] = 1 - bullet[top];
    }

    void randomizeBullet()
    {
        int live = 0;
        int blank = 0;

        // hitung isi chamber

        for (int i = 0; i <= top; i++)
        {
            if (bullet[i] == 1)
            {
                live++;
            }
            else
            {
                blank++;
            }
        }

        // ========================================
        // SEMUA LIVE
        // ========================================

        if (live == top + 1)
        {
            int randomBlank = rand() % (top + 1);

            bullet[randomBlank] = 0;
        }

        // ========================================
        // SEMUA BLANK
        // ========================================

        else if (blank == top + 1)
        {
            int randomLive = rand() % (top + 1);

            bullet[randomLive] = 1;
        }

        // ========================================
        // SHUFFLE POSISI
        // ========================================

        for (int i = 0; i <= top; i++)
        {
            int randomIndex = rand() % (top + 1);

            swap(bullet[i], bullet[randomIndex]);
        }
    }

    bool getBulletByIndex(int index, int &result)
    {
        if (index < 1 || index > totalBullet())
            return false;

        result = bullet[index - 1]; // karena array 0-based
        return true;
    }
};

// ========================================
// player setak
// ========================================

const int MAX_HP = 4;

struct Player
{
    string name;
    int hp;
    int ap;
    bool alive;

    bool kenaDamage;
    bool skipTurn;
    bool supercharged;
    bool stabilizer;
    bool extraTurn;
    int dominatrixSequence; 
    bool reflectionField;
    int dominatrixMode; 
    bool hyperbarrel;
    bool chaosState;

    bool rogueProtocol;
    bool paradoxRound;

    bool reflectionSustain;
    bool scannerAggressive;
    bool scannerDefensive;
    bool overdriveDisrupt;
    bool nanoShield;
    bool forceShootSelf;
    bool forceShootEnemy;

    Inventory inventory;
};

void tampilkanStatus(Player* p)
{
    bool adaStatus = false;

    // ========================================
    // BUFF
    // ========================================

    if (p->supercharged)
    {
        setColor(6);
        cout << "[SUPERCHARGED] ";
        adaStatus = true;
    }

    if (p->stabilizer)
    {
        setColor(10);
        cout << "[STABILIZED] ";
        adaStatus = true;
    }

    if (p->hyperbarrel)
    {
        setColor(14);
        cout << "[HYPERACCELERATION] ";
        adaStatus = true;
    }

    // ========================================
    // CONTROL
    // ========================================

    if (p->skipTurn)
    {
        setColor(13);
        cout << "[LOCKED] ";
        adaStatus = true;
    }

    if (p->dominatrixSequence)
    {
        setColor(13);
        cout << "[DOMINATED] ";
        adaStatus = true;
    }

    if (p->overdriveDisrupt)
    {
        setColor(13);
        cout << "[DISRUPTED] ";
        adaStatus = true;
    }

    // ========================================
    // DEFENSE
    // ========================================

    if (p->reflectionField)
    {
        setColor(11);
        cout << "[REFLECTION] ";
        adaStatus = true;
    }

    if (p->nanoShield)
    {
        setColor(11);
        cout << "[NANOSHIELD] ";
        adaStatus = true;
    }

    if (p->extraTurn)
    {
        setColor(9);
        cout << "[OVERDRIVE] ";
        adaStatus = true;
    }

    // ========================================
    // CHAOS
    // ========================================

    if (p->rogueProtocol)
    {
        setColor(4);
        cout << "[ROGUE] ";
        adaStatus = true;
    }

    if (p->paradoxRound)
    {
        setColor(12);
        cout << "[PARADOX] ";
        adaStatus = true;
    }

    if (p->chaosState)
    {
        setColor(12);
        cout << "[CHAOS] ";
        adaStatus = true;
    }

    // ========================================
    // NO STATUS
    // ========================================

    if (!adaStatus)
    {
        setColor(8);
        cout << "[NORMAL]";
    }

    setColor(7);
}

// ========================================
// generate peluru
// ========================================

void generateBullet(BulletStack &stack)
{
    stack.init();

    int bulletArray[6];

    // jumlah live lebih balance
    // 2 - 4 live shell

    int liveBullet = 2 + rand() % 3;

    int blankBullet = 6 - liveBullet;

    // isi semua blank dulu

    for (int i = 0; i < 6; i++)
    {
        bulletArray[i] = 0;
    }

    // random posisi live shell

    int placed = 0;

    while (placed < liveBullet)
    {
        int pos = rand() % 6;

        if (bulletArray[pos] == 0)
        {
            bulletArray[pos] = 1;
            placed++;
        }
    }

    // push ke stack

    for (int i = 0; i < 6; i++)
    {
        stack.push(bulletArray[i]);
    }

    // info chamber

    cout << "\nSISTEM MEMUAT PELURU...\n";

    Sleep(1000);

    cout << "LIVE SHELL  : "
         << liveBullet << endl;

    cout << "BLANK SHELL : "
         << blankBullet << endl;

    Sleep(1500);
}

// ========================================
// UI gamenya
// ========================================

void tampilkanUI(int pilihan, Player *current, Player *enemy, BulletStack &bullet)
{
    system("cls");

    cout << "\n";
    cout << "=====================================================\n";
    cout << "                    NEUROTRIGGER\n";
    cout << "=====================================================\n\n";

    // INFO PLAYER

    setColor(10);
    cout << "PLAYER : " << current->name << "\n";

    setColor(7);
    cout << current->name << " HP : " << current->hp;

    if (current->ap > 0)
    {
        setColor(11);
        cout << " (" << current->ap << " AP)";
        setColor(7);
    }

    cout << "\nSTATUS " << current->name << " : ";
    tampilkanStatus(current);

    cout << endl;
    
    setColor(4);
    cout << "\nENEMY : " << enemy->name << "\n";

    setColor(7);
    cout << enemy->name << " HP : " << enemy->hp;

    if (enemy->ap > 0)
    {
        setColor(11);
        cout << " (" << enemy->ap << " AP)";
        setColor(7);
    }

    cout << "\nSTATUS " << enemy->name << " : ";
    tampilkanStatus(enemy);

    cout << endl;

    // INFO CHAMBER

    setColor(14);
    cout << "\nSISA PELURU : " << bullet.totalBullet() << endl;

    setColor(7);

    cout << "\n";

    // BUTTON UI

    if (pilihan == 0)
        setColor(12);
    else
        setColor(7);

    cout << "====================";

    setColor(7);

    cout << "     ";

    if (pilihan == 1)
        setColor(12);
    else
        setColor(7);

    cout << "====================\n";

    if (pilihan == 0)
        setColor(12);
    else
        setColor(7);

    cout << "|                  |";

    setColor(7);

    cout << "     ";

    if (pilihan == 1)
        setColor(12);
    else
        setColor(7);

    cout << "|                  |\n";

    if (pilihan == 0)
        setColor(12);
    else
        setColor(7);

    cout << "|      TEMBAK      |";

    setColor(7);

    cout << "     ";

    if (pilihan == 1)
        setColor(12);
    else
        setColor(7);

    cout << "|       ITEM       |\n";

    if (pilihan == 0)
        setColor(12);
    else
        setColor(7);

    cout << "|                  |";

    setColor(7);

    cout << "     ";

    if (pilihan == 1)
        setColor(12);
    else
        setColor(7);

    cout << "|                  |\n";

    if (pilihan == 0)
        setColor(12);
    else
        setColor(7);

    cout << "====================";

    setColor(7);

    cout << "     ";

    if (pilihan == 1)
        setColor(12);
    else
        setColor(7);

    cout << "====================\n";

    // CONTROL

    setColor(8);

    cout << "\nA = KIRI | D = KANAN";
    cout << "\nENTER = ACTION\n";

    setColor(7);
}

// ========================================
// UI nembak
// ========================================

int menuTembak(Player* current, Player* enemy, BulletStack& bullet)
{
    int pilihan = 0;

    while (true)
    {
        system("cls");

        cout << "\n=========== TARGET ===========" << endl;

        // TEMBAK LAWAN
        if (pilihan == 0)
            setColor(12);
        else
            setColor(7);

        cout << "\n[ TEMBAK LAWAN ]";

        // TEMBAK DIRI SENDIRI
        if (pilihan == 1)
            setColor(12);
        else
            setColor(7);

        cout << "\n[ TEMBAK DIRI SENDIRI ]";

        setColor(8);

        cout << "\n\nA = ATAS | D = BAWAH";
        cout << "\nENTER = ACTION";
        cout << "\nESC = KEMBALI";

        setColor(7);

        char input = _getch();

        Sleep(80);

        // kanan
        if (input == 'd' || input == 'D')
        {
            pilihan++;

            if (pilihan > 1)
                pilihan = 0;
        }

        // kiri
        else if (input == 'a' || input == 'A')
        {
            pilihan--;

            if (pilihan < 0)
                pilihan = 1;
        }

        // enter
        else if (input == 13)
        {
            return pilihan;
        }

        // ESC
        else if (input == 27)
        {
            return -1;
        }
    }
}