#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>

using namespace std;

void setColor(int warna)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), warna);
}

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

struct ItemData
{
    string itemName;
    string description;
    bool rare;
};

ItemData itemList[20] =
{   
    // basic item
    {"RECOVERY STIM", "MEMULIHKAN 2 HP.", false},
    {"NEURAL LENS", "MELIHAT JENIS PELURU TERATAS DALAM CHAMBER.", false},
    {"SUPERCHARGED PULSE", "PELURU LIVE SELANJUTNYA AKAN MEMBERIKAN 2 DAMAGE.", false},
    {"STABILIZER ENERGY", "PELURU BLANK BERIKUTNYA AKAN MEMULIHKAN 1 HP.\nJIKA HP PENUH, MAKA AKAN MEMBERIKAN 1 AP.\nMEMILIKI 50% CHANCE UNTUK MEMBERIKAN EFEK [NANOSHIELD] (MENAHAN 1 DAMAGE).", false},
    {"HYPERBARREL ACCELERATOR", "PELURU LIVE BERIKUTNYA AKAN MEMILIKI 25% CHANCE UNTUK MEMBERIKAN CRITICAL DAMAGE (3 DAMAGE).\nJIKA BERHASIL MEMBERIKAN CRITICAL DAMAGE, ADA 50% CHANCE UNTUK MEMBERIKAN EFEK [OVERDRIVE DISRUPT] (MENGGANGGU OVERDRIVE LAWAN).", false},
    {"OVERDRIVE MODE", "MEMUNGKINKAN USER UNTUK MENDAPATKAN 1x EXTRA TURN.\nSAAT TERKENA EFEK [OVERDRIVE DISRUPT], OVERDRIVE AKAN LANGSUNG DIBATALKAN.", false},
    {"CHAMBER PURGER", "MEMBUANG PELURU TERATAS DAN MELIHAT JENIS PELURU YANG TERSISA DI DALAM CHAMBER SECARA ACAK.", false},
    {"POLARITY SHIFT", "MENGUBAH PELURU LIVE MENJADI BLANK ATAUPUN SEBALIKNYA.", false},
    {"SYNAPSE LOCK", "MEMUNGKINKAN USER UNTUK MENGUNCI TRIGGER DIRINYA SENDIRI ATAU LAWAN.\nSAAT TRIGGER DIKUNCI, PENEMBAK TIDAK AKAN BISA MENEMBAK UNTUK 1x TURN.", false},
    {"KINETIC BARRIER", "MEMBERIKAN 1 AP YANG BERFUNGSI UNTUK MENAHAN DAMAGE SEBELUM HP DIGUNAKAN.", false},
    {"PROBABILITY SCANNER", "MELIHAT JUMLAH SISA PELURU LIVE/BLANK DALAM CHAMBER.", false},
    {"DOMINATRIX SEQUENCE", "MEMUNGKINKAN USER UNTUK MEMAKSA LAWAN MENEMBAK DIRINYA SENDIRI ATAU LAWANNYA UNTUK 1x TURN.", false},
    {"REFLECTION FIELD", "MEMANTULKAN 1-2 DAMAGE YANG DIBERIKAN PENEMBAK KE PENEMBAK ITU SENDIRI.\nSAAT TERKENA 1 DAMAGE, ADA 30% CHANCE DIMANA FIELD BISA BERTAHAN UNTUK MENAHAN 1 DAMAGE LAGI.\nFIELD TIDAK BISA MENAHAN DAMAGE YANG LEBIH DARI 2 DAN AKAN LANGSUNG HANCUR.", false},
    {"CORE NEUTRALIZER", "MENGHAPUS 1 BUFF RANDOM DARI LAWAN ANTARA [SUPERCHARGED]/[STABILIZED]/[HYPERACCELERATION]).", false},
    {"MATRIX REBOOT", "MEMUNGKINKAN USER UNTUK MENARGETKAN DIRINYA SENDIRI ATAU LAWAN.\nJIKA MENARGETKAN DIRI SENDIRI, MAKA AKAN MENGHAPUS 1 EFEK RANDOM ANTARA [LOCKED]/[DOMINATED].\nJIKA MENARGETKAN LAWAN, MAKA AKAN MENGHAPUS 1 EFEK RANDOM ANTARA [LOCKED]/[REFLECTION].", false},

    // special item
    {"QUANTUM COIN", "SETELAH MELEMPAR KOIN, ADA 50% UNTUK BERHASIL MENDAPATKAN FULL HEAL.\nSAAT MENDAPATKAN FULL HEAL, ADA 40% CHANCE UNTUK MENDAPATKAN 1 AP ATAU 10% CHANCE UNTUK MENDAPATKAN 2 AP.\nJIKA GAGAL MENDAPATKAN FULL HEAL, MAKA USER AKAN LANGSUNG MATI.", true},
    {"CHAOS ENGINE", "MEMBUAT SITUASI KEKACAUAN DENGAN MENANDAKAN BAIK DIRI SENDIRI MAUPUN LAWAN DENGAN EFEK [CHAOS].\nDALAM MASA INI, SELURUH URUTAN PELURU AKAN DIACAK.\nJIKA JENIS PELURU DALAM CHAMBER SAMA SEMUA, MAKA JENIS PELURU AKAN DIACAK JUGA.\nSELAGI PELURU DALAM CHAMBER BELUM HABIS, PELURU TERSEBUT AKAN ADA DALAM KEADAAN TIDAK STABIL.\nPELURU LIVE MEMILIKI 50% CHANCE UNTUK MEMANTULKAN DAMAGE KEMBALI DARI PENEMBAK KE PENEMBAK ITU SENDIRI.\nPELURU BLANK MEMILIKI 50% CHANCE UNTUK MEMULIHKAN 1 HP KEPADA TARGET DARI PENEMBAK (MEMBERIKAN 1 AP JIKA HP PENUH).", true},
    {"ROGUE PROTOCOL", "MEMBUAT PELURU TERATAS MENJADI LIVE DAN USER AKAN MENERIMA EFEK [ROGUE].\nDALAM MASA INI, CHAMBER AKAN MENJADI TIDAK STABIL YANG MEMBUAT ARAH TEMBAKAN BISA BERUBAH DAN MEMBERIKAN 4 DAMAGE KEPADA TARGET YANG KENA TEMBAK.", true},
    {"HIJACK MODULE", "MEMUNGKINKAN USER UNTUK MENCURI 1 ITEM RANDOM DARI LAWAN.\nNAMUN, ADA 50% CHANCE USER AKAN GAGAL MENCURI ITEM DAN 1 ITEM MILIKNYA SENDIRI AKAN HILANG SECARA RANDOM.", true},
    {"PARADOX ROUND", "MEMBUAT PELURU TERATAS MENJADI LIVE DAN USER AKAN MENERIMA EFEK [PARADOX].\nDALAM MASA INI, PELURU TERATAS DALAM CHAMBER AKAN SELALU BERUBAH-UBAH.\nJIKA PELURU BERUBAH MENJADI DESTRUCTIVE ROUND, MAKA AKAN MEMBERIKAN 2 DAMAGE (BISA MENEMBUS REFLECTION FIELD) DAN ADA 50% CHANCE UNTUK MENGHANCURKAN 1 AP.\nJIKA PELURU BERUBAH MENJADI SAFE ROUND, MAKA AKAN MEMULIHKAN 2 HP (MEMBERIKAN 1 AP JIKA HP PENUH) DAN ADA 50% CHANCE UNTUK MEMBERIKAN 1 AP TAMBAHAN.", true}
};

