#ifndef TEXTBUTTON_H
#define TEXTBUTTON_H

#include "CapEngine.h"
#include "button.h"

#include <string>

class TextButton : public Button {

 private:
  TextButton(const TextButton&);
  TextButton& operator=(const TextButton&);

 public:
  TextButton(std::string text, std::string font, int fontSize, CapEngine::Vector position);
  ~TextButton();
  virtual void update();
  virtual void render();
  virtual void setEnabled(bool enabled = true);
  virtual bool isEnabled() const;
  virtual int getWidth() const;
  virtual int getHeight() const;
  virtual void setWidth(int width);
  virtual void setHeight(int height);
  virtual std::string getText() const;
  virtual void setText(const std::string text);
  virtual void setPosition(const CapEngine::Vector position);

 protected:
  std::string m_text;
  std::string m_font;
  int m_fontSize;
  int m_width;
  int m_height;
  bool m_selected;
  bool m_enabled;
  bool m_activated;
  CapEngine::Surface* m_pTextSurfaceInactive;
  CapEngine::Surface* m_pTextSurfaceActive;
  CapEngine::Vector m_position;

};

#endif // TEXTBUTTON_H
