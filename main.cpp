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
   int main (){
       Player p1("VladosPro228");
       DiamondSword sword;
       return 0;
   }
іі