// ========================================
// acak item
// ========================================

string generateRandomItem(bool &rareSpawned)
{
    // cek rare spawn

    int chance = rand() % 100;

    bool spawnRare = false;

    // 30% chance rare
    // maksimal 1 rare

    if (chance < 30 && !rareSpawned)
    {
        spawnRare = true;
        rareSpawned = true;
    }
};

    // ========================================
    // simpan item yang cocok
    // ========================================

    string availableItem[20];

    int totalAvailable = 0;

    for (int i = 0; i < 20; i++)
    {
        // rare item

        if (spawnRare && itemList[i].rare)
        {
            availableItem[totalAvailable] =
                itemList[i].itemName;

            totalAvailable++;
        }

        // basic item

        else if (!spawnRare && !itemList[i].rare)
        {
            availableItem[totalAvailable] =
                itemList[i].itemName;

            totalAvailable++;
        }
    }

    // ========================================
    // random item
    // ========================================

    int randomIndex =
        rand() % totalAvailable;

    return availableItem[randomIndex];
}

// ========================================
// ronde baru item baru
// ========================================

string getNewItem()
{
    bool wantRare = (rand() % 100) < 30; 

    string candidates[20];
    int count = 0;

    for (int i = 0; i < 20; i++)
    {
        if (itemList[i].rare == wantRare)
        {
            candidates[count++] = itemList[i].itemName;
        }
    }

    int index = rand() % count;
    return candidates[index];
}

// ========================================
// setak peluru
// ========================================

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
// sistem nemak nemak
// ========================================

