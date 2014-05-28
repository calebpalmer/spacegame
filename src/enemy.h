#ifndef ENEMY_H
#define ENEMY_H


class Enemy{
 public:
  Enemy(std::string imagePath, std::string gunType);
 private:
  std::string m_imagePath;
  std::string m_gunType;
};

#endif
