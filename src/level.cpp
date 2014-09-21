#include "level.h"

#include "enemy_factory.h"

#include "CapEngine.h"
#include <sstream>

using namespace std;
using namespace CapEngine;

Level::Level(int levelNumber, string levelDescription) :
  m_levelNumber(levelNumber), m_levelDescription(levelDescription) {}

void Level::addWave(unique_ptr<EnemyWave> wave){
  m_enemyWaves.push_back(std::move(wave));
}

void Level::start(){
  Time time;
  m_startTime = CapEngine::currentTime();
}

void Level::update(double ms, World* world){
  double elapsedTime = currentTime() - m_startTime;
  auto i = m_enemyWaves.begin();
  while(i != m_enemyWaves.end()){
    if((elapsedTime/1000.0) >= (*i)->startTime){
      // unleash the wave!
      for (auto j : (*i)->enemies){
	unique_ptr<GameObject> pNewEnemyObject = EnemyFactory::getInstance()->makeEnemy(j.first);
	pNewEnemyObject->position.x = j.second;
	pNewEnemyObject->position.y = 0 - (pNewEnemyObject->boundingPolygon().height / 2.0);
	world->addObject(*(pNewEnemyObject.release()));
      }
      i = m_enemyWaves.erase(i);
    }
    else{
      i++;
    }
  }
}

vector<unique_ptr<Level> > parseLevelFile(string filepath){
  XmlParser parser(filepath);
  string xpathExpression = "/levels/level";
  vector<XmlNode> levelNodes = parser.getNodes(xpathExpression);
  vector<unique_ptr<Level> > levels;

  for (auto i : levelNodes){
    int levelNum;
    istringstream(parser.getAttribute(i, "number")) >> levelNum;
    string levelDescription = parser.getAttribute(i, "desc");
    unique_ptr<Level>  pNewLevel(new Level(levelNum, levelDescription));
    
    ostringstream xpath;
    xpath << "//level[@number='" << levelNum << "']/waves/wave";
    vector<XmlNode> waveNodes = parser.getNodes(xpath.str());
    for(auto j : waveNodes){
      int time;
      istringstream(parser.getAttribute(j, "time")) >> time;
      unique_ptr<Level::EnemyWave> pNewWave(new Level::EnemyWave);
      pNewWave->startTime = time;

      ostringstream enemyPath;
      enemyPath << "//level[@number='" << levelNum << "']/waves/wave[@time='" << time << "']/enemy";
      vector<XmlNode> enemyNodes = parser.getNodes(enemyPath.str());
      for (auto k : enemyNodes) {
	string type = parser.getAttribute(k, "type");
	int x_start;
	istringstream(parser.getAttribute(k, "x_start")) >> x_start;
	pNewWave->enemies.push_back(std::make_pair(type, x_start));
      }
      pNewLevel->addWave(std::move(pNewWave));
    }
    levels.push_back(std::move(pNewLevel));
  }
  
  return levels;
}

int Level::getLevelNumber(){
  return m_levelNumber;
}

std::string Level::getLevelDescription(){
  return m_levelDescription;
}
