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
    int GetWindowWidth();
    int GetWindowHeight();
    Uint32 GetFramerate();

private:
    static GlobalSettings instance_;
    GlobalSettings() = default;

    int WINDOW_WIDTH = 1000;
    int WINDOW_HEIGHT = 1000;
    const Uint32 MS_PER_FRAME = 1000 / 60; // Limit FPS do 60
};


#endif //SPACE_PIRATES_GLOBALSETTINGS_H
