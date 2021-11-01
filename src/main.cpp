#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>

#include <vector>
#include <string>


#include "FontManager.h"
#include "Text.h"
#include "Clock.h"
#include "Sprite.h"


//Constants
#define GAME_TITLE "Game 2048"
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define CELL_SIZE 80
#define CELL_MARGIN 90

#define TABLE_WIDTH (CELL_SIZE +  (CELL_SIZE - CELL_MARGIN) ) * 5
#define TABLE_HEIGHT (CELL_SIZE +  (CELL_SIZE - CELL_MARGIN) ) * 5

#define TABLE_X (SCREEN_WIDTH - TABLE_WIDTH) / 2
#define TABLE_Y (SCREEN_HEIGHT - TABLE_HEIGHT) / 2


#define TABLE_PADDING 10

SDL_Color WindowColor = {250, 247, 238};
SDL_Color TextColor = {175,163,148};
SDL_Color TableColor = {187,173,160};
SDL_Color CellColor = {237,224,200};

bool isRunning = true;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

int Score = 0;
bool PlayerWin = false;
bool PlayerLose = false;

Text winText;
Text pressEnterText;
Text loseText;
Text ScoreText;


struct cell{
    int value;
    SDL_Color back_color;
    SDL_Color text_color;
};



cell table[4][4] = 
{
    {
        {2048, CellColor, TextColor},
        {0, CellColor, TextColor},
        {2, CellColor, TextColor},
        {0, CellColor, TextColor}
    },
    {
        {0, CellColor, TextColor},
        {0, CellColor, TextColor},
        {0, CellColor, TextColor},
        {2, CellColor, TextColor}
    },
    {
        {0, CellColor, TextColor},
        {0, CellColor, TextColor},
        {0, CellColor, TextColor},
        {2, CellColor, TextColor}
    },
    {
        {0, CellColor, TextColor},
        {0, CellColor, TextColor},
        {0, CellColor, TextColor},
        {0, CellColor, TextColor}
    }
};


//Sum all values of table
int SumTable()
{
    int sum = 0;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            sum += table[i][j].value;
        }
    }
    return sum;
}

void UpdateScore()
{
    Score = SumTable();
    //store in ScoreText the "Score: " + score
    std::string txt = "Score: " + std::to_string(Score);
    //  Text(SDL_Renderer* renderer,TTF_Font* font, SDL_Color color, const char* text); 
    ScoreText = Text(renderer, fontManager.GetFont(Fonts::FONT_OPEN_SANS_BOLD), {108,91,77}, txt.c_str());
}


//update color of cellcolor and textcolor dependent on value
//called when player makes a move
void UpdateColor()
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(table[i][j].value == 0)
            {
                table[i][j].back_color = {205,193,180};
                table[i][j].text_color = TextColor;
            }
            else if(table[i][j].value == 2)
            {
                table[i][j].back_color = {237,224,200};
                table[i][j].text_color = {175,163,148};
            }
            else if(table[i][j].value == 4)
            {
                table[i][j].back_color = {237,224,200};
                table[i][j].text_color = {175,163,148};
            }
            else if(table[i][j].value == 8)
            {
                table[i][j].back_color = {242,177,121};
                table[i][j].text_color = {255,255,255};
            }
            else if(table[i][j].value == 16)
            {
                table[i][j].back_color = {245,149,99};
                table[i][j].text_color = {255,255,255};
            }
            else if(table[i][j].value == 32)
            {
                table[i][j].back_color = {246,124,95};
                table[i][j].text_color = {255,255,255};
            }
            else if(table[i][j].value == 64)
            {
                table[i][j].back_color = {246,94,59};
                table[i][j].text_color = {255,255,255};
            }
            else if(table[i][j].value == 128)
            {
                table[i][j].back_color = {237,207,114};
                table[i][j].text_color = {255,255,255};
            }
            else if(table[i][j].value == 256)
            {
                table[i][j].back_color = {241,201,90};
                table[i][j].text_color = {255,255,255};
            }
            else if(table[i][j].value == 512)
            {
                table[i][j].back_color = {228,185,71};
                table[i][j].text_color = {255,255,255};
            }
            else if(table[i][j].value == 1024)
            {
                table[i][j].back_color = {226,180,52};
                table[i][j].text_color = {255,255,255};
            }
            else if(table[i][j].value == 1024)
            {
                table[i][j].back_color = {226,180,52};
                table[i][j].text_color = {255,255,255};
            }
            else if(table[i][j].value == 2048)
            {
                table[i][j].back_color = {231,179,39};
                table[i][j].text_color = {255,255,255};

                if(!PlayerWin)
                {
                    PlayerWin = true;
                    UpdateScore();
                }
            }
        }
    }
}