bool shoot(Player *shooter, Player *target, BulletStack &stack, bool &doubleDamage)
{
    if (stack.isEmpty())
    {
        cout << "\nPELURU HABIS!\n";
        return false;
        
    }

    int bullet = stack.pop();

    cout << "\n";
    cout << shooter->name << " MENARIK PELATUK...\n";

    Sleep(1000);

    if (bullet == 1)
    {   
        int damage = 1;
        bool rogueRandomTarget = false;
        bool paradoxDestruct = false;
        bool paradoxHeal = false;

        // cek paradox round

        if (shooter->paradoxRound)
        {
            shooter->paradoxRound = false;

            shooter->supercharged = false;
            shooter->supercharged = false;
            shooter->hyperbarrel = false; 

            setColor(13);

            cout << "\nPARADOX BERPROSES...\n";

            setColor(7);

            Sleep(1500);

            int paradoxResult = rand() % 2;

            // DAMAGE

            if (paradoxResult == 0)
            {
                damage = 2;
                paradoxDestruct = true;

                setColor(4);
                cout << "\nPARADOX MENJADI DESTRUCTIVE ROUND!\n";
                setColor(7);
            }

            // HEAL

            else
            {
                paradoxHeal = true;

                setColor(10); 
                cout << "\nPARADOX BERUBAH MENJADI SAFE ROUND!\n";
                setColor(7);
            }

            Sleep(1000);
        }

        // CEK ROGUE PROTOCOL

        if (shooter->rogueProtocol)
        {
            shooter->rogueProtocol = false;
            
            shooter->supercharged = false;
            shooter->supercharged = false;
            shooter->hyperbarrel = false; 

            damage = 4;

            setColor(12);

            cout << "\nROGUE PROTOCOL AKTIF!\n";
            cout << "TEMBAKAN MULAI BERGERAK TAK TERKENDALI!\n";
            cout << "ARAH TEMBAKAN MENUJU KE...\n";


            Sleep(1500);

            int randomTarget = rand() % 2;

            // target berubah ke diri sendiri

            if (randomTarget == 0)
            {
                target = shooter;

                cout << "\nDIRI SENDIRI!\n";
            }

            // target tetap lawan

            else
            {   
                cout << "\nLAWAN!\n";
            }

            Sleep(1500);
            setColor(7);
        }
        
        // PARADOX HEAL

        if (paradoxHeal)
        {
            int healAmount = 2;

            setColor(10);

            // HP belum penuh

            if (target->hp < MAX_HP)
            {
                target->hp += healAmount;

                // batasi max HP

                if (target->hp > MAX_HP)
                {
                    target->hp = MAX_HP;
                    setColor(11);
                    cout << "HP MAKSIMUM TERCAPAI!\n";

                    int healChance = rand() % 100;
                    if (healChance < 50)
                    {
                        target->ap++;

                        cout << "SISA PARADOX AKAN DIKONVERSI MENJADI AP!\n\n";

                        cout << target->name
                            << " MENDAPATKAN 1 AP!\n";

                        cout << "TOTAL AP : "
                            << target->ap
                            << endl;
                    }
                }
                else
                {
                    cout << "HP "
                        << target->name
                        << " BERTAMBAH!\n";

                    cout << "HP SEKARANG : "
                        << target->hp
                        << endl;
                }
            }

            // HP penuh → convert jadi AP

            else if (target->hp == MAX_HP)
            {
                setColor(11);
                cout << "SISA PARADOX AKAN DIKONVERSI MENJADI AP!\n\n";

                int healChance = rand() % 100;
                    if (healChance < 50)
                    {
                        target->ap += 2;

                        cout << target->name
                            << " MENDAPATKAN 2 AP!\n";

                        cout << "TOTAL AP : "
                            << target->ap
                            << endl;
                    }
                    else
                    {   
                        target->ap++;

                        cout << target->name
                            << " MENDAPATKAN 1 AP!\n";

                        cout << "TOTAL AP : "
                            << target->ap
                            << endl;
                    }
            }

            setColor(7);

            return false;
        }

        setColor(12);

        cout << "\nBANG!!!\n";

        setColor(7);

        if (shooter->supercharged)
        {   
            damage = 2;

            setColor(4);
            cout << "DOUBLE DAMAGE AKTIF!\n";
            setColor(7);

            shooter->supercharged = false;
        }

        // HYPERBARREL CHECK
        if (shooter->hyperbarrel)
        {
            shooter->hyperbarrel = false; 

            int crit = rand() % 100;

            if (crit < 25)
            {
                damage = 3;

                setColor(14);
                cout << "CRITICAL HIT AKTIF! DAMAGE x3!\n";
                setColor(7);

                // ========================================
                // HIDDEN OVERDRIVE DISRUPT
                // ========================================

                if ((rand() % 100) < 50)
                {   
                    if (target != shooter) {
                        setColor(14);
                        cout << "LAWAN BERHASIL TERKENA OVERDRIVE DISRUPT!\n\n";
                        setColor(7);
                    }
                    target->overdriveDisrupt = true;
                }
                    }
                }
        // jika masih ada damage tersisa

        if (damage > 0)
        {   
            if (shooter->chaosState && shooter != target)
            {
                int chaos = rand() % 100;

                if (chaos < 50)
                {
                    setColor(4);

                    cout << "\nCHAOS ENERGY AKTIF!\n";
                    cout << "PELURU BERBALIK ARAH KE PENEMBAK!\n";

                    setColor(7);

                    target = shooter;
                }
            }
                        
            // REFLECTION FIELD CHECK
            if (target->reflectionField)
            {
                // DAMAGE > 2 AKAN LANGSUNG HANCUR

                if (damage > 2)
                {
                    target->reflectionField = false;
                    target->reflectionSustain = false;

                    setColor(4);

                    cout << "\nREFLECTION FIELD HANCUR!\n";
                    cout << "DAMAGE TERLALU BESAR!\n\n";

                    setColor(7);
                }

                // PARADOX TEMBUS FIELD

                else if (paradoxDestruct)
                {
                    setColor(4);

                    cout << "\nPARADOX MENGACAUKAN REFLECTION FIELD!!\n";
                    cout << "PELURU BISA MENEMBUS PERTAHANAN!\n\n";

                    setColor(7);
                }

                // NORMAL REFLECTION

                else
                {
                    // self shot tidak dipantulkan

                    if (target == shooter)
                    {
                        cout << "\nREFLECTION FIELD TIDAK MEMANTULKAN PELURU!\n";
                        cout << "DAMAGE DARI DIRI SENDIRI TETAP DITERIMA!\n\n";
                    }

                    else
                    {   
                        if (target->nanoShield)
                        {
                            target->nanoShield = false;

                            setColor(11);

                            cout << "\nNANOSHIELD MENAHAN 1 DAMAGE!\n";

                            setColor(7);

                            // kurangi damage sebesar 1
                            damage -= 1;

                            // damage habis total
                            if (damage <= 0)
                            {
                                cout << target->name
                                    << " TIDAK MENERIMA DAMAGE!\n";

                                return true;
                            }

                            cout << "SISA DAMAGE : "
                                << damage << endl;
                        }
                        else
                        {
                        cout << "\nREFLECTION FIELD MEMANTULKAN PELURU!\n";

                        shooter->hp -= damage;

                        shooter->kenaDamage = true;

                        cout << shooter->name
                            << " TERKENA "
                            << damage
                            << " DAMAGE BALIK!\n";
                        }

                        // SUSTAIN SYSTEM

                        // belum pernah sustain
                        if (!target->reflectionSustain)
                        {
                            int sustain = rand() % 100;

                            // 30% survive
                            if (sustain < 30)
                            {
                                target->reflectionSustain = true;

                                setColor(11);
                                cout << "\nREFLECTION FIELD BERTAHAN!\n";
                                cout << "FIELD MASIH BISA MENAHAN 1 DAMAGE LAGI!\n";
                                setColor(7);
                            }

                            // gagal sustain
                            else
                            {
                                target->reflectionField = false;

                                setColor(4);
                                cout << "\nREFLECTION FIELD HANCUR!\n";
                                setColor(7);
                            }
                        }

                        // sustain sudah pernah dipakai
                        else
                        {
                            // DAMAGE BESAR MENEMBUS FIELD
                            if (damage >= 2)
                            {
                                target->reflectionField = false;
                                target->reflectionSustain = false;

                                setColor(4);

                                cout << "\nREFLECTION FIELD HANCUR!\n";
                                cout << "DAMAGE TERLALU BESAR!\n";

                                setColor(7);

                                // target tetap kena 1 damage
                                if (target->nanoShield)
                                {
                                    target->nanoShield = false;

                                    setColor(11);

                                    cout << "\nNANOSHIELD MENAHAN 1 DAMAGE!\n";

                                    setColor(7);

                                    // kurangi damage sebesar 1
                                    damage -= 1;

                                    // damage habis total
                                    if (damage <= 0)
                                    {
                                        cout << target->name
                                            << " TIDAK MENERIMA DAMAGE!\n";

                                        return true;
                                    }

                                    cout << "SISA DAMAGE : "
                                        << damage << endl;
                                }
                                else
                                {
                                    target->hp -= 1;

                                    target->kenaDamage = true;

                                    cout << target->name
                                        << " TERKENA 1 DAMAGE!\n";

                                    // cek mati
                                    if (target->hp <= 0)
                                    {
                                        target->alive = false;

                                        cout << target->name
                                            << " MATI!\n";
                                    }
                                }
                            }

                            // DAMAGE NORMAL
                            else
                            {
                                target->reflectionField = false;
                                target->reflectionSustain = false;

                                setColor(4);

                                cout << "\nREFLECTION FIELD HANCUR!\n";

                                setColor(7);
                            }
                        }

                        // mati

                        if (shooter->hp <= 0)
                        {
                            shooter->alive = false;

                            cout << shooter->name
                                << " MATI!\n";
                        }

                        return true;
                    }
                }
            }

            while (target->ap > 0 && damage > 0)
            {   
                if (paradoxDestruct)
                {
                    int destructChance = rand() % 100;
                    if (destructChance < 50)
                    {
                        target->ap--;

                        setColor(4);
                        cout << "\nPARADOX MENGHANCURKAN SEBAGIAN BARRIER!\n";
                        setColor(11);
                        cout << "SISA AP : "
                            << target->ap
                            << endl;
                        setColor(7);

                        paradoxDestruct = false;
                    }
                }
                else if (target->nanoShield)
                {
                    target->nanoShield = false;

                    setColor(11);

                    cout << "\nNANOSHIELD MENAHAN 1 DAMAGE!\n";

                    setColor(7);

                    // kurangi damage sebesar 1
                    damage -= 1;

                    // damage habis total
                    if (damage <= 0)
                    {
                        cout << target->name
                            << " TIDAK MENERIMA DAMAGE!\n";

                        return true;
                    }

                    cout << "SISA DAMAGE : "
                        << damage << endl;
                }
                else
                {
                    target->ap--;

                    damage--;

                    setColor(11);

                    cout << target->name
                        << " MENAHAN DAMAGE DENGAN AP!\n";

                    cout << "SISA AP : "
                        << target->ap
                        << endl;

                    setColor(7);
                }
            }

            if (target->nanoShield)
            {
                target->nanoShield = false;

                setColor(11);

                cout << "\nNANOSHIELD MENAHAN 1 DAMAGE!\n";

                setColor(7);

                // kurangi damage sebesar 1
                damage -= 1;

                // damage habis total
                if (damage <= 0)
                {
                    cout << target->name
                        << " TIDAK MENERIMA DAMAGE!\n";

                    return true;
                }

                cout << "SISA DAMAGE : "
                    << damage << endl;
            }

            target->hp -= damage;

            cout << target->name
                << " TERKENA "
                << damage
                << " DAMAGE!\n";

            target->kenaDamage = true;
        }

        if (target->hp <= 0)
        {
            target->alive = false;

            cout << target->name << " MATI!\n";
        }
        else
        {
            cout << "SISA HP : " << target->hp << endl;
        }
        return true;
    }
    else
    {
        setColor(8);

        cout << "\nklik...\n";
        cout << "BLANK SHELL\n";

        // ========================================
        // CHAOS BLANK EFFECT
        // ========================================

        if (shooter->chaosState)
        {
            int chaosHeal = rand() % 100;

            // 50% trigger
            if (chaosHeal < 50)
            {
                setColor(10);

                cout << "\nCHAOS ENERGY AKTIF!\n";

                // HP belum penuh
                if (target->hp < MAX_HP)
                {
                    cout << "PELURU MEMULIHKAN HP TARGET!\n\n";

                    target->hp++;

                    cout << target->name
                        << " MEMULIHKAN 1 HP!\n";
                }

                // HP penuh → jadi AP
                else
                {
                    cout << "HP MAKSIMUM TERCAPAI!\n";
                    cout << "ENERGI DIKONVERSI MENJADI AP!\n\n";

                    target->ap++;

                    cout << target->name
                        << " MENDAPATKAN 1 AP!\n";
                }

                setColor(7);

                return true;
            }
        }

        if (shooter->stabilizer)
        {
            // jika HP belum penuh

            if (target == shooter)
            {
                shooter->stabilizer = false;

                setColor(10);

                cout << "\nSTABILIZER BERHASIL!\n";

                if (shooter->hp < MAX_HP)
                {
                    shooter->hp++;

                    cout << shooter->name
                        << " MEMULIHKAN 1 HP!\n";

                    cout << "HP "
                        << shooter->name
                        << " SEKARANG : "
                        << shooter->hp
                        << endl;
                }

                // jika HP penuh

                else
                {
                    shooter->ap++;

                    setColor(11);
                    cout << "\nHP MAKSIMUM TERCAPAI!\n";
                    cout << "HP AKAN DIKONVERSIKAN MENJADI AP!\n\n";

                    cout << shooter->name
                        << " MENDAPATKAN 1 AP!\n";

                    cout << "TOTAL AP "
                        << shooter->name
                        << " : "
                        << shooter->ap
                        << endl;
                }

                int nanoChance = rand() % 100;

                if (nanoChance < 50)
                {
                    shooter->nanoShield = true;

                    setColor(11);

                    cout << "\nSTABILIZER MEMBENTUK NANOSHIELD!\n";
                    cout << "1 DAMAGE BERIKUTNYA AKAN DITAHAN!\n";

                    setColor(7);
                }
            }
        }
        setColor(7);
        return false;
    }
}

