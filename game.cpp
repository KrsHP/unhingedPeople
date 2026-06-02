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
// main
// ========================================

// int main()
// {   
//     srand(time(0));

//     // buat tree mushu

//     EnemyTree* root = buildEnemyTree();
//     EnemyTree* currentEnemy = root;

//     // player

//     Player player;

//     player.hp = 4;
//     player.alive = true;   

//     player.ap = 0;
//     player.skipTurn = false;
//     player.stabilizer = false;
//     player.supercharged = false;
//     player.extraTurn = false;
//     player.dominatrixSequence = false;
//     player.reflectionField = false;
//     player.hyperbarrel = false;
//     player.chaosState = false;

//     player.rogueProtocol = false;
//     player.paradoxRound = false;

//     player.overdriveDisrupt = false;
//     player.nanoShield= false;
//     player.reflectionSustain = false;

//     player.inventory.init();

//     cout << "MASUKKAN NAMA PLAYER : ";
//     cin >> ws;
//     getline(cin, player.name);

//     // loop mush

//     for (int level = 0; level < 4 && player.alive; level++)
//     {
//         system("cls");

//         setColor(4);
//         cout << "\n=====================================\n";
//         cout << "               STAGE " << level + 1 << endl;
//         cout << "=====================================\n";
//         setColor(7);

//         // ambil nama musuh
//         string enemyName = currentEnemy->enemyName;

//         Player dealer;

//         dealer.name = enemyName;
//         dealer.hp = 4;
//         dealer.alive = true;

//         dealer.ap = 0;
//         dealer.skipTurn = false;
//         dealer.stabilizer = false;
//         dealer.supercharged = false;
//         dealer.extraTurn = false;
//         dealer.dominatrixSequence = false;
//         dealer.reflectionField = false;
//         dealer.kenaDamage = false;
//         dealer.hyperbarrel = false;
//         dealer.chaosState = false;
        
//         dealer.rogueProtocol = false;
//         dealer.paradoxRound = false;

//         dealer.overdriveDisrupt = false;
//         dealer.nanoShield= false;
//         dealer.reflectionSustain = false;
//         dealer.forceShootSelf = false;
//         dealer.forceShootEnemy = false;
//         dealer.scannerAggressive = false;
//         dealer.scannerDefensive = false;

//         dealer.inventory.init();

//         bool rareSpawnedEnemy = false;

//         for (int i = 0; i < 5; i++) 
//         {
//             string itemName = generateRandomItem(rareSpawnedEnemy);

//             dealer.inventory.addItem(itemName);
//         }

//         // reset status aktif

//         player.ap = 0;

//         player.skipTurn = false;

//         player.supercharged = false;
//         player.stabilizer = false;
//         player.hyperbarrel = false;

//         player.extraTurn = false;

//         player.dominatrixSequence = false;
//         player.dominatrixMode = 0;

//         player.reflectionField = false;
//         player.reflectionSustain = false;

//         player.rogueProtocol = false;
//         player.paradoxRound = false;

//         dealer.ap = 0;

//         dealer.skipTurn = false;

//         dealer.supercharged = false;
//         dealer.stabilizer = false;
//         dealer.hyperbarrel = false;

//         dealer.extraTurn = false;

//         dealer.dominatrixSequence = false;
//         dealer.dominatrixMode = 0;

//         dealer.reflectionField = false;
//         dealer.reflectionSustain = false;

//         dealer.rogueProtocol = false;
//         dealer.paradoxRound = false;

//         dealer.forceShootEnemy = false;
//         dealer.forceShootSelf = false;

//         // reset HP player saat musuh baru

//         player.hp = 4;

//         // reset item player saat musuh baru

//         player.inventory.init();

//         cout << "\nITEM DIPEROLEH :\n";

//         bool rareSpawned = false;

//         for (int i = 0; i < 5; i++)
//         {
//             string itemName =
//                 generateRandomItem(rareSpawned);

//             player.inventory.addItem(itemName);

//             cout << "- "
//                 << itemName;

//             // tampilkan label rare

//             for (int j = 0; j < 20; j++)
//             {
//                 if (itemList[j].itemName == itemName)
//                 {
//                     if (itemList[j].rare)
//                     {
//                         setColor(13);

//                         cout << " [SPECIAL]";

//                         setColor(7);
//                     }

//                     break;
//                 }
//             }

//             cout << endl;
//         }

//         // setak pluru

//         BulletStack bullets;
//         bullets.init();

//         generateBullet(bullets);

//         bool doubleDamage = false;

//         setColor(4);

//         cout << "\nMUSUH STAGE " 
//             << level+1
//             << " : "
//             << dealer.name << endl;
        
//         setColor(7);

//         Sleep(1500);
//         // nemak loopnya

//         while (player.alive && dealer.alive)
// {
//     // reload jika peluru habis

//     if (bullets.isEmpty())
//     {
//         system("cls");

//         setColor(14);

//         cout << "\n====================================\n";
//         cout << "           CHAMBER KOSONG\n";
//         cout << "====================================\n\n";

//         setColor(7);

//         cout << "PELURU AKAN DIISI KEMBALI...\n";

//         Sleep(1500);

//         generateBullet(bullets);

//         player.chaosState = false;
//         dealer.chaosState = false;

//         // ITEM REWARD ROUND BARU

//         string itemPlayer = getNewItem();
//         string itemEnemy = getNewItem();

//         player.inventory.addItem(itemPlayer);
//         dealer.inventory.addItem(itemEnemy);

//         cout << "\n" << player.name << " mendapatkan item: "
//             << itemPlayer;

//         // cek apakah rare

//         for (int i = 0; i < 20; i++)
//         {
//             if (itemList[i].itemName == itemPlayer)
//             {
//                 if (itemList[i].rare)
//                 {
//                     setColor(13);

//                     cout << " [SPECIAL]";

//                     setColor(7);
//                 }
//                 break;
//             }
//         }

//         cout << endl;
//         system("pause");
//     }

//     int pilihan = 0;
//     bool playerSudahMenembak = false;

//     while (true)
//     {   
//         tampilkanUI(pilihan, &player, &dealer, bullets);

//         char input = _getch();

//         Sleep(80);

//         if (input == 'd' || input == 'D')
//         {
//             pilihan++;

//             if (pilihan > 1)
//             {
//                 pilihan = 0;
//             }
//         }

//         else if (input == 'a' || input == 'A')
//         {
//             pilihan--;

