#include "FontManager.h"

void FontManager::AddFont(const char* fileName, int size, Fonts font)
{
    if (FileExist(fileName))
    {
        TTF_Font* font = TTF_OpenFont(fileName, size);
        fonts.push_back(font);
    }
    else
    {
        printf("Font file not found: %s\n", fileName);
    }
}

FontManager::FontManager()
{
    //Add all fonts using add font AddFont(const char* fileName, int size, Fonts font)
    AddFont("res/fonts/OpenSans-Light.ttf", 16, FONT_OPEN_SANS_LIGHT);
    AddFont("res/fonts/OpenSans-Regular.ttf", 16, FONT_OPEN_SANS_REGULAR);
    AddFont("res/fonts/OpenSans-Semibold.ttf", 16, FONT_OPEN_SANS_SEMIBOLD);
    AddFont("res/fonts/OpenSans-Bold.ttf", 32, FONT_OPEN_SANS_BOLD);
    AddFont("res/fonts/OpenSans-Italic.ttf", 16, FONT_OPEN_SANS_ITALIC);
    AddFont("res/fonts/OpenSans-BoldItalic.ttf", 16, FONT_OPEN_SANS_BOLD_ITALIC);
}

 TTF_Font* FontManager::GetFont(Fonts font)
 {
     return fonts[font];
 }