#include <iostream>
#include <string>
#include <utility>
#include <vector>

class IDamageable {
public:
    virtual void takeDamage(int amount) = 0; 
    virtual ~IDamageable() {} 
};

class WorldEntity {
protected:
    double x, y;
public:
    WorldEntity(double _x = 0, double _y = 0) : x(_x), y(_y) {
        std::cout << "[WorldEntity] Створено в (" << x << ", " << y << ")" << std::endl;
    }

    void identify() { 
        std::cout << "[Base] Я просто сутність світу." << std::endl; 
    }

    virtual void action() { 
        std::cout << "[Base] Сутність світу бездіяльно стоїть." << std::endl; 
    }

    virtual ~WorldEntity() {
        std::cout << "[WorldEntity] Видалено зі світу" << std::endl;
    }
};

class DiamondSword {
private: 
    int damage;
public:
    DiamondSword(int dmg = 7) : damage(dmg) {}
    int getDamage() const { return damage; }
};

class IronArmor {
private: 
    int defense;
public:
    IronArmor(int def = 5) : defense(def) {}
    int getDefense() const { return defense; }
};

class Player : public WorldEntity, public IDamageable {
protected:
    std::string nickname;
    int health;
    static int playerCount;
    DiamondSword sword;
    IronArmor armor;

public:
    Player(std::string name, int hp, double _x = 0, double _y = 0) 
        : WorldEntity(_x, _y), nickname(name), health(hp), sword(7), armor(5) {
        playerCount++;
        std::cout << "[Spawn] " << nickname << " заспавнився!" << std::endl;
    }

    void identify() { 
        std::cout << "[Derived] Я Гравець: " << nickname << std::endl; 
    }

    void action() override { 
        std::cout << "[Player] " << nickname << " махає мечем на " << sword.getDamage() << " шкоди!" << std::endl; 
    }

    void takeDamage(int amount) override {
        int finalDamage = amount - armor.getDefense();
        if (finalDamage < 0) finalDamage = 0;
        health -= finalDamage;
        std::cout << "[Hit] " << nickname << " отримав " << finalDamage << " шкоди. HP: " << health << std::endl;
    }

    void operator-() { 
        health -= 10; 
        std::cout << "[Effect] " << nickname << " отримав шкоду!" << std::endl; 
    }

    Player& operator+(int heal) { 
        health += heal; 
        return *this; 
    }

    friend std::ostream& operator<<(std::ostream& os, const Player& p) {
        os << "Нік: " << p.nickname << " | HP: " << p.health;
        return os;
    }

    static int getOnline() { return playerCount; }

    ~Player() {
        if (!nickname.empty()) {
            playerCount--;
            std::cout << "[Quit] " << nickname << " вийшов з гри!" << std::endl;
        }
    }
};

int Player::playerCount = 0;

class Admin final : public Player {
public:
    Admin(std::string name) : Player(name, 999) {}
    
    void action() override {
        std::cout << "[Admin] " << nickname << " редагує світ (Creative Mode)!" << std::endl;
    }
};

class WoodenBlock : public IDamageable {
public:
    void takeDamage(int amount) override {
        std::cout << "[Block] Дерев'яний блок тріщить! Отримано " << amount << " шкоди." << std::endl;
    }
};

int main() {
    std::cout << "--- 1. Static Binding ---" << std::endl;
    Player p1("Vlados", 50, 10, 20);
    WorldEntity* staticPtr = &p1;
    staticPtr->identify(); 
    
    std::cout << "\n--- 3. Dynamic Polymorphism (Pointer) ---" << std::endl;
    WorldEntity* polyPtr = &p1;
    polyPtr->action(); 
    
    std::cout << "\n--- 6. Dynamic Polymorphism (Reference) ---" << std::endl;
    Admin god("Notch");
    WorldEntity& entityRef = god;
    entityRef.action(); 
    
    std::cout << "\n--- 8. Interface IDamageable ---" << std::endl;
    WoodenBlock oakLog;
    IDamageable* targets[2];
    targets[0] = &p1;     
    targets[1] = &oakLog; 

    for(int i = 0; i < 2; i++) {
        targets[i]->takeDamage(15); 
    }

    std::cout << "\n--- Destructors ---" << std::endl;
    
    return 0;
}