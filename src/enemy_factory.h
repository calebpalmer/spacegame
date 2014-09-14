#ifndef ENEMY_FACTORY_H
#define ENEMY_FACTORY_H

#include "gameobject.h"

#include <memory>
#include <map>

class EnemyFactory{
 private:
  EnemyFactory(const EnemyFactory&);
  EnemyFactory& operator=(const EnemyFactory&);
  EnemyFactory();
 public:
  virtual ~EnemyFactory();
  std::unique_ptr<GameObject> makeEnemy(std::string enemyKey);
  bool registerEnemy(std::string enemyKey, std::unique_ptr<ObjectCreator> creator);
  static EnemyFactory* getInstance();
  
 private:
  struct Enemy{
    int id;
  };

  std::map<std::string, ObjectCreator*> m_enemyMap;
  static EnemyFactory* s_pEnemyFactory;
};

#endif // ENEMY_FACTORY_H