//             if (pilihan < 0)
//             {
//                 pilihan = 1;
//             }
//         }

//         else if (input == 13)
//         {   
//             // ========================================
//             // TEMBAK
//             // ========================================

//             if (pilihan == 0)
//             {       
//                 system("cls");

//                 bool hasilLive;

//                 int targetPilihan = menuTembak(
//                     &player,
//                     &dealer,
//                     bullets
//                 );

//                 // ESC
//                 if (targetPilihan == -1)
//                 {
//                     continue;
//                 }

//                 // =========================
//                 // SYNAPSE LOCK CHECK
//                 // =========================

//                 if (player.skipTurn)
//                 {
//                     player.skipTurn = false;

//                     if (player.dominatrixSequence)
//                     {
//                         if (player.dominatrixMode == 1)
//                         {
//                             setColor(13);

//                             cout << "\nDOMINATRIX: 'DIPAKSA MENEMBAK DIRI SENDIRI!'\n";

//                             Sleep(1000);

//                             setColor(7);

//                             cout << "\n"
//                                 << player.name
//                                 << " TIDAK BISA MENEMBAK KARENA TRIGGER TERKUNCI!\n";
                            
                            
//                         }

//                         else if (player.dominatrixMode == 2)
//                         {
//                             setColor(13);

//                             cout << "\nDOMINATRIX: 'DIPAKSA MENEMBAK LAWAN!'\n";

//                             Sleep(1000);

//                             setColor(7);

//                             cout << "\n"
//                                 << player.name
//                                 << " TIDAK BISA MENEMBAK KARENA TRIGGER TERKUNCI!\n";
//                         }

//                         player.dominatrixSequence = false;
//                         player.dominatrixMode = 0;
//                     }

//                     else
//                     {
//                         cout << "\n"
//                             << player.name
//                             << " TIDAK BISA MENEMBAK KARENA TRIGGER TERKUNCI!\n";
//                     }

//                     if (player.extraTurn)
//                     {
//                         if (!dealer.alive || !player.alive)
//                         {
//                             break;
//                         }

//                         player.extraTurn = false;
//                         playerSudahMenembak = false;

//                         cout << "\nOVERDRIVE AKTIF!\n";
//                         cout << player.name
//                             << " MENDAPATKAN TURN TAMBAHAN!\n";

//                         system("pause");

//                         if (bullets.totalBullet() == 0)
//                         {
//                             break;
//                         }

//                         continue;
//                     }
//                     system("pause");

//                     playerSudahMenembak = true;

//                     break;
//                 }

//                 // =========================
//                 // DOMINATRIX CHECK
//                 // =========================

//                 if (player.dominatrixSequence)
//                 {
//                     if (player.dominatrixMode == 1)
//                     {
//                         setColor(13);

//                         cout << "\nDOMINATRIX: 'DIPAKSA MENEMBAK DIRI SENDIRI!'\n";

//                         setColor(7);

//                         targetPilihan = 1;
//                     }

//                     else if (player.dominatrixMode == 2)
//                     {
//                         setColor(13);

//                         cout << "\nDOMINATRIX: 'DIPAKSA MENEMBAK LAWAN!'\n";

//                         setColor(7);

//                         targetPilihan = 0;
//                     }

//                     player.dominatrixSequence = false;
//                     player.dominatrixMode = 0;
//                 }

//                 // =========================
//                 // TEMBAK MUSUH
//                 // =========================

//                 cout << endl;
                
//                 if (targetPilihan == 0)
//                 {   
//                     hasilLive = shoot(
//                         &player,
//                         &dealer,
//                         bullets,
//                         doubleDamage
//                     );

//                     playerSudahMenembak = true;
//                 }

//                 // =========================
//                 // TEMBAK DIRI SENDIRI
//                 // =========================

//                 else if (targetPilihan == 1)
//                 {   
//                     shoot(
//                         &player,
//                         &player,
//                         bullets,
//                         doubleDamage
//                     );
                    
//                     playerSudahMenembak = true;
//                 }
//                 system("pause");
//             }

//             // ========================================
//             // ITEM
//             // ========================================

//             else
//             {
//                 if (player.inventory.countItem() == 0)
//                 {   
//                     system("cls");

//                     cout << "\n=====================================================\n";
//                     cout << "                     ITEM LIST\n";
//                     cout << "=====================================================\n";
                    
//                     cout << "\nITEM KOSONG!\n";
//                     system("pause");
//                     continue;
//                 }

//                 int pilihanItem = 0;

//                 while (true)
//                 {
//                     tampilkanUIItem(
//                         pilihanItem,
//                         &player,
//                         &dealer,
//                         bullets
//                     );

//                     char itemInput = _getch();

//                     // =========================
//                     // NAVIGASI BAWAH
//                     // =========================

//                     if (itemInput == 'd' || itemInput == 'D')
//                     {
//                         pilihanItem++;

//                         if (pilihanItem >= player.inventory.countItem())
//                         {
//                             pilihanItem = 0;
//                         }
//                     }

//                     // =========================
//                     // NAVIGASI ATAS
//                     // =========================

//                     else if (itemInput == 'a' || itemInput == 'A')
//                     {
//                         pilihanItem--;

//                         if (pilihanItem < 0)
//                         {
//                             pilihanItem =
//                                 player.inventory.countItem() - 1;
//                         }
//                     }

//                     // =========================
//                     // ESC = KEMBALI
//                     // =========================

//                     else if (itemInput == 27)
//                     {
//                         break;
//                     }

//                     // =========================
//                     // PILIH ITEM
//                     // =========================

//                     else if (itemInput == 13)
//                     {
//                         string item;

//                         ItemNode* node =
//                             player.inventory.useSelectedItem(
//                                 pilihanItem + 1,
//                                 item
//                             );

//                         if (node != NULL)
//                         {
//                             cout << "\n\n"
//                                 << player.name 
//                                 << " MENGGUNAKAN : "
//                                 << item << endl;

//                             bool targetSelf = false;

//                             bool success = useItemEffect(
//                                 item,
//                                 &player,
//                                 &dealer,
//                                 bullets,
//                                 doubleDamage,
//                                 targetSelf,
//                                 false
//                             );

//                             if (success)
//                             {
//                                 player.inventory.removeNode(node);
//                             }
//                             else
//                             {
//                                 cout << "\nITEM TIDAK DIGUNAKAN!\n";
//                             }

