#ifndef ENEMY_FACTORY_H
#define ENEMY_FACTORY_H

#include "gameobject.h"

#include <memory>
#include <map>

class EnemyFactory{
 private:
  EnemyFactory(const EnemyFactory&);
  EnemyFactory& operator=(const EnemyFactory&);

 public:
  EnemyFactory(std::string enemyConfigPath);
  virtual ~EnemyFactory() {}
  std::unique_ptr<GameObject> makeEnemy(int enemyKey);
  
 private:
  struct Enemy{
    int id;
  };

  std::map<int, Enemy*> mEnemyMap;
  void loadEnemyMap(std::string enemyConfigPath);
};

#endif // ENEMY_FACTORY_H
