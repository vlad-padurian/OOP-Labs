#include <iostream>
#include <string>
#include <utility>

class Player {
private:
    std::string nickname;
    int health;

public:
    Player() : Player("Steve", 20) {}

    Player(std::string name, int hp) : nickname(name), health(hp) {
        std::cout << "[Spawn] " << nickname << " заспавнився! HP: " << health << std::endl;
    }

    Player(const Player& other) : nickname(other.nickname + "_Copy"), health(other.health) {
        std::cout << "[Copy] Створено копію гравця: " << nickname << std::endl;
    }

    Player(Player&& other) noexcept : nickname(std::move(other.nickname)), health(other.health) {
        other.health = 0;
        std::cout << "[Move] Дані гравця переміщено!" << std::endl;
    }

    void updateProfile(std::string nickname, int health) {
        this->nickname = nickname; 
        this->health = health;
        std::cout << "[This] Поля оновлено через вказівник this." << std::endl;
    }

    ~Player() {
        if (nickname.empty()) {
            std::cout << "[Destructor] Видалено порожній об'єкт." << std::endl;
        } else {
            std::cout << "[Quit] " << nickname << " вийшов з гри!" << std::endl;
        }
    }

    void showStats() {
        if (nickname.empty()) {
            std::cout << "Статистика: Гравець порожній." << std::endl;
        } else {
            std::cout << "Nickname: " << nickname << " | HP: " << health << std::endl;
        }
    }
};

class DiamondSword {
private:
    int damage;
public:
    DiamondSword(int dmg = 7) : damage(dmg) {
        std::cout << "[Item] Алмазний меч створено! Damage: " << damage << std::endl;
    }
    ~DiamondSword() { std::cout << "[Item] Алмазний меч знищено!" << std::endl; }
    int getDamage() { return damage; }
};

class IronArmor {
private:
    int defense;
public:
    IronArmor(int def = 5) : defense(def) {
        std::cout << "[Item] Залізна броня одягнена! Defense: " << defense << std::endl;
    }
    ~IronArmor() { std::cout << "[Item] Броню знято!" << std::endl; }
    int getDefense() { return defense; }
};

int main() {
    Player p1("VladosPro228", 30);
    Player p2 = p1; 
    p2.updateProfile("NewNick", 50);
    Player p3 = std::move(p1);

    std::cout << "\n--- Summary ---" << std::endl;
    p2.showStats();
    p3.showStats();
    p1.showStats();
    std::cout << "----------------\n" << std::endl;

    return 0;
}