Text tableText[4][4] = {};

void PopulateTableText()
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            //if value is 0 make it empty text
            if(table[i][j].value == 0)
            {
                 tableText[i][j] = Text();
            }
            else
            {
                 tableText[i][j] = Text(renderer,fontManager.GetFont(FONT_OPEN_SANS_BOLD),table[i][j].text_color,std::to_string(table[i][j].value).c_str());
            }
           
        }
    }
}


//function draw rectangle
void DrawFillRect(int x, int y, int w, int h, SDL_Color color)
{
    SDL_Rect rect = {x,y,w,h};
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);
}



void DrawTable()
{
    //draw the background of the table
    DrawFillRect(TABLE_X- TABLE_PADDING ,TABLE_Y - TABLE_PADDING,TABLE_WIDTH + TABLE_PADDING*2,TABLE_HEIGHT + TABLE_PADDING*2,TableColor);

    //draw the cells
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            //draw each cell
            DrawFillRect(TABLE_X+(j*CELL_MARGIN),TABLE_Y+(i*CELL_MARGIN),  CELL_SIZE,  CELL_SIZE, table[i][j].back_color);

            //draw tabletext
            tableText[i][j].Draw(renderer,TABLE_X + (j * CELL_MARGIN) + CELL_SIZE/2 - tableText[i][j].w/2,TABLE_Y + (i * CELL_MARGIN) + CELL_SIZE/2 - tableText[i][j].h/2 );
        }
    }
}



//function to move all values of table cell to left
void MoveLeft()
{
    for (int i = 0; i < 4; i++)
    {
        for(int y = 0; y < 4 ;y++)
        {
             for(int x = 1; x < 4; x++)
            {
                if(table[y][x-1].value == 0)
                {
                    table[y][x-1].value = table[y][x].value;
                    table[y][x].value = 0;
                }
                else if(table[y][x-1].value == table[y][x].value)
                {
                    table[y][x-1].value += table[y][x].value;;
                    table[y][x].value = 0;
                }
            }
        }
    }
}

//function to move all values of table cell to right
void MoveRight()
{
    for (int i = 0; i < 4; i++)
    {
        for(int y = 0; y < 4 ;y++)
        {
             for(int x = 2; x >= 0; x--)
            {
                if(table[y][x+1].value == 0)
                {
                    table[y][x+1].value = table[y][x].value;
                    table[y][x].value = 0;
                }
                else if(table[y][x+1].value == table[y][x].value)
                {
                    table[y][x+1].value += table[y][x].value;;
                    table[y][x].value = 0;
                }
            }
        }
    }
}

//function to move all values of table cell to up
void MoveUp()
{
    for (int i = 0; i < 4; i++)
    {
        for(int y = 1; y < 4 ;y++)
        {
             for(int x = 0; x < 4; x++)
            {
                if(table[y-1][x].value == 0)
                {
                    table[y-1][x].value = table[y][x].value;
                    table[y][x].value = 0;
                }
                else if(table[y-1][x].value == table[y][x].value)
                {
                    table[y-1][x].value += table[y][x].value;;
                    table[y][x].value = 0;
                }
            }
        }
    }
}

//function to move all values of table cell to down
void MoveDown()
{
     for (int i = 0; i < 4; i++)
    {
        for(int y = 2; y >= 0  ;y--)
        {
             for(int x = 0; x < 4; x++)
            {
                if(table[y+1][x].value == 0)
                {
                    table[y+1][x].value = table[y][x].value;
                    table[y][x].value = 0;
                }
                else if(table[y+1][x].value == table[y][x].value)
                {
                    table[y+1][x].value += table[y][x].value;;
                    table[y][x].value = 0;
                }
            }
        }
    }
}

//function to check if there is any empty cell
bool IsEmptyCell()
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(table[i][j].value == 0)
            {
                return true;
            }
        }
    }
    return false;
}



//generate random number in cell with value 0
void GenerateRandomCell()
{
    int x = rand() % 4;
    int y = rand() % 4;
    while(table[y][x].value != 0)
    {
        x = rand() % 4;
        y = rand() % 4;
    }
    table[y][x].value = 2;
}

