#ifndef LEVEL_H
#define LEVEL_H

#include "world.h"

#include <memory>
#include <string>
#include <vector>

class Level {

 public:
  struct EnemyWave{
    double startTime;
    std::vector<std::pair<std::string, int> > enemies; 
  };
  Level(int levelNumber, std::string levelDescription);
  void addWave(std::unique_ptr<EnemyWave> wave);
  void start();
  void update(double ms, World* world);
  int getLevelNumber() const;
  std::string getLevelDescription() const;
  int wavesRemaining() const;
  
 private:
  Level(const Level&);
  Level& operator=(const Level&);
 

 protected:
  double m_startTime;
  int m_levelNumber;
  std::string m_levelDescription;
  std::vector< std::unique_ptr<EnemyWave> > m_enemyWaves;
 
};

std::vector<std::unique_ptr<Level> > parseLevelFile(std::string filepath);

#endif // LEVEL_H

