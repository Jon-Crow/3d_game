#ifndef SETTINGS_H
#define SETTINGS_H

void loadSettings();
void saveSettings();
void setScreenSize(int w, int h);
int getScreenWidth();
int getScreenHeight();
void setRenderDivison(int rd);
int getRenderDivison();

#endif // SETTINGS_H