//                             // chamber kosong habis purge
//                             if (item == "CHAMBER PURGER" &&
//                                 bullets.totalBullet() == 0)
//                             {
//                                 Sleep(1000);
//                                 break;
//                             }
//                         }

//                         system("pause");
//                         break;
//                     }
//                 }
//             }

//             // ========================================
//             // OVERDRIVE CHECK
//             // ========================================

//             if (playerSudahMenembak)
//             {
//                 if (player.extraTurn)
//                 {
//                     if (!dealer.alive || !player.alive)
//                     {
//                         break;
//                     }

//                     player.extraTurn = false;
//                     playerSudahMenembak = false;

//                     cout << "\nOVERDRIVE AKTIF!\n";
//                     cout << player.name
//                         << " MENDAPATKAN TURN TAMBAHAN!\n";

//                     system("pause");

//                     if (bullets.totalBullet() == 0)
//                     {
//                         break;
//                     }

//                     continue;
//                 }

//                 break;
//             }
//         }
//     }      
//             // ========================================
//             // TURN MUSUH
//             // ========================================
            
//             if (dealer.alive &&
//                 player.alive &&
//                 !bullets.isEmpty())
//             {
                
//                 // inisiasi status musuh

//                 string item;
//                 bool musuhDoubleDamage = false;
//                 bool musuhSudahNembak = false;
//                 bool aiUsedItem = false;

//                 bool lensUsed = false;
//                 bool bulletScanned = false;
//                 bool chamberPurged = false;

//                 bool aiUsedTrackItem = false;
//                 bool aiUsedCounterItem = false;
//                 bool aiUsedDefenseItem = false;
//                 bool aiUsedBuffItem = false;
//                 bool aiUsedManipulationItem = false;
//                 bool aiUsedChaosItem = false;

//                 dealer.forceShootEnemy = false;
//                 dealer.forceShootSelf = false;

//                 while (true)
//                 {   
//                     system("cls");

//                     cout << "\nTURN " << dealer.name << "...\n";
//                     Sleep(1200);
                    
//                     // ========================================
//                     // AI DECISION : USE ITEM?
//                     // 75% chance pakai item
//                     // 25% langsung menembak
//                     // ========================================

//                     if (aiWantsToUseItem(75))
//                     {
//                         // ========================================
//                         // AI : NEURAL LENS
//                         // ========================================

//                         if (!aiUsedItem && !dealer.dominatrixSequence)
//                         {
//                             bool lensUsed = aiTryUseItem(
//                                 dealer,
//                                 player,
//                                 bullets,
//                                 musuhDoubleDamage,
//                                 "NEURAL LENS",
//                                 70,
//                                 aiUsedItem
//                             );

//                             if (lensUsed && !dealer.skipTurn)
//                             {
//                                 // LIVE → tembak lawan

//                                 if (bullets.bullet[bullets.top] == 1)
//                                 {   
//                                     // PLAYER PUNYA REFLECTION

//                                     if (player.reflectionField)
//                                     {
//                                         // PRIORITAS 1 : POLARITY SHIFT 

//                                         if (!aiUsedItem)
//                                         {
//                                             aiTryUseItem(
//                                                 dealer,
//                                                 player,
//                                                 bullets,
//                                                 musuhDoubleDamage,
//                                                 "POLARITY SHIFT",
//                                                 100,
//                                                 aiUsedItem
//                                             );
//                                         }
                                            
//                                         // PRIORITAS 2 : CHAMBER PURGER

//                                         if (!aiUsedItem)
//                                         {
//                                             bool purgerUsed = aiTryUseItem(
//                                                 dealer,
//                                                 player,
//                                                 bullets,
//                                                 musuhDoubleDamage,
//                                                 "CHAMBER PURGER",
//                                                 100,
//                                                 aiUsedItem
//                                             );

//                                             if (purgerUsed && !bullets.isEmpty())
//                                             {
//                                                 chamberPurged = true;

//                                                 int idx = rand() % bullets.totalBullet() + 1;

//                                                 // ====================================
//                                                 // NEXT BULLET ANALYSIS
//                                                 // ====================================

//                                                 // LIVE
//                                                 if (bullets.bullet[bullets.top] == 1 && bullets.bullet[bullets.top] == idx)
//                                                 {
//                                                     dealer.forceShootEnemy = true;

//                                                     // counter reflection
//                                                     if (player.reflectionField)
//                                                     {
//                                                         if (!aiUsedItem)
//                                                         {
//                                                             aiTryUseItem(
//                                                                 dealer,
//                                                                 player,
//                                                                 bullets,
//                                                                 musuhDoubleDamage,
//                                                                 "POLARITY SHIFT",
//                                                                 100,
//                                                                 aiUsedItem
//                                                             );
//                                                         }

//                                                         if (!aiUsedItem)
//                                                         {
//                                                             aiTryUseItem(
//                                                                 dealer,
//                                                                 player,
//                                                                 bullets,
//                                                                 musuhDoubleDamage,
//                                                                 "CHAOS ENGINE",
//                                                                 100,
//                                                                 aiUsedItem
//                                                             );
//                                                         }
//                                                     }

//                                                     // buff offensive
//                                                     bool supercharged = aiTryUseItem(
//                                                         dealer,
//                                                         player,
//                                                         bullets,
//                                                         musuhDoubleDamage,
//                                                         "SUPERCHARGED PULSE",
//                                                         100,
//                                                         aiUsedItem
//                                                     );

//                                                     if (!supercharged)
//                                                     {
//                                                         aiTryUseItem(
//                                                             dealer,
//                                                             player,
//                                                             bullets,
//                                                             musuhDoubleDamage,
//                                                             "HYPERBARREL ACCELERATOR",
//                                                             100,
//                                                             aiUsedItem
//                                                         );
//                                                     }
//                                                 }

//                                                 // BLANK
//                                                 else if (bullets.bullet[bullets.top] == 0 && bullets.bullet[bullets.top] == idx)
//                                                 {
//                                                     dealer.forceShootSelf = true;

//                                                     aiTryUseItem(
//                                                         dealer,
//                                                         player,
//                                                         bullets,
//                                                         musuhDoubleDamage,
//                                                         "STABILIZER ENERGY",
//                                                         100,
//                                                         aiUsedItem
//                                                     );
//                                                 }
//                                             }
//                                         }

//                                         // PRIORITAS 3 : CHAOS ENGINE