// ========================================
// UI item
// ========================================

string getItemDescription(string itemName)
{
    for (int i = 0; i < 20; i++)
    {
        if (itemList[i].itemName == itemName)
        {
            return itemList[i].description;
        }
    }

    return "Tidak ada deskripsi.";
}

bool isRareItem(string itemName)
{
    for (int i = 0; i < 20; i++)
    {
        if (itemList[i].itemName == itemName)
        {
            return itemList[i].rare;
        }
    }

    return false;
}

void tampilkanUIItem(
    int pilihan,
    Player* current,
    Player* enemy,
    BulletStack& bullet
)
{
    system("cls");

    // ITEM LIST

    cout << "\n=====================================================\n";
    cout << "                     ITEM LIST\n";
    cout << "=====================================================\n\n";

    ItemNode* temp = current->inventory.head;

    int index = 0;

    string selectedItem = "";

    while (temp != NULL)
    {
        // ITEM YANG DIPILIH
        if (index == pilihan)
        {
            setColor(12);

            cout << ">> ";

            selectedItem = temp->itemName;
        }
        else
        {
            setColor(7);

            cout << "   ";
        }

        // NOMOR ITEM
        cout << "[" << (index + 1) << "] "
             << temp->itemName;

        setColor(7);

        cout << endl;

        temp = temp->next;
        index++;
    }

    // =========================================
    // ITEM DESCRIPTION
    // =========================================

    if (isRareItem(selectedItem))
    {
        setColor(13);
        cout << "\n[SPECIAL ITEM]\n";
    }
    else
    {
        setColor(8);
        cout << "\n[BASIC ITEM]\n";
    }

    setColor(7);

    cout << getItemDescription(selectedItem) << endl;

    // CONTROL

    setColor(8);

    cout << "\nA = ATAS | D = BAWAH";
    cout << "\nENTER = ACTION";
    cout << "\nESC = KEMBALI";

    setColor(7);
}

// ========================================
// game over
// ========================================

void showGameOver(Player &player)
{
    system("cls");

    if (player.alive)
    {
        setColor(10);

        cout << "\n====================================\n";
        cout << "             GAME OVER\n";
        cout << "====================================\n\n";

        cout << player.name
             << " BERHASIL KELUAR DARI SIMULASI!\n";
    }
    else
    {
        setColor(4);

        cout << "\n====================================\n";
        cout << "             GAME OVER\n";
        cout << "====================================\n\n";

        cout << player.name
             << " TERPERANGKAP DALAM SIMULASI SELAMANYA...\n";
    }

    setColor(7);

    cout << endl;

    system("pause");
}

// ========================================
// pake item
// ========================================