//function called after a move
void AfterMove()
{
    GenerateRandomCell();
    UpdateColor();
    PopulateTableText();
    if(!IsEmptyCell())
    {
        PlayerLose = true;
        UpdateScore();
    }
}
void ResetTable()
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            table[i][j].value = 0;
        }
    }
    GenerateRandomCell();
    GenerateRandomCell();
    UpdateColor();
    PopulateTableText();
    UpdateScore();
}
void UserEvents(SDL_Event event)
{
    if(PlayerWin || PlayerLose)
    {
        switch(event.type)
        {
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_RETURN:
                        PlayerWin = false;
                        PlayerLose = false;
                        ResetTable();
                    break;
                }
        }
        return;
    }

    switch(event.type)
    {
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
                case SDLK_UP:
                    MoveUp();
                    AfterMove();
                    break;
                case SDLK_DOWN:
                    MoveDown();
                    AfterMove();
                    break;
                case SDLK_LEFT:
                    MoveLeft();
                    AfterMove();
                    break;
                case SDLK_RIGHT:
                    MoveRight();
                    AfterMove();
                    break;
                default:
                    break;
            }
    }
}


void PrintTable()
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            printf("%d ",table[i][j].value);
        }
        printf("\n");
    }
}



void Events()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            //if mouse is clicked
            case SDL_MOUSEBUTTONDOWN:

                break;
            case SDL_MOUSEBUTTONUP:

                break;

            case SDL_QUIT:
                isRunning = false;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        isRunning = false;
                        break;
                    default:
                        break;
                }
                break;

        }
        UserEvents(event);
    }
}



void FinishScreen()
{
    if(PlayerWin)
    {
        winText.Draw(renderer,TABLE_X + TABLE_WIDTH/2 - (winText.w/2),TABLE_Y);
        ScoreText.Draw(renderer,TABLE_X + TABLE_WIDTH/2 - (ScoreText.w/2),TABLE_Y + winText.h + 10);
        pressEnterText.Draw(renderer,TABLE_X + TABLE_WIDTH/2 - (pressEnterText.w/2),TABLE_Y + winText.h + ScoreText.h + 20);
        
    }
    else if(PlayerLose)
    {
        loseText.Draw(renderer,TABLE_X + TABLE_WIDTH/2 - (loseText.w/2),TABLE_Y);
        ScoreText.Draw(renderer,TABLE_X + TABLE_WIDTH/2 - (ScoreText.w/2),TABLE_Y + winText.h + 10);
        pressEnterText.Draw(renderer,TABLE_X + TABLE_WIDTH/2 - (pressEnterText.w/2),TABLE_Y + winText.h + ScoreText.h + 20);
    }

}




void Render()
{
    //Clear screen
    SDL_SetRenderDrawColor(renderer,WindowColor.r, WindowColor.g, WindowColor.b, WindowColor.a);
    SDL_RenderClear(renderer);

    DrawTable();

    FinishScreen();

    SDL_RenderPresent(renderer);
}

void GameLoop()
{
    PrintTable();
    while (isRunning)
    {
        clock.LimitFps(60);
        //printf("FPS: %i\n", clock.Currentfps);
        Events();
        Render();
    }
}



int main(int argc, char* argv[])
{
    //Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    //Init Tff
    if (TTF_Init() == -1)
    {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        return 1;
    }

    //Create window
    window = SDL_CreateWindow(GAME_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    //Create renderer for window
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        return 1;
    }
    
    //init fontmanager
    fontManager = FontManager();

    UpdateColor();
    PopulateTableText();

    //create wintext         Text(SDL_Renderer* renderer,TTF_Font* font, SDL_Color color, const char* text); 
    winText = Text(renderer, fontManager.GetFont(Fonts::FONT_OPEN_SANS_BOLD), {108,91,77}, "You Win");
    loseText = Text(renderer, fontManager.GetFont(Fonts::FONT_OPEN_SANS_BOLD), {108,91,77}, "You Lose");
    pressEnterText = Text(renderer, fontManager.GetFont(Fonts::FONT_OPEN_SANS_BOLD), {108,91,77}, "Enter to try again");
    UpdateScore();

    //SetIcon
    SDL_Surface* icon = IMG_Load("res/icon.png");
    SDL_SetWindowIcon(window, icon);
    SDL_FreeSurface(icon);

    GameLoop();

    //free text
    winText.Free();
    loseText.Free();
    pressEnterText.Free();
    ScoreText.Free();


    //free all text table
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            tableText[i][j].Free();
        }
    }

    //free font manager
    fontManager.Free();

    //free window
    SDL_DestroyWindow(window);
    //free renderer
    SDL_DestroyRenderer(renderer);

    //Quit SDL subsystems
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
    return 0;
}