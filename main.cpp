#include <iostream>
#include <string>
#include <utility>

class WorldEntity {
protected:
    double x, y;
public:
    WorldEntity(double _x = 0, double _y = 0) : x(_x), y(_y) {
        std::cout << "[WorldEntity] Створено в координатах (" << x << ", " << y << ")" << std::endl;
    }

    WorldEntity(const WorldEntity& other) : x(other.x), y(other.y) {}
    WorldEntity(WorldEntity&& other) noexcept : x(other.x), y(other.y) { other.x = other.y = 0; }
    WorldEntity& operator=(const WorldEntity& other) {
        if (this != &other) { x = other.x; y = other.y; }
        return *this;
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

class Player : public WorldEntity {
protected:
    std::string nickname;
    int health;
    static int playerCount;
    DiamondSword sword;
    IronArmor armor;

public:
    Player() : Player("Steve", 20) {}

    Player(std::string name, int hp, double _x = 0, double _y = 0) 
        : WorldEntity(_x, _y), nickname(name), health(hp), sword(7), armor(5) {
        playerCount++;
        std::cout << "[Spawn] " << nickname << " заспавнився! HP: " << health << std::endl;
    }

    Player(const Player& other) 
        : WorldEntity(other), nickname(other.nickname + "_Copy"), health(other.health), 
          sword(other.sword), armor(other.armor) {
        playerCount++;
        std::cout << "[Copy] Створено копію гравця: " << nickname << std::endl;
    }

    Player(Player&& other) noexcept 
        : WorldEntity(std::move(other)), nickname(std::move(other.nickname)), 
          health(other.health), sword(std::move(other.sword)), armor(std::move(other.armor)) {
        other.health = 0;
        std::cout << "[Move] Дані гравця переміщено!" << std::endl;
    }

    Player& operator=(const Player& other) {
        if (this != &other) {
            WorldEntity::operator=(other);
            nickname = other.nickname;
            health = other.health;
            sword = other.sword;
            armor = other.armor;
        }
        return *this;
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
        os << "Нікнейм: " << p.nickname << " | HP: " << p.health << " | Поз: (" << p.x << "," << p.y << ")";
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Player& p) {
        std::cout << "Введіть нікнейм: ";
        is >> p.nickname;
        std::cout << "Введіть HP: ";
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
            std::cout << "Нікнейм: " << nickname << " | HP: " << health << " | Поз: (" << x << "," << y << ")" << std::endl;
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

class Admin : public Player {
public:
    Admin(std::string name) : Player(name, 999, 0, 0) {
        std::cout << "[Admin] Режим бога активовано для " << nickname << std::endl;
    }
    
    Admin(const Admin& other) : Player(other) {
        std::cout << "[Admin] Копіювання адміна" << std::endl;
    }
    
    Admin& operator=(const Admin& other) {
        Player::operator=(other);
        return *this;
    }
    
    ~Admin() {
        std::cout << "[Admin] Адмін вийшов з сервера" << std::endl;
    }
};

int main() {
    Admin superuser("Notch");
    std::cout << "----------------" << std::endl;

    Player p1("VladosPro228", 50, 10, 20);
    Player p2 = p1; 

    -p1;
    p1 + 15;

    std::cout << "\n--- Тест виведення даних (<<) ---" << std::endl;
    std::cout << "Гравець p1: " << p1 << std::endl;
    std::cout << "Копія p2: " << p2 << std::endl;
    std::cout << "Адмін: " << superuser << std::endl;

    std::cout << "\nГравців онлайн: " << Player::getOnline() << std::endl;
    std::cout << "----------------\n" << std::endl;

    return 0;
} 