//                                         if (!aiUsedItem)
//                                         {
//                                             aiTryUseItem(
//                                                 dealer,
//                                                 player,
//                                                 bullets,
//                                                 musuhDoubleDamage,
//                                                 "CHAOS ENGINE",
//                                                 100,
//                                                 aiUsedItem
//                                             );
//                                         }
//                                         aiUsedManipulationItem = true;
//                                     } 

//                                     dealer.forceShootEnemy = true;

//                                     bool supercharged = aiTryUseItem(
//                                         dealer,
//                                         player,
//                                         bullets,
//                                         musuhDoubleDamage,
//                                         "SUPERCHARGED PULSE",
//                                         100,
//                                         aiUsedItem
//                                     );

//                                     if (!supercharged) {
//                                         aiTryUseItem(
//                                         dealer,
//                                         player,
//                                         bullets,
//                                         musuhDoubleDamage,
//                                         "HYPERBARREL ACCELERATOR",
//                                         100,
//                                         aiUsedItem
//                                     );
//                                     aiUsedBuffItem = true;
//                                     }
//                                 }

//                                 // BLANK → tembak diri sendiri

//                                 else if (bullets.bullet[bullets.top] == 0)
//                                 {
//                                     dealer.forceShootSelf = true;

//                                     aiTryUseItem(
//                                         dealer,
//                                         player,
//                                         bullets,
//                                         musuhDoubleDamage,
//                                         "STABILIZER ENERGY",
//                                         100,
//                                         aiUsedItem
//                                     );
//                                 }
//                             }
//                             aiUsedTrackItem = true;
//                         }

//                         // ========================================
//                         // AI : PROBABILITY SCANNER
//                         // ========================================

//                         if (!aiUsedItem && bullets.totalBullet() <= 4 && !aiUsedTrackItem && !dealer.dominatrixSequence)
//                         {
//                             bool scannerUsed = aiTryUseItem(
//                                 dealer,
//                                 player,
//                                 bullets,
//                                 musuhDoubleDamage,
//                                 "PROBABILITY SCANNER",
//                                 70,
//                                 aiUsedItem
//                             );

//                             if (scannerUsed && !dealer.skipTurn)
//                             {
//                                 int live = 0;
//                                 int blank = 0;

//                                 countBullet(bullets, live, blank);

//                                 // semua LIVE

//                                 if (live == bullets.totalBullet())
//                                 {
//                                     dealer.scannerAggressive = true;

//                                     // SCANNER AGGRESSIVE MODE

//                                     if (dealer.scannerAggressive)
//                                     {
//                                         dealer.scannerAggressive = false;

//                                         // PLAYER PUNYA REFLECTION

//                                         if (player.reflectionField)
//                                         {
//                                             // PRIORITAS 1 : POLARITY SHIFT 

//                                             if (!aiUsedItem)
//                                             {
//                                                 aiTryUseItem(
//                                                     dealer,
//                                                     player,
//                                                     bullets,
//                                                     musuhDoubleDamage,
//                                                     "POLARITY SHIFT",
//                                                     100,
//                                                     aiUsedItem
//                                                 );
//                                             }
                                                
//                                             // PRIORITAS 2 : CHAMBER PURGER

//                                             if (!aiUsedItem)
//                                             {
//                                                 bool purgerUsed = aiTryUseItem(
//                                                 dealer,
//                                                 player,
//                                                 bullets,
//                                                 musuhDoubleDamage,
//                                                 "CHAMBER PURGER",
//                                                 100,
//                                                 aiUsedItem
//                                             );

//                                                 if (purgerUsed && !bullets.isEmpty())
//                                                 {
//                                                     chamberPurged = true;

//                                                     int idx = rand() % bullets.totalBullet() + 1;

//                                                     // ====================================
//                                                     // NEXT BULLET ANALYSIS
//                                                     // ====================================

//                                                     // LIVE
//                                                     if (bullets.bullet[bullets.top] == 1 && bullets.bullet[bullets.top] == idx)
//                                                     {
//                                                         dealer.forceShootEnemy = true;

//                                                         // counter reflection
//                                                         if (player.reflectionField)
//                                                         {
//                                                             if (!aiUsedItem)
//                                                             {
//                                                                 aiTryUseItem(
//                                                                     dealer,
//                                                                     player,
//                                                                     bullets,
//                                                                     musuhDoubleDamage,
//                                                                     "POLARITY SHIFT",
//                                                                     100,
//                                                                     aiUsedItem
//                                                                 );
//                                                             }

//                                                             if (!aiUsedItem)
//                                                             {
//                                                                 aiTryUseItem(
//                                                                     dealer,
//                                                                     player,
//                                                                     bullets,
//                                                                     musuhDoubleDamage,
//                                                                     "CHAOS ENGINE",
//                                                                     100,
//                                                                     aiUsedItem
//                                                                 );
//                                                             }
//                                                         }

//                                                         // buff offensive
//                                                         bool supercharged = aiTryUseItem(
//                                                             dealer,
//                                                             player,
//                                                             bullets,
//                                                             musuhDoubleDamage,
//                                                             "SUPERCHARGED PULSE",
//                                                             100,
//                                                             aiUsedItem
//                                                         );

//                                                         if (!supercharged)
//                                                         {
//                                                             aiTryUseItem(
//                                                                 dealer,
//                                                                 player,
//                                                                 bullets,
//                                                                 musuhDoubleDamage,
//                                                                 "HYPERBARREL ACCELERATOR",
//                                                                 100,
//                                                                 aiUsedItem
//                                                             );
//                                                         }
//                                                     }

//                                                     // BLANK
//                                                     else if (bullets.bullet[bullets.top] == 0 && bullets.bullet[bullets.top] == idx)
//                                                     {
//                                                         dealer.forceShootSelf = true;

//                                                         aiTryUseItem(
//                                                             dealer,
//                                                             player,
//                                                             bullets,
//                                                             musuhDoubleDamage,
//                                                             "STABILIZER ENERGY",
//                                                             100,
//                                                             aiUsedItem
//                                                         );
//                                                     }
//                                                 }
//                                             }

//                                             // PRIORITAS 3 : CHAOS ENGINE

//                                             if (!aiUsedItem)
//                                             {
//                                                 aiTryUseItem(
//                                                     dealer,
//                                                     player,
//                                                     bullets,
//                                                     musuhDoubleDamage,
//                                                     "CHAOS ENGINE",
//                                                     100,
//                                                     aiUsedItem
//                                                 );
//                                             }
//                                             aiUsedManipulationItem = true;
//                                         } 

