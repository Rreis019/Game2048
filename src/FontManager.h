#include <vector>
#include <SDL2/SDL_ttf.h>

#include <fstream>

//check if file exist
static bool FileExist(const char* fileName)
{
    std::ifstream infile(fileName);
    return infile.good();
}

enum Fonts
{
    FONT_OPEN_SANS_LIGHT,
    FONT_OPEN_SANS_REGULAR,
    FONT_OPEN_SANS_SEMIBOLD,
    FONT_OPEN_SANS_BOLD,
    FONT_OPEN_SANS_ITALIC,
    FONT_OPEN_SANS_BOLD_ITALIC
};

class FontManager
{
public:
    
    FontManager();

    //add font to vector
    void AddFont(const char* fileName, int size, Fonts font);

    //get font from vector using enum
    TTF_Font* GetFont(Fonts font);

    //free all fonts
    void Free()
    {
        for (int i = 0; i < fonts.size(); i++)
        {
            TTF_CloseFont(fonts[i]);
        }
    }
private:
    std::vector<TTF_Font*> fonts;
};

static FontManager fontManager;