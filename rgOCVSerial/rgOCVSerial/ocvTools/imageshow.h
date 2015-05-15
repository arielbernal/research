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

  static void Show(const std::string &Name, cv::Mat &Image) {
    getInstance().show(Name, Image);
  }

  static void Remove(const std::string &Name) { getInstance().remove(Name); }

  static void CloseAll() { getInstance().closeAll(); }

protected:
  void show(const std::string &Name, cv::Mat &Image) {
    Iterator I = Dialogs.find(Name);
    if (I == Dialogs.end()) {
      ImageDialog *pDialog = new ImageDialog(Name, Image);
      Dialogs[Name] = pDialog;
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

private:
  typedef std::map<std::string, ImageDialog *>::iterator Iterator;
  ImageShow() {}
  ImageShow(const ImageShow &) = delete;
  void operator=(const ImageShow &) = delete;

  std::map<std::string, ImageDialog *> Dialogs;
};

} // namespace glp

#endif // IMAGESHOW_H