//                                         bool supercharged = aiTryUseItem(
//                                             dealer,
//                                             player,
//                                             bullets,
//                                             musuhDoubleDamage,
//                                             "SUPERCHARGED PULSE",
//                                             100,
//                                             aiUsedItem
//                                         );

//                                         if (!supercharged)
//                                         {
//                                             aiTryUseItem(
//                                                 dealer,
//                                                 player,
//                                                 bullets,
//                                                 musuhDoubleDamage,
//                                                 "HYPERBARREL ACCELERATOR",
//                                                 100,
//                                                 aiUsedItem
//                                             );
//                                         }
//                                         aiUsedBuffItem =  true;
                                        
//                                         aiTryUseItem(
//                                             dealer,
//                                             player,
//                                             bullets,
//                                             musuhDoubleDamage,
//                                             "OVERDRIVE MODE",
//                                             100,
//                                             aiUsedItem
//                                         );

//                                         dealer.forceShootEnemy = true;
//                                         bulletScanned = true;
//                                     }
//                                 }

//                                 // semua BLANK

//                                 else if (blank == bullets.totalBullet())
//                                 {
//                                     dealer.scannerDefensive = true;

//                                     // SCANNER DEFENSIVE MODE

//                                     if (dealer.scannerDefensive)
//                                     {
//                                         dealer.scannerDefensive = false;

//                                         aiTryUseItem(
//                                             dealer,
//                                             player,
//                                             bullets,
//                                             musuhDoubleDamage,
//                                             "STABILIZER ENERGY",
//                                             100,
//                                             aiUsedItem
//                                         );

//                                         aiTryUseItem(
//                                             dealer,
//                                             player,
//                                             bullets,
//                                             musuhDoubleDamage,
//                                             "OVERDRIVE MODE",
//                                             100,
//                                             aiUsedItem
//                                         );

//                                         dealer.forceShootSelf = true;
//                                         bulletScanned = true;
//                                     }
//                                 }
//                             }
//                             aiUsedTrackItem = true;
//                         }

//                         // ========================================
//                         // AI : MATRIX REBOOT
//                         // ========================================

//                         if (!aiUsedItem)
//                         {
//                             bool selfControlled =
//                                 dealer.skipTurn ||
//                                 dealer.dominatrixSequence;

//                             bool enemyControlled =
//                                 player.skipTurn ||
//                                 player.reflectionField;

//                             // jika ada efek kontrol

//                             if (selfControlled || enemyControlled)
//                             {
//                                 aiTryUseItem(
//                                     dealer,
//                                     player,
//                                     bullets,
//                                     musuhDoubleDamage,
//                                     "MATRIX REBOOT",
//                                     85,
//                                     aiUsedItem
//                                 );
//                             }
//                             aiUsedCounterItem = true;
//                         }
                        
//                         // ========================================
//                         // AI : CORE NEUTRALIZER
//                         // ========================================

//                         if (!aiUsedCounterItem)
//                         {
//                             bool playerHasBuff =
//                                 player.supercharged ||
//                                 player.stabilizer ||
//                                 player.hyperbarrel;

//                             if (playerHasBuff)
//                             {
//                                 aiTryUseItem(
//                                     dealer,
//                                     player,
//                                     bullets,
//                                     musuhDoubleDamage,
//                                     "CORE NEUTRALIZER",
//                                     85,
//                                     aiUsedItem
//                                 );
//                             }
//                         }

//                         // KENA DAMAGE → KINETIC BARRIER 

//                         if (dealer.kenaDamage)
//                         {
//                             bool barrierUsed = aiTryUseItem(
//                                 dealer,
//                                 player,
//                                 bullets,
//                                 musuhDoubleDamage,
//                                 "KINETIC BARRIER",
//                                 75,
//                                 aiUsedItem
//                             );

//                             // SETELAH BARRIER, 30% CHANCE REFLECTION

//                             if (barrierUsed)
//                             {
//                                 if (aiWantsToUseItem(30))
//                                 {
//                                     aiTryUseItem(
//                                         dealer,
//                                         player,
//                                         bullets,
//                                         musuhDoubleDamage,
//                                         "REFLECTION FIELD",
//                                         100, // langsung aktif kalau sudah masuk sini
//                                         aiUsedItem
//                                     );
//                                 }
//                                 dealer.kenaDamage = false;
//                             }
//                             aiUsedDefenseItem = true;
//                         }

//                         // KENA DAMAGE → REFLECTION FIELD
                        
//                         if (dealer.kenaDamage && !aiUsedDefenseItem)
//                         {
//                             aiTryUseItem(
//                                 dealer,
//                                 player,
//                                 bullets,
//                                 musuhDoubleDamage,
//                                 "REFLECTION FIELD",
//                                 70,
//                                 aiUsedItem
//                             );

//                             dealer.kenaDamage = false;
//                         }

//                         // HP LOW → RECOVERY STIM

//                         if (dealer.hp <= 2)
//                         {
//                             aiTryUseItem(
//                                 dealer,
//                                 player,
//                                 bullets,
//                                 musuhDoubleDamage,
//                                 "RECOVERY STIM",
//                                 80,
//                                 aiUsedItem
//                             );
//                         }

//                         // HP CRITICAL → QUANTUM COIN

//                         if (dealer.hp == 1)
//                         {
//                             aiTryUseItem(
//                                 dealer,
//                                 player,
//                                 bullets,
//                                 musuhDoubleDamage,
//                                 "QUANTUM COIN",
//                                 50,
//                                 aiUsedItem
//                             );
//                         }

//                         // ========================================
//                         // AI : OVERDRIVE MODE
//                         // ========================================

//                         if (!aiUsedItem)
//                         {
//                             aiTryUseItem(
//                                 dealer,
//                                 player,
//                                 bullets,
//                                 musuhDoubleDamage,
//                                 "OVERDRIVE MODE",
//                                 65,
//                                 aiUsedItem
//                             );
//                         }

//                         // ========================================
//                         // RANDOM BUFF USAGE
//                         // ========================================

//                         if (!aiUsedItem && !aiUsedBuffItem && aiWantsToUseItem(75))
//                         {
//                             int randomBuff = rand() % 3;

//                             switch(randomBuff)
//                             {
//                                 case 0:

//                                     if (dealer.supercharged)
//                                         break;

