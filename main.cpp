#include<iostream>
#include<string>
 
  class Player {
      private :
      std::string nickname;
      int health;
      public:
      Player(std::string name = "Steve", int hp = 20) : nickname(name), health(hp) {
        std::cout << "[Player] " << nickname << " заспавнився! HP: " << health << std::endl;
    }
};
class DiamondSword {
public:
    int damage;
    DiamondSword() : damage(7) {
        std::cout << "[Item] Алмазний меч створено! Damage: " << damage << std::endl;
    }
};
class IronArmor {
public:
    int defense;
    IronArmor() : defense(5) {
        std::cout << "[Item] Залізна броня одягнена! Defense: " << defense << std::endl;
    }
};
   int main (){
       Player p1("VladosPro228");
       DiamondSword sword;
       IronArmor armor;
       return 0;
   }
