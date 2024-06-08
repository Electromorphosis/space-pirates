//
// Created by mechlon on 06.06.24.
//

#ifndef SPACE_PIRATES_GLOBALSETTINGS_H
#define SPACE_PIRATES_GLOBALSETTINGS_H

class GlobalSettings
{
public:
    static GlobalSettings& GetInstance();

    void SetWindowWidth(int newWidth);
    void SetWindowHeight(int newWidth);
    int GetWindowWidth(int newWidth);
    int GetWindowHeight(int newWidth);

private:
    static GlobalSettings instance_;
    GlobalSettings() = default;

    int WINDOW_WIDTH = 1000;
    int WINDOW_HEIGHT = 1000;

};


#endif //SPACE_PIRATES_GLOBALSETTINGS_H
