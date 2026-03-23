#include <iostream>
#include <string>
#include <utility>

class WorldEntity {
protected:
    double x, y;
public:
    WorldEntity(double _x = 0, double _y = 0) : x(_x), y(_y) {
        std::cout << "[WorldEntity] Created at (" << x << ", " << y << ")" << std::endl;
    }
    virtual ~WorldEntity() {
        std::cout << "[WorldEntity] Destroyed" << std::endl;
    }
};

class Player : public WorldEntity {
protected:
    std::string nickname;
    int health;
    static int playerCount;

public:
    Player() : Player("Steve", 20) {}

    Player(std::string name, int hp, double _x = 0, double _y = 0) 
        : WorldEntity(_x, _y), nickname(name), health(hp) {
        playerCount++;
        std::cout << "[Spawn] " << nickname << " HP: " << health << std::endl;
    }

    Player(const Player& other) 
        : WorldEntity(other.x, other.y), nickname(other.nickname + "_Copy"), health(other.health) {
        playerCount++;
        std::cout << "[Copy] Created: " << nickname << std::endl;
    }

    Player(Player&& other) noexcept 
        : WorldEntity(std::move(other.x), std::move(other.y)), 
          nickname(std::move(other.nickname)), health(other.health) {
        other.health = 0;
        std::cout << "[Move] Data moved!" << std::endl;
    }

    static int getOnline() {
        return playerCount;
    }

    void operator-() {
        this->health -= 10;
        if (this->health < 0) this->health = 0;
        std::cout << "[Effect] " << nickname << " took damage!" << std::endl;
    }

    Player& operator+(int heal) {
        this->health += heal;
        std::cout << "[Effect] " << nickname << " healed!" << std::endl;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Player& p) {
        os << "Nickname: " << p.nickname << " | HP: " << p.health << " | Pos: (" << p.x << "," << p.y << ")";
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Player& p) {
        std::cout << "Nickname: ";
        is >> p.nickname;
        std::cout << "Health: ";
        is >> p.health;
        return is;
    }

    void updateProfile(std::string nickname, int health) {
        this->nickname = nickname; 
        this->health = health;
    }

    void showStats() const {
        if (nickname.empty()) {
            std::cout << "Stats: Empty." << std::endl;
        } else {
            std::cout << "Nickname: " << nickname << " | HP: " << health << " | Pos: (" << x << "," << y << ")" << std::endl;
        }
    }

    ~Player() {
        if (!nickname.empty()) {
            playerCount--;
            std::cout << "[Quit] " << nickname << " left!" << std::endl;
        }
    }
};

int Player::playerCount = 0;

class Admin : public Player {
public:
    Admin(std::string name) : Player(name, 999, 0, 0) {
        std::cout << "[Admin] God mode for " << nickname << std::endl;
    }
    
    ~Admin() {
        std::cout << "[Admin] Logged out" << std::endl;
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

int main() {
    Admin superuser("Notch");
    std::cout << "----------------" << std::endl;

    Player p1("VladosPro228", 50, 10, 20);
    const Player admin_bot("Admin_Bot", 999);

    -p1;
    p1 + 15;

    std::cout << "\n--- Test Output Operator ---" << std::endl;
    std::cout << "p1: " << p1 << std::endl;
    std::cout << "superuser: " << superuser << std::endl;

    std::cout << "\nOnline count: " << Player::getOnline() << std::endl;
    std::cout << "----------------\n" << std::endl;

    return 0;
}