#include <iostream>
#include <string>
#include <utility>

class Player {
private:
    std::string nickname;
    int health;
    static int playerCount;

public:
    Player() : Player("Steve", 20) {}

    Player(std::string name, int hp) : nickname(name), health(hp) {
        playerCount++;
        std::cout << "[Spawn] " << nickname << " заспавнився! HP: " << health << std::endl;
    }

    Player(const Player& other) : nickname(other.nickname + "_Copy"), health(other.health) {
        playerCount++;
        std::cout << "[Copy] Створено копію гравця: " << nickname << std::endl;
    }

    Player(Player&& other) noexcept : nickname(std::move(other.nickname)), health(other.health) {
        other.health = 0;
        std::cout << "[Move] Дані гравця переміщено!" << std::endl;
    }

    static int getOnline() {
        return playerCount;
    }

    void operator-() {
        this->health -= 10;
        if (this->health < 0) this->health = 0;
        std::cout << "[Effect] " << nickname << " отримав шкоду!" << std::endl;
    }

    Player& operator+(int heal) {
        this->health += heal;
        std::cout << "[Effect] " << nickname << " вилікувався!" << std::endl;
        return *this;
    }
friend std::ostream& operator<<(std::ostream& os, const Player& p) {
        os << "Nickname: " << p.nickname << " | HP: " << p.health;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Player& p) {
        std::cout << "Введіть Nickname: ";
        is >> p.nickname;
        std::cout << "Введіть Health: ";
        is >> p.health;
        return is;
    }
    void updateProfile(std::string nickname, int health) {
        this->nickname = nickname; 
        this->health = health;
    }

    void showStats() const {
        if (nickname.empty()) {
            std::cout << "Статистика: Гравець порожній." << std::endl;
        } else {
            std::cout << "Nickname: " << nickname << " | HP: " << health << std::endl;
        }
    }

    ~Player() {
        if (!nickname.empty()) {
            playerCount--;
            std::cout << "[Quit] " << nickname << " вийшов з гри!" << std::endl;
        }
    }
};

int Player::playerCount = 0;

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

int main() {
    Player p1("VladosPro228", 50);
    const Player admin("Admin_Bot", 999);

    -p1;
    p1 + 15;

   std::cout << "\n--- Тест оператора виведення (<<) ---" << std::endl;
    std::cout << "Об'єкт p1: " << p1 << std::endl;
    std::cout << "Об'єкт admin: " << admin << std::endl;

    std::cout << "\n--- Тест оператора введення (>>) ---" << std::endl;
    std::cin >> p1; // Введи нові дані для p1 з клавіатури

    std::cout << "\n--- Оновлений стан після введення ---" << std::endl;
    std::cout << p1 << std::endl;

    std::cout << "\nГравців онлайн: " << Player::getOnline() << std::endl;
    std::cout << "----------------\n" << std::endl;

    return 0;
}