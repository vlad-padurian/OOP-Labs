#include <string>
#include <vector>
#include <memory>    
#include <fstream>   
#include <stdexcept> 

using namespace std;

class IDamageable {
public:
    virtual void takeDamage(int amount) = 0;
    virtual ~IDamageable() {}
};

class WorldEntity {
protected:
    double x, y;
public:
    WorldEntity(double _x = 0, double _y = 0) : x(_x), y(_y) {}
    virtual void action() { cout << "[Entity] Бездіяльно стоїть.\n"; }
    virtual ~WorldEntity() {}
};


class DiamondSword {
    int damage;
public:
    DiamondSword(int dmg = 7) : damage(dmg) {}
    int getDamage() const { return damage; }
};

class IronArmor {
    int defense;
public:
    IronArmor(int def = 5) : defense(def) {}
    int getDefense() const { return defense; }
};


class Player : public WorldEntity, public IDamageable {
protected:
    string nickname;
    int health;
    DiamondSword sword;
    IronArmor armor;

public:
    Player(string name, int hp, double _x = 0, double _y = 0) 
        : WorldEntity(_x, _y), nickname(name), health(hp) {}

    string getNickname() const { return nickname; }
    int getHealth() const { return health; }

    void action() override {
        cout << "[Player] " << nickname << " махає мечем на " << sword.getDamage() << " шкоди!\n";
    }

    void takeDamage(int amount) override {
        int finalDamage = amount - armor.getDefense();
        if (finalDamage < 0) finalDamage = 0;
        health -= finalDamage;
        cout << "[Hit] " << nickname << " отримав " << finalDamage << ". HP: " << health << "\n";
    }

    friend ostream& operator<<(ostream& os, const Player& p) {
        os << "Гравець: " << p.nickname << " | HP: " << p.health;
        return os;
    }
};


class GameManager {
private:
    vector<unique_ptr<Player>> players; 
    bool isAdmin = false;              
    const string adminPassword = "admin228pass";
    const string dataFile = "world_data.txt";
    const string historyFile = "history.txt";

    void logAction(string msg) {
        ofstream log(historyFile, ios::app);
        if (log.is_open()) {
            log << "[HISTORY]: " << msg << "\n";
            log.close();
        }
    }

public:
    GameManager() {
        load(); 
    }

    void save() {
        ofstream out(dataFile);
        if (out.is_open()) {
            for (size_t i = 0; i < players.size(); ++i) {
                out << players[i]->getNickname() << " " << players[i]->getHealth() << "\n";
            }
            out.close();
            logAction("Дані успішно збережено у файл.");
        }
    }

    void load() {
        try {
            ifstream in(dataFile);
            if (!in) throw runtime_error("Файл даних не знайдено .");
            
            players.clear();
            string name;
            int hp;
            while (in >> name >> hp) {
               
                players.push_back(unique_ptr<Player>(new Player(name, hp)));
            }
            in.close();
            cout << "[System] Дані завантажено.\n";
        } catch (const exception& e) {
            cout << "[System] " << e.what() << "\n";
        }
    }

    void login() {
        int mode;
        cout << "--- ВХІД ---\n1. Користувач (Звичайний гравець)\n2. Адміністратор\nВибір: ";
        cin >> mode;
        if (mode == 2) {
            string pass;
            cout << "Введіть пароль: ";
            cin >> pass;
            if (pass == adminPassword) {
                isAdmin = true;
                cout << "Доступ Адміна дозволено!\n";
                logAction("Адмін увійшов у систему.");
            } else {
                cout << "Пароль невірний! Ви увійшли як Звичайний гравець.\n";
            }
        }
    }

    void run() {
        int choice = -1;
        while (choice != 0) {
            cout << "\n=== КОНСОЛЬНЕ МЕНЮ ===\n";
            if (isAdmin) {
                cout << "1. Додати гравця (Лише адмін)\n";
                cout << "2. Очистити світ (Лише адмін)\n";
            }
            cout << "3. Переглянути список гравців\n";
            cout << "0. Вихід\nВибір: ";
            cin >> choice;

            if (choice == 1 && isAdmin) {
                string n; int h;
                cout << "Нік: "; cin >> n;
                cout << "HP: "; cin >> h;
                players.push_back(unique_ptr<Player>(new Player(n, h)));
                save(); 
                logAction("Адмін додав гравця: " + n);
            } 
            else if (choice == 2 && isAdmin) {
                players.clear();
                save();
                logAction("Адмін очистив список гравців.");
                cout << "Світ очищено.\n";
            }
            else if (choice == 3) {
                cout << "\n--- ГРАВЦІ В ОНЛАЙНІ ---\n";
                if (players.empty()) cout << "Порожньо...\n";
                for (size_t i = 0; i < players.size(); ++i) {
                    cout << *players[i] << "\n";
                }
            }
        }
    }
};

int main() {
    setlocale(LC_ALL, "Ukrainian");

    GameManager game;
    game.login();
    game.run();

    return 0;
}