//                                     aiTryUseItem(
//                                         dealer,
//                                         player,
//                                         bullets,
//                                         musuhDoubleDamage,
//                                         "SUPERCHARGED PULSE",
//                                         100,
//                                         aiUsedItem
//                                     );

//                                     dealer.forceShootEnemy = true;
//                                     aiUsedBuffItem = true;

//                                     break;

//                                 case 1:

//                                     if (dealer.stabilizer)
//                                         break;

//                                     aiTryUseItem(
//                                         dealer,
//                                         player,
//                                         bullets,
//                                         musuhDoubleDamage,
//                                         "STABILIZER ENERGY",
//                                         100,
//                                         aiUsedItem
//                                     );

//                                     dealer.forceShootSelf = true;
//                                     aiUsedBuffItem = true;

//                                     break;

//                                 case 2:

//                                     if (dealer.hyperbarrel)
//                                         break;

//                                     aiTryUseItem(
//                                         dealer,
//                                         player,
//                                         bullets,
//                                         musuhDoubleDamage,
//                                         "HYPERBARREL ACCELERATOR",
//                                         100,
//                                         aiUsedItem
//                                     );

//                                     dealer.forceShootEnemy = true;
//                                     aiUsedBuffItem = true;

//                                     break;
//                             }
//                         }

//                         // ========================================
//                         // RANDOM CHAMBER MANIPULATION
//                         // ========================================
                        
//                         if (!aiUsedItem && !aiUsedManipulationItem && !aiUsedBuffItem && aiWantsToUseItem(50))
//                         {
//                             int randomChamber = rand() % 3;

//                             switch(randomChamber)
//                             {
//                                 // POLARITY SHIFT

//                                 case 0:

//                                     aiTryUseItem(
//                                         dealer,
//                                         player,
//                                         bullets,
//                                         musuhDoubleDamage,
//                                         "POLARITY SHIFT",
//                                         100,
//                                         aiUsedItem
//                                     );

//                                     break;

//                                 // CHAMBER PURGER

//                                 case 1:
//                                 {
//                                     bool purgerUsed = aiTryUseItem(
//                                         dealer,
//                                         player,
//                                         bullets,
//                                         musuhDoubleDamage,
//                                         "CHAMBER PURGER",
//                                         100,
//                                         aiUsedItem
//                                     );

//                                     if (purgerUsed && !bullets.isEmpty())
//                                     {
//                                         chamberPurged = true;

//                                         int idx = rand() % bullets.totalBullet() + 1;

//                                         // ====================================
//                                         // NEXT BULLET ANALYSIS
//                                         // ====================================

//                                         // LIVE
//                                         if (bullets.bullet[bullets.top] == 1 && bullets.bullet[bullets.top] == idx)
//                                         {
//                                             dealer.forceShootEnemy = true;

//                                             // counter reflection
//                                             if (player.reflectionField)
//                                             {
//                                                 if (!aiUsedItem)
//                                                 {
//                                                     aiTryUseItem(
//                                                         dealer,
//                                                         player,
//                                                         bullets,
//                                                         musuhDoubleDamage,
//                                                         "POLARITY SHIFT",
//                                                         100,
//                                                         aiUsedItem
//                                                     );
//                                                 }

//                                                 if (!aiUsedItem)
//                                                 {
//                                                     aiTryUseItem(
//                                                         dealer,
//                                                         player,
//                                                         bullets,
//                                                         musuhDoubleDamage,
//                                                         "CHAOS ENGINE",
//                                                         100,
//                                                         aiUsedItem
//                                                     );
//                                                 }
//                                             }

//                                             // buff offensive
//                                             bool supercharged = aiTryUseItem(
//                                                 dealer,
//                                                 player,
//                                                 bullets,
//                                                 musuhDoubleDamage,
//                                                 "SUPERCHARGED PULSE",
//                                                 100,
//                                                 aiUsedItem
//                                             );

//                                             if (!supercharged)
//                                             {
//                                                 aiTryUseItem(
//                                                     dealer,
//                                                     player,
//                                                     bullets,
//                                                     musuhDoubleDamage,
//                                                     "HYPERBARREL ACCELERATOR",
//                                                     100,
//                                                     aiUsedItem
//                                                 );
//                                             }
//                                         }

//                                         // BLANK
//                                         else if (bullets.bullet[bullets.top] == 0 && bullets.bullet[bullets.top] == idx)
//                                         {
//                                             dealer.forceShootSelf = true;

//                                             aiTryUseItem(
//                                                 dealer,
//                                                 player,
//                                                 bullets,
//                                                 musuhDoubleDamage,
//                                                 "STABILIZER ENERGY",
//                                                 100,
//                                                 aiUsedItem
//                                             );
//                                         }
//                                     }
//                                     break;
//                                 }
//                                 // CHAOS ENGINE

//                                 case 2:

//                                     aiTryUseItem(
//                                         dealer,
//                                         player,
//                                         bullets,
//                                         musuhDoubleDamage,
//                                         "CHAOS ENGINE",
//                                         100,
//                                         aiUsedItem
//                                     );

//                                     break;
//                             }
//                         }

                        
//                         // ========================================
//                         // AI : SYNAPSE LOCK
//                         // ========================================

//                         if (!aiUsedItem)
//                         {
//                             // ====================================
//                             // PRIORITAS : KENA DOMINATRIX
//                             // lock diri sendiri
//                             // ====================================

//                             if (dealer.dominatrixSequence)
//                             {
//                                 if (aiWantsToUseItem(90))
//                                 {
//                                     string item;

//                                     ItemNode* node = findItemByName(
//                                         dealer.inventory,
//                                         "SYNAPSE LOCK",
//                                         item
//                                     );

//                                     if (node != NULL)
//                                     {
//                                         cout << "\n" << dealer.name << " MENGGUNAKAN SYNAPSE LOCK!\n";

//                                         useItemEffect(
//                                             item,
//                                             &dealer,
//                                             &player,
//                                             bullets,
//                                             musuhDoubleDamage,
//                                             true,
//                                             true
//                                         );

//                                         dealer.inventory.removeNode(node);

//                                         aiUsedItem = true;

//                                         Sleep(1200);
//                                     }
//                                 }
//                             }

//                             // ====================================
//                             // PLAYER PUNYA REFLECTION FIELD
//                             // ====================================

//                             if (player.reflectionField && lensUsed && bullets.bullet[bullets.top] == 1)
//                             {
//                                 if (aiWantsToUseItem(90))
//                                 {
//                                     string item;

