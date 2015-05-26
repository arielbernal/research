#ifndef IMAGESHOW_H
#define IMAGESHOW_H

#include <iostream>
#include <opencv2/opencv.hpp>
#include <map>
#include <ocvTools/imagedialog.h>

namespace glp {

class ImageShow {
public:
  static ImageShow &getInstance() {
    static ImageShow instance;
    return instance;
  }

  void show(const std::string &Name, cv::Mat &Image) {
    Iterator I = Dialogs.find(Name);
    if (I == Dialogs.end()) {
      ImageDialog *pDialog = new ImageDialog(Name, Image);
      Dialogs[Name] = pDialog;
      pDialog->show();
    }
  }

  void show(const std::string &Name, cv::Mat &Image,
            std::function<void()> Func) {
    Iterator I = Dialogs.find(Name);
    if (I == Dialogs.end()) {
      ImageDialog *pDialog = new ImageDialog(Name, Image);
      Dialogs[Name] = pDialog;
      pDialog->setCallbackRenderer(Func);
      pDialog->show();
    }
  }

  void remove(const std::string &Name) {
    Iterator I = Dialogs.find(Name);
    if (I != Dialogs.end()) {
      Dialogs.erase(I);
    }
  }

  void closeAll() {
    std::cout << "Close All ImageDialogs" << std::endl;
    for (auto &e : Dialogs) {
      e.second->close();
    }
  }

  void enableFPS(const std::string &Name, bool enabled = true) {
    Iterator I = Dialogs.find(Name);
    if (I != Dialogs.end())
      I->second->enableFPS(enabled);
  }

private:
  typedef std::map<std::string, ImageDialog *>::iterator Iterator;
  ImageShow() {}
  ImageShow(const ImageShow &) = delete;
  void operator=(const ImageShow &) = delete;

  std::map<std::string, ImageDialog *> Dialogs;
};

inline void ShowImage(const std::string &Name, cv::Mat &Image) {
  ImageShow::getInstance().show(Name, Image);
}

inline void ShowImage(const std::string &Name, cv::Mat &Image,
                      std::function<void()> Func) {
  ImageShow::getInstance().show(Name, Image, Func);
}

inline void RemoveImage(const std::string &Name) {
  ImageShow::getInstance().remove(Name);
}

inline void CloseAllImages() { ImageShow::getInstance().closeAll(); }

inline void EnableImageFPS(const std::string &Name, bool enabled = true) {
  ImageShow::getInstance().enableFPS(Name, enabled);
}

} // namespace glp

#endif // IMAGESHOW_H