bool useItemEffect(string itemName, Player *user, Player *target, BulletStack &bullets, bool &doubleDamage, bool targetSelf, bool isDealer)
{
    // RECOVERY STIM

    if (itemName == "RECOVERY STIM")
    {   
        // HP sudah penuh

        if (user->hp >= MAX_HP)
        {   
            cout << "\nHP SUDAH PENUH!\n";

            return false;
        }

        // heal

        user->hp += 2;

        // jika melebihi batas

        if (user->hp > MAX_HP)
        {
            user->hp = MAX_HP;

            setColor(11);

            cout << "\nHP MAKSIMUM TERCAPAI!\n\n";
        }

        setColor(10);

        cout << "\nHP BERTAMBAH!\n";

        cout << "HP SEKARANG : "
            << user->hp
            << endl;

        setColor(7);
    }

    // NEURAL LENS

    else if (itemName == "NEURAL LENS")
    {   
        if (!isDealer)
        {
            bullets.peekBullet();
        }
    }

    // SUPERCHARGED PULSE

    else if (itemName == "SUPERCHARGED PULSE")
    {   
        if (user->stabilizer || user->hyperbarrel || user->rogueProtocol || user->paradoxRound)
        {
            cout << "\nCHAMBER MODIFIER SUDAH AKTIF!\n";
            cout << "TIDAK BISA MENGGUNAKAN SUPERCHARGED PULSE!\n";
            return false;
        }

        if (user->supercharged)
        {
            cout << "\nSUPERCHARGED PULSE SUDAH AKTIF!\n";

            return false;
        }
        user->supercharged = true;

        cout << "\nSUPERCHARGED PULSE AKTIF!\n";
        cout << "LIVE BULLET SELANJUTNYA AKAN MEMBERIKAN DOUBLE DAMAGE!\n";
    }

    // CHAMBER PURGER

    else if (itemName == "CHAMBER PURGER")
    {
        if (!isDealer)
        {
            if (user->rogueProtocol || user->paradoxRound)
            {
                cout << "\nCHAMBER PURGER TIDAK DAPAT DIGUNAKAN!\n";

                if (user->rogueProtocol)
                    cout << "ROGUE PROTOCOL SEDANG AKTIF!\n";

                if (user->paradoxRound)
                    cout << "PARADOX ROUND SEDANG AKTIF!\n";

                return false;
            }

            if (bullets.isEmpty())
            {
                cout << "\nCHAMBER KOSONG!\n";
                return false;
            }

            bullets.pop();

            cout << "\nPELURU TERATAS DIBUANG!\n";
            Sleep(1000);

            int idx = rand() % bullets.totalBullet() + 1; // 1 - N (bottom-based)

            int bulletType;
            if (!bullets.getBulletByIndex(idx, bulletType))
            {
                cout << "\nGAGAL MENGAKSES CHAMBER!\n";
                return false;
            }

            cout << "MELIHAT PELURU SECARA ACAK DARI BAWAH...\n";
            Sleep(1000);
            
            cout << "\nPELURU KE-" << idx << " ADALAH ";

            if (bulletType == 1)
            {   
                setColor(12);
                cout << "LIVE BULLET!\n";
            }
            else
            {   
                setColor(8);
                cout << "BLANK BULLET!\n";
            }
            setColor(7);
            return true;
        }
        else
        {
            if (user->rogueProtocol || user->paradoxRound)
            {
                cout << "\nCHAMBER PURGER TIDAK DAPAT DIGUNAKAN!\n";

                if (user->rogueProtocol)
                    cout << "ROGUE PROTOCOL SEDANG AKTIF!\n";

                if (user->paradoxRound)
                    cout << "PARADOX ROUND SEDANG AKTIF!\n";

                return false;
            }

            if (bullets.isEmpty())
            {
                cout << "\nCHAMBER KOSONG!\n";
                return false;
            }

            bullets.pop();

            cout << "\nPELURU TERATAS DIBUANG!\n";
            Sleep(800);

            return true;
        }
    }

    // PROBABILITY SCANNER

    else if (itemName == "PROBABILITY SCANNER")
    {   
        if (!isDealer)
        {
        bullets.scanRemainingBullet();
        }
    }

    // POLARITY SHIFT

    else if (itemName == "POLARITY SHIFT")
    {   
        if (user->rogueProtocol || user->paradoxRound)
        {
            cout << "\nPOLARITY SHIFT TIDAK DAPAT DIGUNAKAN!\n";

            if (user->rogueProtocol)
                cout << "ROGUE PROTOCOL SEDANG AKTIF!\n";

            if (user->paradoxRound)
                cout << "PARADOX ROUND SEDANG AKTIF!\n";

            return false;
        }

        bullets.swapBulletType();

        cout << "\nPOLARITY SHIFT AKTIF!\n";
        cout << "PELURU TERATAS DIUBAH!\n";
    }

    // STABILIZER ENERGY

    else if (itemName == "STABILIZER ENERGY")
    {   
        if (user->supercharged || user->hyperbarrel || user->rogueProtocol || user->paradoxRound)
        {
            cout << "\nCHAMBER MODIFIER SUDAH AKTIF!\n";
            cout << "TIDAK BISA MENGGUNAKAN STABILIZER ENERGY!\n";

            return false;
        }

        if (user->stabilizer)
        {
            cout << "\nSTABILIZER ENERGY SUDAH AKTIF!\n";

            return false;
        }
        user->stabilizer = true;

        cout << "\nSTABILIZER AKTIF!\n";
        cout << "\nBLANK BULLET SELANJUTNYA AKAN MEMULIHKAN 1 HP!\n";
    }

    // OVERDRIVE MODE

    else if (itemName == "OVERDRIVE MODE")
    {   
        // OVERDRIVE DISRUPT CHECK

        if (user->overdriveDisrupt)
        {
            user->overdriveDisrupt = false;

            setColor(12);

            cout << "\nOVERDRIVE MODE GAGAL DIAKTIFKAN!\n";
            cout << "SISTEM BOOST MENGALAMI GANGGUAN!\n";

            setColor(7);

            return true;
        }

        if (user->extraTurn)
        {
            cout << "\nOVERDRIVE MODE SUDAH AKTIF!\n";

            return false;
        }
        user->extraTurn = true;

        cout << "\nOVERDRIVE MODE AKTIF!\n";
        cout << user->name
            << " MENDAPATKAN EXTRA TURN!\n";
    }

    // KINETIC BARRIER

    else if (itemName == "KINETIC BARRIER")
    {
        user->ap++;

        cout << "\nKINETIC BARRIER AKTIF!\n";
        cout << "MENDAPATKAN 1 AP!\n";

        cout << "TOTAL AP : "
            << user->ap
            << "\n"
            << endl; 
    }

    // SYNAPSE LOCK

    else if (itemName == "SYNAPSE LOCK")
    {   
        if (!isDealer)
        {
            cout << "\nTARGET :\n";
            cout << "[1] DIRI SENDIRI\n";
            cout << "[2] LAWAN\n";
            cout << "PILIH TARGET : ";

            int pilihTarget;
            if (!(cin >> pilihTarget))
            {
                cin.clear();
                cin.ignore(1000, '\n');

                cout << "\nTARGET TIDAK VALID!\n";
                cout << "SYNAPSE LOCK DIBATALKAN...\n";

                return false;
            }

            cin.ignore(1000, '\n');

            if (pilihTarget == 1)
                {
                    targetSelf = true;
                }
            else if (pilihTarget == 2)
                {
                    targetSelf = false;
                }
            else
                {
                    cout << "\nTARGET TIDAK VALID!\n";
                    cout << "SYNAPSE LOCK DIBATALKAN...\n";

                    return false;
                }
            
        }       
             
        if (targetSelf)
        {   
            if (user->skipTurn)
            {
                cout << "\nTRIGGER SUDAH TERKUNCI UNTUK DIRI SENDIRI!\n";

                return false;
            }

            user->skipTurn = true;

            cout << "\nMENGUNCI TRIGGER...\n";
            Sleep(1000);

            cout << "\n"
                << user->name
                << " TRIGGER TERKUNCI UNTUK DIRI SENDIRI!\n";
        }
        else
        {   
            if (target->dominatrixSequence)
            {
                cout << "\nTARGET SEDANG DALAM EFEK KONTROL!\n";
                cout << "TIDAK BISA MENGGUNAKAN SYNAPSE LOCK!\n";

                return false;
            }

            if (target->skipTurn)
            {
                cout << "\nTRIGGER SUDAH TERKUNCI UNTUK "
                << target->name
                << "!\n";

                return false;
            }

            target->skipTurn = true;

            cout << "\nMENGUNCI TRIGGER...\n";
            Sleep(1000);

            cout << "\nTRIGGER TERKUNCI UNTUK "
                << target->name
                << "!\n";
        }
    }

    // DOMINATRIX SEQUENCE

    else if (itemName == "DOMINATRIX SEQUENCE")
    {   
        if (!isDealer) 
        {
            if (target->skipTurn)
            {
                cout << "\nTARGET SEDANG DALAM EFEK KONTROL!\n";
                cout << "TIDAK BISA MENGGUNAKAN DOMINATRIX SEQUENCE!\n";

                return false;
            }

            if (target->dominatrixSequence)
            {
                cout << "\nTARGET SUDAH ADA DALAM KENDALI!\n";
                return false;
            }

            target->dominatrixSequence = true;

            cout << "\nDOMINATRIX SEQUENCE DIJALANKAN...\n";
            Sleep(1000);

            cout << "\nPILIH MODE KONTROL:\n";
            cout << "[1] PAKSA MENEMBAK DIRI SENDIRI\n";
            cout << "[2] PAKSA MENEMBAK LAWAN\n";
            cout << "PILIHAN: ";

            int choice;
            if (!(cin >> choice))
            {
                cin.clear();
                cin.ignore(1000, '\n');

                cout << "\nTARGET TIDAK VALID!\n";
                cout << "DOMINATRIX SEQUENCE DIBATALKAN...\n";
                target->dominatrixSequence = false;

                return false;
            }

            if (choice == 1)
            {
                target->dominatrixMode = 1;
                cout << "\n" << target->name << " AKAN DIPAKSA MENEMBAK DIRI SENDIRI!\n";
            }
            else if (choice == 2)
            {
                target->dominatrixMode = 2;
                cout << "\n" << target->name << " AKAN DIPAKSA MENEMBAK LAWAN!\n";
            }
            else
            {
                cout << "\nTARGET TIDAK VALID!\n";
                cout << "DOMINATRIX SEQUENCE DIBATALKAN...\n";
                target->dominatrixSequence = false;

                return false;
            }
            return true;
        }
        else
        {
            // target sudah dalam control

            if (target->skipTurn)
            {
                cout << "\n"
                << target
                << " SEDANG DALAM EFEK KONTROL!\n";
                cout << "TIDAK BISA MENGGUNAKAN DOMINATRIX SEQUENCE!\n";

                return false;
            }

            if (target->dominatrixSequence)
            {
                cout << "\nTARGET SUDAH DALAM KENDALI!\n";

                return false;
            }

            target->dominatrixSequence = true;

            cout << "\nDOMINATRIX SEQUENCE DIJALANKAN...\n";
            Sleep(1000);

            // ========================================
            // AI DECISION MODE
            // ========================================

            // DAMAGE BUFF
            // paksa self shot

            if (target->supercharged ||
                target->hyperbarrel)
            {
                target->dominatrixMode = 1;
            }

            // DEFENSIVE BUFF
            // paksa tembak dealer

            else if (target->stabilizer ||
                    target->reflectionField)
            {
                target->dominatrixMode = 2;
            }

            // RANDOM NORMAL MODE

            else
            {   
                int dominatrixChoice = rand() % 100;
                if (dominatrixChoice > 20)
                {
                    target->dominatrixMode = 1;
                }
                else
                {
                    target->dominatrixMode = 2;
                }
            }
            return true;
        }
        
    }

    // REFLECTION FIELD

    else if (itemName == "REFLECTION FIELD")
    {
        if (user->reflectionField)
        {
            cout << "\nREFLECTION FIELD SUDAH AKTIF!\n";
            return false;
        }

        user->reflectionField = true;

        cout << "\nREFLECTION FIELD AKTIF!\n";
        cout << "SEMUA DAMAGE DARI PENEMBAK AKAN DIPANTULKAN KEMBALI KE PENEMBAK!\n";

        return true;
    }

    // HYPERBARREL ACCELERATOR

    else if (itemName == "HYPERBARREL ACCELERATOR")
    {   
        if (user->supercharged || user->stabilizer || user->rogueProtocol || user->paradoxRound)
        {
            cout << "\nCHAMBER MODIFIER SUDAH AKTIF!\n";
            cout << "TIDAK BISA MENGGUNAKAN HYPERBARREL ACCELERATOR!\n";
            return false;
        }

        if (user->hyperbarrel)
        {
            cout << "\nHYPERBARREL ACCELERATOR SUDAH AKTIF!\n";
            return false;
        }

        user->hyperbarrel = true;

        cout << "\nHYPERBARREL ACCELERATOR AKTIF!\n";
        cout << "LIVE BULLET SELANJUTNYA MEMILIKI 25% CHANCE UNTUK MEMBERIKAN CRITICAL DAMAGE (x3)\n";
        cout << "CRITICAL DAMAGE JUGA MEMILIKI 50% CHANCE UNTUK MENGAGALKAN OVERDRIVE MODE TARGET!\n";
    }

    // CORE NEUTRALIZER

    else if (itemName == "CORE NEUTRALIZER")
    {
        string possibleBuffs[3];
        int count = 0;

        // cek buff aktif lawan
        if (target->stabilizer)
            possibleBuffs[count++] = "STABILIZER ENERGY";

        if (target->supercharged )
            possibleBuffs[count++] = "SUPERCHARGED PULSE";

        if (target->hyperbarrel)
            possibleBuffs[count++] = "HYPERBARREL ACCELERATOR";

        // tidak ada buff
        if (count == 0)
        {
            cout << "\nTARGET TIDAK MEMILIKI BUFF!\n";
            return false;
        }

        // pilih random buff
        int r = rand() % count;
        string removed = possibleBuffs[r];

        // hapus efeknya
        if (removed == "STABILIZER ENERGY")
            target->stabilizer = false;

        else if (removed == "SUPERCHARGED PULSE")
            target->supercharged = false;

        else if (removed == "HYPERBARREL ACCELERATOR")
            target->hyperbarrel = false;

        setColor(11); 
        cout << "\nCORE NEUTRALIZER AKTIF!\n";
        cout << "BUFF LAWAN YANG TERHAPUS: " << removed << "\n";
        setColor(7);
    }

    // MATRIX REBOOT

    else if (itemName == "MATRIX REBOOT")
    {   
        if (!isDealer)
        {
            cout << "\nMATRIX REBOOT AKTIF!\n";
            Sleep(1000);

            cout << "\nPILIH TARGET REBOOT:\n";
            cout << "[1] DIRI SENDIRI\n";
            cout << "[2] LAWAN\n";
            cout << "PILIHAN: ";

            int choice;
            if (!(cin >> choice))
            {
                cin.clear();
                cin.ignore(1000, '\n');

                cout << "\nTARGET TIDAK VALID!\n";
                cout << "MATRIX REBOOT DIBATALKAN...\n";

                return false;
            }

            cin.ignore(1000, '\n');
            
            if (choice == 1 || choice == 2)
            { 
                bool targetSelf = (choice == 1);
                Player* affected = (targetSelf ? user : target);

                cout << "\nINISIASI PROSES REBOOT...\n";
                Sleep(1000);

                // =========================
                // SELF TARGET
                // =========================

                if (targetSelf)
                {
                    bool hasSynapse = affected->skipTurn;
                    bool hasDominatrix = affected->dominatrixSequence;

                    // tidak ada efek

                    if (!hasSynapse && !hasDominatrix)
                    {
                        cout << "\nTIDAK ADA EFEK KONTROL YANG DITEMUKAN!\n";
                        cout << "PROSES REBOOT DIBATALKAN...\n";

                        return false;
                    }

                    cout << "\nMELAKUKAN REBOOT PADA DIRI SENDIRI...\n";
                    Sleep(1000);

                    // hanya synapse

                    if (hasSynapse && !hasDominatrix)
                    {
                        affected->skipTurn = false;

                        cout << "EFEK SYNAPSE LOCK TERHAPUS!\n";
                    }

                    // hanya dominatrix

                    else if (!hasSynapse && hasDominatrix)
                    {
                        affected->dominatrixSequence = false;
                        affected->dominatrixMode = 0;

                        cout << "EFEK DOMINATRIX TERHAPUS!\n";
                    }

                    // keduanya ada → random

                    else
                    {
                        int effect = rand() % 2;

                        if (effect == 0)
                        {
                            affected->skipTurn = false;

                            cout << "EFEK SYNAPSE LOCK TERHAPUS!\n";
                        }
                        else
                        {
                            affected->dominatrixSequence = false;
                            affected->dominatrixMode = 0;

                            cout << "EFEK DOMINATRIX TERHAPUS!\n";
                        }
                    }
                }

                // =========================
                // ENEMY TARGET
                // =========================

                else
                {
                    bool hasSynapse = affected->skipTurn;
                    bool hasReflection = affected->reflectionField;

                    // tidak ada efek

                    if (!hasSynapse && !hasReflection)
                    {
                        cout << "\nTIDAK ADA EFEK KONTROL YANG DITEMUKAN!\n";
                        cout << "PROSES REBOOT DIBATALKAN...\n";

                        return false;
                    }

                    cout << "\nMELAKUKAN REBOOT PADA LAWAN...\n";
                    Sleep(1000);

                    // hanya synapse

                    if (hasSynapse && !hasReflection)
                    {
                        affected->skipTurn = false;

                        cout << "EFEK SYNAPSE LOCK LAWAN TERHAPUS!\n";
                    }

                    // hanya reflection

                    else if (!hasSynapse && hasReflection)
                    {
                        affected->reflectionField = false;

                        cout << "EFEK REFLECTION FIELD LAWAN TERHAPUS!\n";
                    }

                    // keduanya ada → random

                    else
                    {
                        int effect = rand() % 2;

                        if (effect == 0)
                        {
                            affected->skipTurn = false;

                            cout << "EFEK SYNAPSE LOCK LAWAN TERHAPUS!\n";
                        }
                        else
                        {
                            affected->reflectionField = false;

                            cout << "EFEK REFLECTION FIELD LAWAN TERHAPUS!\n";
                        }
                    }
                }
            }
            else
            {
                cout << "\nTARGET TIDAK VALID!\n";
                cout << "MATRIX REBOOT DIBATALKAN...\n";

                return false;
            }
        }
        else
        {
            cout << "\nMATRIX REBOOT AKTIF...\n";
            Sleep(1000);

            bool selfControlled =
                user->skipTurn ||
                user->dominatrixSequence;

            bool enemyControlled =
                target->skipTurn ||
                target->reflectionField;

            // tidak ada efek sama sekali

            if (!selfControlled && !enemyControlled)
            {
                cout << "\nTARGET TIDAK MEMILIKI EFEK KONTROL!\n";

                return false;
            }

            bool targetSelf;

            // ========================================
            // PRIORITAS TARGET
            // ========================================

            // hanya dealer kena efek

            if (selfControlled && !enemyControlled)
            {
                targetSelf = true;
            }

            // hanya player kena efek

            else if (!selfControlled && enemyControlled)
            {
                targetSelf = false;
            }

            // keduanya kena efek → random

            else
            {
                targetSelf = rand() % 2;
            }

            Player* affected =
                (targetSelf ? user : target);

            cout << "\nINISIASI PROSES REBOOT...\n";
            Sleep(1000);

            // ========================================
            // SELF TARGET
            // ========================================

            if (targetSelf)
            {
                bool hasSynapse =
                    affected->skipTurn;

                bool hasDominatrix =
                    affected->dominatrixSequence;

                cout << "\nMELAKUKAN REBOOT PADA DIRI SENDIRI...\n";
                Sleep(1000);

                // hanya synapse

                if (hasSynapse && !hasDominatrix)
                {
                    affected->skipTurn = false;

                    cout << "EFEK SYNAPSE LOCK TERHAPUS!\n\n";
                }

                // hanya dominatrix

                else if (!hasSynapse && hasDominatrix)
                {
                    affected->dominatrixSequence = false;
                    affected->dominatrixMode = 0;

                    cout << "EFEK DOMINATRIX TERHAPUS!\n\n";
                }

                // random

                else
                {
                    int effect = rand() % 2;

                    if (effect == 0)
                    {
                        affected->skipTurn = false;

                        cout << "EFEK SYNAPSE LOCK TERHAPUS!\n\n";
                    }
                    else
                    {
                        affected->dominatrixSequence = false;
                        affected->dominatrixMode = 0;

                        cout << "EFEK DOMINATRIX TERHAPUS!\n\n";
                    }
                }
            }

            // ========================================
            // ENEMY TARGET
            // ========================================

            else
            {
                bool hasSynapse =
                    affected->skipTurn;

                bool hasReflection =
                    affected->reflectionField;

                cout << "\nMELAKUKAN REBOOT PADA LAWAN...\n";
                Sleep(1000);

                // hanya synapse

                if (hasSynapse && !hasReflection)
                {
                    affected->skipTurn = false;

                    cout << "EFEK SYNAPSE LOCK LAWAN TERHAPUS!\n\n";
                }

                // hanya reflection

                else if (!hasSynapse && hasReflection)
                {
                    affected->reflectionField = false;

                    cout << "EFEK REFLECTION FIELD LAWAN TERHAPUS!\n\n";
                }

                // random

                else
                {
                    int effect = rand() % 2;

                    if (effect == 0)
                    {
                        affected->skipTurn = false;

                        cout << "EFEK SYNAPSE LOCK LAWAN TERHAPUS!\n\n";
                    }
                    else
                    {
                        affected->reflectionField = false;

                        cout << "EFEK REFLECTION FIELD LAWAN TERHAPUS!\n\n";
                    }
                }
            }
        }
    }

    // CHAOS ENGINE

    else if (itemName == "CHAOS ENGINE")
    {   
        if (user->rogueProtocol || user->paradoxRound)
        {
            cout << "\nCHAOS STATE SEDANG BERJALAN!\n";
            cout << "TIDAK BISA MENGGUNAKAN CHAOS ENGINE!\n";
            return false;
        }

        if (user->chaosState || user->rogueProtocol)
        {
            cout << "\nCHAOS ENGINE SUDAH AKTIF!\n";
            return false;
        }

        bullets.randomizeBullet();
        user->chaosState = true;
        target->chaosState = true;

        setColor(12);
        cout << "\nCHAMBER MULAI BERGETAR SECARA EKSTREM!\n";
        cout << "SELURUH PELURU MENJADI TIDAK STABIL DAN AKAN DIACAK ULANG!\n";
        setColor(7);
    }

    // QUANTUM COIN

    else if (itemName == "QUANTUM COIN")
    {
        int fate = rand() % 2;
        int bonus= rand() % 10;

        setColor(11); 
        cout << "\nQUANTUM COIN BERPUTAR...\n";
        setColor(7);

        Sleep(2000);

        if (fate == 0)
            {
                user->hp = 4;

                setColor(10);

                cout << "\nFULL HEAL!\n";

                if (bonus < 4) {
                    if (bonus == 0) {
                        setColor(11); 

                        user->ap = 1;
                        cout << "\nMENDAPATKAN BONUS 2 AP!\n";

                        setColor(7);
                    } 
                    else
                    {
                    setColor(11); 

                    user->ap = 1;
                    cout << "\nMENDAPATKAN BONUS 1 AP!\n";

                    setColor(7);
                    }
                }
            }
            else
            {
                user->hp = 0;
                user->alive = false;

                setColor(4);

                cout << "\nQUANTUM FAILURE...\n";

                cout << user->name
                    << " MATI!\n";

                setColor(7);

                if (!isDealer && user->hp == 0)
                {
                    showGameOver(*user);
                    exit(0);
                }
            }

            setColor(7);
        }

        // HIJACK MODULE

        else if (itemName == "HIJACK MODULE")
        {
            int result = rand() % 2;

            cout << "\nMELAKUKAN HIJACK MODULE...\n";
            Sleep(1500);

            // ========================================
            // BERHASIL MENCURI
            // ========================================

            if (result == 0)
            {
                string stolenItem;

                ItemNode* stolenNode =
                    target->inventory.getRandomNode(stolenItem);

                // target tidak punya item

                if (stolenNode == NULL)
                {
                    cout << "\nHIJACK BERHASIL!\n";
                    cout << "NAMUN LAWAN TIDAK MEMILIKI ITEM!\n";

                    return true;
                }

                // hapus item dari target

                target->inventory.removeNode(stolenNode);

                // tambahkan ke user

                user->inventory.addItem(stolenItem);

                setColor(10);

                cout << "\nHIJACK BERHASIL!\n";
                cout << "ITEM DICURI : "
                    << stolenItem << endl;

                setColor(7);
            }

            // ========================================
            // GAGAL → kehilangan item sendiri
            // ========================================

            else
            {
                string lostItem;

                // cek apakah inventory kosong

                if (user->inventory.countItem() <= 1)
                {
                    cout << "\nHIJACK GAGAL!\n";
                    cout << "NAMUN INVENTORY KOSONG!\n";

                    return true;
                }

                ItemNode* lostNode = NULL;

                // cari item random selain HIJACK MODULE

                do
                {
                    lostNode =
                        user->inventory.getRandomNode(lostItem);

                    if (lostNode == NULL)
                    {
                        break;
                    }

                } while (lostItem == "HIJACK MODULE");

                // safety check

                if (lostNode == NULL)
                {
                    cout << "\nHIJACK GAGAL!\n";
                    cout << "TIDAK ADA ITEM VALID UNTUK DIHAPUS!\n";

                    return true;
                }

                // hapus item

                user->inventory.removeNode(lostNode);

                setColor(4);

                cout << "\nHIJACK GAGAL!\n";
                cout << "ITEM YANG HILANG : "
                    << lostItem << endl;

                setColor(7);
            }

            return true;
        }
        
        // ROGUE PROTOCOL

        else if (itemName == "ROGUE PROTOCOL")
        {   
            if (user->supercharged || user->stabilizer || user->hyperbarrel)
            {
                cout << "\nCHAMBER MODIFIER SUDAH AKTIF!\n";
                cout << "TIDAK BISA MENGGUNAKAN ROGUE PROTOCOL!\n";
                return false;
            }

            if (user->chaosState || user->paradoxRound)
            {
                cout << "\nCHAOS STATE SEDANG BERJALAN!\n";
                cout << "TIDAK BISA MENGGUNAKAN CHAOS ENGINE!\n";
                return false;
            }
            
            if (user->rogueProtocol)
            {
                cout << "\nROGUE PROTOCOL SUDAH AKTIF!\n";

                return false;
            }

            user->rogueProtocol = true;

            // paksa peluru teratas jadi LIVE

            if (!bullets.isEmpty())
            {
                bullets.bullet[bullets.top] = 1;
            }

            setColor(12);

            cout << "\nINISIASI ROGUE PROTOCOL...\n";
            cout << "HATI-HATI, CHAMBER MENJADI TIDAK STABIL!\n";
            cout << "TARGET PENEMBAKAN AKAN MENJADI ACAK!\n";

            setColor(7);
        }

        // PARADOX ROUND

        else if (itemName == "PARADOX ROUND")
        {   
            if (user->supercharged || user->stabilizer || user->hyperbarrel)
            {
                cout << "\nCHAMBER MODIFIER SUDAH AKTIF!\n";
                cout << "TIDAK BISA MENGGUNAKAN PARADOX ROUND!\n";
                return false;
            }

            if (user->chaosState || user->rogueProtocol)
            {
                cout << "\nCHAOS STATE SEDANG BERJALAN!\n";
                cout << "TIDAK BISA MENGGUNAKAN CHAOS ENGINE!\n";
                return false;
            }

            // sudah aktif

            if (user->paradoxRound)
            {
                cout << "\nPARADOX ROUND SUDAH AKTIF!\n";

                return false;
            }

            user->paradoxRound = true;

            // paksa peluru jadi LIVE

            if (!bullets.isEmpty())
            {
                bullets.bullet[bullets.top] = 1;
            }

            setColor(13);

            cout << "\nPARADOX ROUND AKTIF!\n";
            cout << "PELURU BERIKUTNYA AKAN MENJADI TIDAK STABIL!\n";

            setColor(7);

            return true;
        }
    return true;
}