//                                     ItemNode* node = findItemByName(
//                                         dealer.inventory,
//                                         "SYNAPSE LOCK",
//                                         item
//                                     );

//                                     if (node != NULL)
//                                     {
//                                         cout << "\n" << dealer.name << " MENGGUNAKAN SYNAPSE LOCK!\n";

//                                         useItemEffect(
//                                             item,
//                                             &dealer,
//                                             &player,
//                                             bullets,
//                                             musuhDoubleDamage,
//                                             true,
//                                             true
//                                         );

//                                         dealer.inventory.removeNode(node);

//                                         aiUsedItem = true;

//                                         Sleep(1200);
//                                     }
//                                 }
//                             }

//                             // ====================================
//                             // PLAYER PUNYA BUFF
//                             // ====================================

//                             else
//                             {
//                                 bool playerBuffed =
//                                     player.supercharged ||
//                                     player.stabilizer ||
//                                     player.hyperbarrel;

//                                 int lockChance =
//                                     playerBuffed ? 80 : 20;

//                                 if (aiWantsToUseItem(lockChance))
//                                 {
//                                     string item;

//                                     ItemNode* node = findItemByName(
//                                         dealer.inventory,
//                                         "SYNAPSE LOCK",
//                                         item
//                                     );

//                                     if (node != NULL)
//                                     {
//                                         cout << "\n" << dealer.name << " MENGGUNAKAN SYNAPSE LOCK!\n";

//                                         useItemEffect(
//                                             item,
//                                             &dealer,
//                                             &player,
//                                             bullets,
//                                             musuhDoubleDamage,
//                                             false,
//                                             true
//                                         );

//                                         dealer.inventory.removeNode(node);

//                                         aiUsedItem = true;

//                                         Sleep(1200);
//                                     }
//                                 }
//                             }
//                         }

//                         // ========================================
//                         // AI : DOMINATRIX SEQUENCE
//                         // ========================================

//                         if (!aiUsedItem)
//                         {
//                             int chance = 25;

//                             // player dangerous

//                             if (player.supercharged ||
//                                 player.hyperbarrel)
//                             {
//                                 chance = 70;
//                             }

//                             // reflection/stabilizer counter

//                             else if (player.stabilizer ||
//                                     player.reflectionField)
//                             {
//                                 chance = 60;
//                             }

//                             aiTryUseItem(
//                                 dealer,
//                                 player,
//                                 bullets,
//                                 musuhDoubleDamage,
//                                 "DOMINATRIX SEQUENCE",
//                                 chance,
//                                 aiUsedItem
//                             );
//                         }

//                         // ========================================
//                         // AI : PARADOX ROUND
//                         // ========================================

//                         if (!aiUsedItem && dealer.hp >= 3)
//                         {
//                             aiTryUseItem(
//                                 dealer,
//                                 player,
//                                 bullets,
//                                 musuhDoubleDamage,
//                                 "PARADOX ROUND",
//                                 50,
//                                 aiUsedItem
//                             );
//                             aiUsedChaosItem = true;
//                         }

//                         // ========================================
//                         // AI : ROGUE PROTOCOL
//                         // ========================================

//                         if (!aiUsedItem && !aiUsedChaosItem)
//                         {
//                             aiTryUseItem(
//                                 dealer,
//                                 player,
//                                 bullets,
//                                 musuhDoubleDamage,
//                                 "ROGUE PROTOCOL",
//                                 20,
//                                 aiUsedItem
//                             );
//                             aiUsedDefenseItem = true;
//                         }

//                         // ========================================
//                         // AI : HIJACK MODULE
//                         // ========================================

//                         if (!aiUsedItem && dealer.inventory.countItem() <= 2)
//                         {
//                             aiTryUseItem(
//                                 dealer,
//                                 player,
//                                 bullets,
//                                 musuhDoubleDamage,
//                                 "HIJACK MODULE",
//                                 60,
//                                 aiUsedItem
//                             );
//                         }
//                     }

//                     // =========================
//                     // SYNAPSE LOCK CHECK
//                     // =========================
//                     if (dealer.skipTurn)
//                     {
//                         dealer.skipTurn = false;

//                         if (dealer.dominatrixSequence)
//                         {
//                             if (dealer.dominatrixMode == 1)
//                             {
//                                 setColor(13);

//                                 cout << "\nDOMINATRIX: 'DIPAKSA MENEMBAK DIRI SENDIRI!'\n";

//                                 Sleep(1000);
//                                 setColor(7);

//                                 cout << "\n"
//                                     << dealer.name
//                                     << " TIDAK BISA MENEMBAK KARENA TRIGGER TERKUNCI!\n";
//                             }
//                             else if (dealer.dominatrixMode == 2)
//                             {
//                                 setColor(13);

//                                 cout << "\nDOMINATRIX: 'DIPAKSA MENEMBAK LAWAN!'\n";

//                                 Sleep(1000);
//                                 setColor(7);

//                                 cout << "\n"
//                                     << dealer.name
//                                     << " TIDAK BISA MENEMBAK KARENA TRIGGER TERKUNCI!\n";
//                             }
//                             dealer.dominatrixSequence = false;
//                             dealer.dominatrixMode = 0;
//                         }
//                         else
//                         {
//                             cout << "\n" << dealer.name
//                                 << " TIDAK BISA MENEMBAK KARENA TRIGGER TERKUNCI!\n";
//                         }

//                         if (dealer.extraTurn)
//                             {   
//                                 if (!dealer.alive || !player.alive)
//                                 {
//                                     break;
//                                 }
//                                 musuhSudahNembak = false;
//                                 dealer.extraTurn = false;

//                                 cout << "\nOVERDRIVE AKTIF!\n";
//                                 cout << dealer.name
//                                     << " MENDAPATKAN TURN TAMBAHAN!\n";
                                
//                                 int live = 0;
//                                 int blank = 0;

//                                 // musuh pake scanner

//                                 if (bulletScanned) {

//                                     countBullet(bullets, live, blank);
//                                     bulletScanned = false;

//                                     if (live == bullets.totalBullet())
//                                     {
//                                         dealer.forceShootEnemy = true;
//                                     }
//                                     else if (blank == bullets.totalBullet())
//                                     {
//                                         dealer.forceShootSelf = true;
//                                     }
//                                 }
//                                 Sleep(1200);

