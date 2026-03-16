#include<iostream>
#include<string>

class Player {
private:
    std::string nickname;
    int health;

public:
    Player() : Player("Steve", 20) {}

    Player(std::string name, int hp) : nickname(name), health(hp) {
        std::cout << "[Player] " << nickname << " заспавнився! HP: " << health << std::endl;
    }

    ~Player() {
        std::cout << "[Player] " << nickname << " вийшов з гри!" << std::endl;
    }

    void showStats() {
        std::cout << "Nickname: " << nickname << " | HP: " << health << std::endl;
    }
};

class DiamondSword {
private:
    int damage;

public:
    DiamondSword() : DiamondSword(7) {}

    DiamondSword(int dmg) : damage(dmg) {
        std::cout << "[Item] Алмазний меч створено! Damage: " << damage << std::endl;
    }

    ~DiamondSword() {
        std::cout << "[Item] Алмазний меч знищено!" << std::endl;
    }

    int getDamage() {
        return damage;
    }
};

class IronArmor {
private:
    int defense;

public:
    IronArmor() : IronArmor(5) {}

    IronArmor(int def) : defense(def) {
        std::cout << "[Item] Залізна броня одягнена! Defense: " << defense << std::endl;
    }

    ~IronArmor() {
        std::cout << "[Item] Броню знято!" << std::endl;
    }

    int getDefense() {
        return defense;
    }
};

int main() {

    Player p1("VladosPro228", 30);
    Player p2;

    DiamondSword sword;
    IronArmor armor;

    p1.showStats();

    std::cout << "Damage меча: " << sword.getDamage() << std::endl;
    std::cout << "Defense броні: " << armor.getDefense() << std::endl;

    return 0;
}