// ========================================
// lawan gacha item
// ========================================

bool aiWantsToUseItem(int baseChance)
{
    int roll = rand() % 100;
    return roll < baseChance;
}

ItemNode* findItemByName(Inventory &inv, string target, string &itemName)
{
    ItemNode *temp = inv.head;

    while (temp != NULL)
    {
        if (temp->itemName == target)
        {
            itemName = temp->itemName;
            return temp;
        }
        temp = temp->next;
    }

    return NULL;
}

bool aiTryUseItem(
    Player &dealer,
    Player &player,
    BulletStack &bullets,
    bool &musuhDoubleDamage,
    const string &itemName,
    int chance,
    bool &aiUsedItem
)
{
    if (!aiWantsToUseItem(chance))
        return false;

    string item;
    ItemNode* node = findItemByName(dealer.inventory, itemName, item);

    if (node == NULL)
        return false;

    cout << "\n" << dealer.name << " MENGGUNAKAN " << itemName << "!\n";

    useItemEffect(
        item,
        &dealer,
        &player,
        bullets,
        musuhDoubleDamage,
        false,
        true
    );

    dealer.inventory.removeNode(node);
    aiUsedItem = true;

    Sleep(1200);
    return true;
}

// ========================================
// lawan ngitung sisa peluru
// (probability scanner)
// ========================================

void countBullet(
        BulletStack &bullets,
        int &live,
        int &blank
    )
    {
        live = 0;
        blank = 0;

        for (int i = 0; i <= bullets.top; i++)
        {
            if (bullets.bullet[i] == 1)
            {
                live++;
            }
            else
            {
                blank++;
            }
        }
    }