//                                 continue;
//                             }

//                         system("pause");
//                         break;
//                     }

//                     // cek peluru abis purge

//                     if (chamberPurged && bullets.totalBullet() == 0)
//                         {   
//                             chamberPurged = false;
//                             Sleep(1000);
//                             break;
//                         }

//                     // =========================
//                     // TARGET DECISION SYSTEM
//                     // =========================

//                     int targetAI = -1;

//                     // DOMINATRIX PRIORITY

//                     if (dealer.dominatrixSequence)
//                     {
//                         if (dealer.dominatrixMode == 1)
//                         {
//                             setColor(13);

//                             cout << "\nDOMINATRIX: 'DIPAKSA MENEMBAK DIRI SENDIRI!'\n";

//                             setColor(7);

//                             targetAI = 1;
//                         }
//                         else if (dealer.dominatrixMode == 2)
//                         {
//                             setColor(13);

//                             cout << "\nDOMINATRIX: 'DIPAKSA MENEMBAK LAWAN!'\n";

//                             setColor(7);

//                             targetAI = 0;
//                         }

//                         dealer.dominatrixSequence = false;
//                         dealer.dominatrixMode = 0;
//                     }

//                     // NEURAL LENS DECISION

//                     else if (dealer.forceShootEnemy)
//                     {
//                         targetAI = 0;
//                     }

//                     else if (dealer.forceShootSelf)
//                     {
//                         targetAI = 1;
//                     }

//                     // NORMAL RANDOM AI

//                     else
//                     {
//                         targetAI = rand() % 2;
//                     }

//                     // =========================
//                     // EXECUTE SHOOT
//                     // =========================

//                     if (player.alive && dealer.alive)
//                     {
//                         if (targetAI == 0)
//                         {
//                             cout << dealer.name
//                                 << " MEMBIDIK " << player.name << "...\n";

//                             Sleep(1000);

//                             shoot(&dealer, &player, bullets, musuhDoubleDamage);
//                         }
//                         else
//                         {
//                             cout << dealer.name
//                                 << " MEMBIDIK DIRINYA SENDIRI...\n";

//                             Sleep(1000);

//                             shoot(&dealer, &dealer, bullets, musuhDoubleDamage);
//                         }
//                         musuhSudahNembak = true;

//                         // ========================================
//                         // CEK STATUS BUFF SETELAH MENEMBAK
//                         // ========================================

//                         if (aiUsedBuffItem)
//                         {
//                             // buff agresif habis
//                             if (!dealer.supercharged && !dealer.hyperbarrel)
//                             {
//                                 dealer.forceShootEnemy = false;
//                             }

//                             // buff defensif habis
//                             if (!dealer.stabilizer)
//                             {
//                                 dealer.forceShootSelf = false;
//                             }

//                             aiUsedBuffItem = false;
//                         }

//                         if (musuhSudahNembak) {

//                             // musuh punya overdrive

//                             if (dealer.extraTurn)
//                             {   
//                                 if (!dealer.alive || !player.alive)
//                                 {
//                                     break;
//                                 }
//                                 musuhSudahNembak = false;   
//                                 dealer.extraTurn = false;

//                                 cout << "\nOVERDRIVE AKTIF!\n";
//                                 cout << dealer.name
//                                     << " MENDAPATKAN TURN TAMBAHAN!\n";
                                
//                                 int live = 0;
//                                 int blank = 0;

//                                 // musuh pake scanner

//                                 if (bulletScanned) {

//                                     countBullet(bullets, live, blank);
//                                     bulletScanned = false;

//                                     if (live == bullets.totalBullet())
//                                     {
//                                         dealer.forceShootEnemy = true;
//                                     }
//                                     else if (blank == bullets.totalBullet())
//                                     {
//                                         dealer.forceShootSelf = true;
//                                     }
//                                 }
//                                 Sleep(1200);

//                                 // ========================================
//                                 // RELOAD SAAT OVERDRIVE
//                                 // ========================================

//                                 if (bullets.isEmpty())
//                                 {
//                                     system("cls");

//                                     setColor(14);

//                                     cout << "\n====================================\n";
//                                     cout << "           CHAMBER KOSONG\n";
//                                     cout << "====================================\n\n";

//                                     setColor(7);

//                                     cout << "PELURU AKAN DIISI KEMBALI...\n";

//                                     Sleep(1500);

//                                     generateBullet(bullets);

//                                     // reward item ronde baru

//                                     string itemPlayer = getNewItem();
//                                     string itemEnemy = getNewItem();

//                                     player.chaosState = false;
//                                     dealer.chaosState = false;

//                                     player.inventory.addItem(itemPlayer);
//                                     dealer.inventory.addItem(itemEnemy);

//                                     cout << "\n" << player.name
//                                         << " mendapatkan item: "
//                                         << itemPlayer;

//                                     // label SPECIAL

//                                     for (int i = 0; i < 20; i++)
//                                     {
//                                         if (itemList[i].itemName == itemPlayer)
//                                         {
//                                             if (itemList[i].rare)
//                                             {
//                                                 setColor(13);
//                                                 cout << " [SPECIAL]";
//                                                 setColor(7);
//                                             }
//                                             break;
//                                         }
//                                     }

//                                     cout << endl;

//                                     system("pause");
//                                 }

//                                 continue;
//                             }
//                             system("pause");

//                             break;
//                         }
//                     }
//                 }
//             }
//         }

//         // menang lawan musuh

//         if (player.alive && !dealer.alive)
//         {
//             system("cls");

//             setColor(10);

//             cout << "\n=====================================\n";
//             cout << "           STAGE " << level+1 << " MENANG!\n";
//             cout << "=====================================\n\n";

//             cout << player.name
//              << " BERHASIL MENGALAHKAN "
//              << dealer.name
//              << "!\n\n";
            
//             player.chaosState = false;
//             dealer.chaosState = false;

//             setColor(7);


//             // ====================================
//             // SETELAH MENANG
//             // PILIH CABANG RANDOM
//             // ====================================

//             if (level < 3)
//             {
//                 int path = rand() % 2;

//                 // kiri
//                 if (path == 0)
//                 {
//                     currentEnemy = currentEnemy->left;
//                 }

//                 // kanan
//                 else
//                 {
//                     currentEnemy = currentEnemy->right;
//                 }
//             }
//             system("pause");
//         }
//     }

//     // result akhir

//     showGameOver(player);

//     return 0;
// }