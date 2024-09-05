#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfx.h>
#include <string>
#include <SDL2/SDL_mixer.h>
#include <vector>
#include <conio.h>
#include <fstream>
#include <time.h>
#include <ctime>

using namespace std;

string password = "sut";

//USERS INITIALIZATION----------------------------------------------------------------------

int users_count = 0;
int array_count;

string users_name[13];
int users_score[13];


//USERS INITIALIZATION----------------------------------------------------------------------

//----------------------------------------------------------------------

string users_path = "users.txt";
string setting_path = "setting.txt";
string scores_path = "scores.txt";

long long int final_score = 0;
int score_per_ball = 3;
int shoot_count=0;
int standard_radius = 40;
int time_limit = 60; //TIME LIMIT FOR TIME MODE

//ENV INITIALIZATION----------------------------------------------------------------------

int theme = 1;
int volume = 50;
int volume_saved  = volume;
int effect_volume = 50;
int effect_volume_saved = effect_volume;
int music1_int = 0;
int music2_int = 1;
int music1_final = music1_int;
int music2_final = music2_int;
int trajectory_width = 3;

//ENV INITIALIZATION----------------------------------------------------------------------

long double linear_velocity = 30; //LINEAR VELOCITY OF THE SHOOTING BALL

//----------------------------------------------------------------------

//COLORS----------------------------------------------------------------------

SDL_Color sdl_white = {255, 255, 255};
SDL_Color sdl_black = {0, 0, 0};
SDL_Color sdl_blue = {0, 0, 255};
SDL_Color sdl_green = {0, 255, 0};
SDL_Color sdl_red = {255, 0, 0};
SDL_Color sdl_purple = {160, 32, 240};
SDL_Color sdl_cyan = {0, 100, 100};
SDL_Color sdl_yellow = {255, 255, 0};
SDL_Color sdl_orange = {255, 165, 0};

struct color {
    int r;
    int g;
    int b;
};

color blue = {0, 0, 255};
color red = {255, 0, 0};
color green = {0, 255, 0};
color white = {255, 255, 255};
color black = {0, 0, 0};
color yellow = {255, 255, 0};
color purple = {160, 32, 240};
color cyan = {0, 100, 100};
color orange = {255, 165, 0};

//COLORS----------------------------------------------------------------------

//BASIC SDL FUNCTIONS----------------------------------------------------------------------

void rect(SDL_Renderer *Renderer, int x,int y,int w,int h,int R, int G, int B, int fill_boolian );
void ellipse(SDL_Renderer *Renderer, int x, int y, int Radius1, int Radius2, int R, int G, int B, int fill_boolian);
void display_text(SDL_Renderer * renderer, int x, int y, int size, int h, int w, string text, int font_int, int color);
string text_box(SDL_Renderer * renderer, int font_int, int size, int x, int y, int w, int h, int color, SDL_Texture * login_texture);

//BASIC SDL FUNCTIONS

//MENU FUNCTIONS----------------------------------------------------------------------

int invisible_button(SDL_Renderer * renderer, int x, int y, int w, int h, bool &i, bool j, int r, int g, int b);
int menu(SDL_Renderer *renderer, SDL_Texture * menu_texture);
int score(SDL_Renderer * renderer, SDL_Texture * scores_texture);
int setting_menu(SDL_Renderer * renderer, SDL_Texture * settings_texture, Mix_Music * music1, Mix_Music * music2, int &theme, Mix_Chunk * hit_soundeffect);
int login(SDL_Renderer * renderer, SDL_Texture * login_texture);
int menu_functions(SDL_Renderer * m_renderer, SDL_Texture * menu_texture, SDL_Texture * scores_texture, SDL_Texture * settings_texture, SDL_Window * m_window, Mix_Music * music1, Mix_Music * music2, SDL_Texture * login_texture, SDL_Texture * theme1_texture, SDL_Texture * theme2_texture, SDL_Texture * pause_menu_texture, Mix_Music * gameover_music, SDL_Texture * gameover_texture, Mix_Chunk * hit_soundeffect, SDL_Texture * win_texture, Mix_Music * win_music);
int pause_menu (SDL_Renderer * renderer, SDL_Texture * pause_menu_texture, Mix_Music * music1, Mix_Music * music2, Mix_Chunk * hit_soundeffect);

//MENU FUNCTIONS----------------------------------------------------------------------

//GAME FUNCTIONS----------------------------------------------------------------------

int game_infinite(SDL_Renderer * renderer, SDL_Texture * theme1_texture, int theme, SDL_Texture * pause_menu_texture, Mix_Music * music1, Mix_Music * music2, Mix_Music * gameover_music, SDL_Texture * gameover_texture, Mix_Chunk * hit_soundeffect);
int game_normal(SDL_Renderer * renderer, SDL_Texture * theme1_texture, int theme, SDL_Texture * pause_menu_texture, Mix_Music * music1, Mix_Music * music2, Mix_Music * gameover_music, SDL_Texture * gameover_texture, Mix_Chunk * hit_soundeffect, SDL_Texture * win_texture, Mix_Music * win_music);
int game_time(SDL_Renderer * renderer, SDL_Texture * theme1_texture, int theme, SDL_Texture * pause_menu_texture, Mix_Music * music1, Mix_Music * music2, Mix_Music * gameover_music, SDL_Texture * gameover_texture, Mix_Chunk * hit_soundeffect, SDL_Texture * win_texture, Mix_Music * win_music);

int gamewin(SDL_Renderer *renderer, SDL_Texture * win_texture, Mix_Music * win_music, int time);
int gameover(SDL_Renderer *renderer, SDL_Texture * gameover_texture, Mix_Music * gameover_music, int time);

void ball_chain(int i, int j, int balls[11][11], int ball_color);
bool color_in_balls(int color_ball, int balls[11][11]);
int balls_to_graphics(SDL_Renderer * renderer, int balls[11][11], int x_ball, int y_ball, int color_ball);
int random_number();
int coin_flip();
void randomize(int i, int j, int balls[11][11], int color);
int linear_randomize(int balls[11][11], int color, int j);
int shift_balls(int balls[11][11], bool & game_lost);
int is_connected(int balls[11][11], bool isolated[11][11], int i, int j);
int drop_isolated(int balls[11][11]);
int random_shooting_ball_color();
bool allzero(int balls[11][11]);
int trajectory(SDL_Renderer * renderer, int x_m, int y_m, int x_cannon, int y_cannon);
int pause_menu (SDL_Renderer * renderer, SDL_Texture * pause_menu_texture, Mix_Music * music1, Mix_Music * music2, Mix_Chunk * hit_soundeffect);

//GAME FUNCTIONS----------------------------------------------------------------------


int main( int argc, char * argv[] ) {

    //SETTINGS LOADING----------------------------------------------------------------------

    fstream setting;
    setting.open(setting_path.c_str(), ios::in);
    if (setting.good()) {
        setting>>theme>>volume>>effect_volume>>volume_saved>>effect_volume_saved>>users_count>>music1_int>>music2_int;
    }
    setting.close();

    //SETTINGS LOADING----------------------------------------------------------------------

    //USERS INITIALIZATION----------------------------------------------------------------------

    vector<string> user_name;
    vector<int> users_score;

    //USERS INITIALIZATION----------------------------------------------------------------------


    //AUDIO LOADING----------------------------------------------------------------------

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    //MUSIC
    Mix_Music *music1 = Mix_LoadMUS("music1.mp3");
    Mix_Music *music2 = Mix_LoadMUS("music2.mp3");
    Mix_Music *preview_music = Mix_LoadMUS("preview.mp3");
    Mix_Music *gameover_music = Mix_LoadMUS("gameover.mp3");
    Mix_Music *win_music = Mix_LoadMUS("win_soundeffect.mp3");

    //SOUND EFFECT
    Mix_Chunk *hit_soundeffect = Mix_LoadWAV("hit.wav");

    //AUDIO LOADING----------------------------------------------------------------------


    //PREVIEW MUSIC----------------------------------------------------------------------

    Mix_VolumeMusic(volume);
    Mix_PlayMusic(preview_music, -1);

    //PREVIEW MUSIC----------------------------------------------------------------------

    if (music1_int) {

        Mix_PauseMusic();
        Mix_PlayMusic(music1, -1);

    }

    else if (music2_int) {

        Mix_PauseMusic();
        Mix_PlayMusic(music2, -1);

    }

    music1_int = 0;
    music2_int = 0;

    //WINDOW INITIALIZATION----------------------------------------------------------------------

    int H = 1000;
    int W = 1000;
    Uint32 SDL_flags = SDL_INIT_VIDEO | SDL_INIT_TIMER ;
    Uint32 WND_flags = SDL_WINDOW_SHOWN;//| SDL_WINDOW_FULLSCREEN_DESKTOP;//SDL_WINDOW_BORDERLESS ;
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    SDL_Init( SDL_flags );
    SDL_CreateWindowAndRenderer( W, H, WND_flags, &m_window, &m_renderer );
    SDL_RaiseWindow(m_window);
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);

    //WINDOW INITIALIZATION----------------------------------------------------------------------


    //TEXTURE LOADING----------------------------------------------------------------------

    //MENU TEXTURES
    SDL_Texture * menu_texture = IMG_LoadTexture(m_renderer, "menu.png");
    SDL_Texture * scores_texture = IMG_LoadTexture(m_renderer, "scores.png");
    SDL_Texture * settings_texture = IMG_LoadTexture(m_renderer, "setting.png");
    SDL_Texture * pause_menu_texture = IMG_LoadTexture(m_renderer, "pause.png");
    SDL_Texture * login_texture = IMG_LoadTexture(m_renderer, "login.png");

    //THEME TEXTURES
    SDL_Texture * theme1_texture = IMG_LoadTexture(m_renderer, "jungle_theme.png");
    SDL_Texture * theme2_texture = IMG_LoadTexture(m_renderer, "space_theme.png");

    //OTHERS
    SDL_Texture * preview_texture = IMG_LoadTexture(m_renderer, "preview_image.png");
    SDL_Texture * gameover_texture = IMG_LoadTexture(m_renderer, "gameover_texture.png");
    SDL_Texture * win_texture = IMG_LoadTexture(m_renderer, "win_texture.png");

    //TEXTURE LOADING----------------------------------------------------------------------

    //PREVIEW IMAGE----------------------------------------------------------------------

    SDL_RenderCopy(m_renderer, preview_texture, NULL, NULL);
    SDL_RenderPresent(m_renderer);
    delay(4000);

    //PREVIEW IMAGE----------------------------------------------------------------------

    int state;
    state = menu_functions(m_renderer, menu_texture, scores_texture, settings_texture, m_window, music1, music2, login_texture, theme1_texture, theme2_texture, pause_menu_texture, gameover_music, gameover_texture, hit_soundeffect, win_texture, win_music);
    //WHILE IN THE MENU
    while (state != 0 && state != -1) {
        state = menu_functions(m_renderer, menu_texture, scores_texture, settings_texture, m_window, music1, music2, login_texture, theme1_texture, theme2_texture, pause_menu_texture, gameover_music, gameover_texture, hit_soundeffect, win_texture, win_music);
    }

    //SETTINGS LOADING----------------------------------------------------------------------

    setting.open(setting_path.c_str(), ios::out);
    if (setting.good()) {
        setting<<theme<<" "<<volume<<" "<<effect_volume<<" "<<volume_saved<<" "<<effect_volume_saved<<" "<<users_count<<" "<<music1_final<<" "<<music2_final;
    }
    setting.close();
    array_count = users_count;

    //SETTINGS LOADING----------------------------------------------------------------------

    //CREDITS----------------------------------------------------------------------

    textbackground(0);
    clrscr();
    cout<<endl;
    textcolor(0);
    textbackground(14);
    cout<<"\t CREDITS:"<<endl;
    textbackground(0);
    textcolor(2);
    textbackground(2);
    cout<<"\t";
    textbackground(0);
    cout<<" CREATED BY AMIRREZA MIRJALILY & MOBIN BEHRAVAN"<<endl;
    textcolor(5);
    textbackground(5);
    cout<<"\t";
    textbackground(0);
    cout<<" SHARIF UNIVERSITY OF TECHNOLOGY, EE DEPARTMENT"<<endl;
    textbackground(9);
    cout<<"\t";
    textbackground(0);
    textcolor(9);
    cout<<" JAN 2024"<<endl;

    //CREDITS----------------------------------------------------------------------

    return 0;
}

//BASIC SDL FUNCTIONS----------------------------------------------------------------------

void display_centered_text(SDL_Renderer * renderer, int x, int y, int size, int h, string text, int font_int, int color) {

    TTF_Init();

    TTF_Font * font;

    if (font_int == 1) {
        font = TTF_OpenFont("Arial.ttf", size);
    }
    else if (font_int == 2) {
        font = TTF_OpenFont("fancyfont.ttf", size);
    }

    int w = text.length() * size / 2;

    SDL_Rect text_rect = {x-w/2, y, w, h};
    SDL_Surface * text_surface;
    if (color == 1) {
        text_surface = TTF_RenderText_Solid(font, text.c_str(), sdl_black);
    }
    else if (color == 2) {
        text_surface = TTF_RenderText_Solid(font, text.c_str(), sdl_red);
    }
    else if (color == 3) {
        text_surface = TTF_RenderText_Solid(font, text.c_str(), sdl_green);
    }
    else if (color == 4) {
        text_surface = TTF_RenderText_Solid(font, text.c_str(), sdl_purple);
    }
    else if (color == 5) {
        text_surface = TTF_RenderText_Solid(font, text.c_str(), sdl_white);
    }
    else if (color == 6) {
        text_surface = TTF_RenderText_Solid(font, text.c_str(), sdl_yellow);
    }

    TTF_Quit();

    SDL_Texture * text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_RenderCopy(renderer, text_texture, NULL, &text_rect);

}

void display_text(SDL_Renderer * renderer, int x, int y, int size, int h, int w, string text, int font_int, int color) {

    TTF_Init();

    TTF_Font * font;

    if (font_int == 1) {
        font = TTF_OpenFont("Arial.ttf", size);
    }
    else if (font_int == 2) {
        font = TTF_OpenFont("fancyfont.ttf", size);
    }

    SDL_Rect text_rect = {x, y, w, h};
    SDL_Surface * text_surface;
    if (color == 1) {
        text_surface = TTF_RenderText_Solid(font, text.c_str(), sdl_black);
    }
    else if (color == 2) {
        text_surface = TTF_RenderText_Solid(font, text.c_str(), sdl_red);
    }
    else if (color == 3) {
        text_surface = TTF_RenderText_Solid(font, text.c_str(), sdl_green);
    }
    else if (color == 4) {
        text_surface = TTF_RenderText_Solid(font, text.c_str(), sdl_purple);
    }
    else if (color == 5) {
        text_surface = TTF_RenderText_Solid(font, text.c_str(), sdl_white);
    }

    TTF_Quit();

    SDL_Texture * text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_RenderCopy(renderer, text_texture, NULL, &text_rect);

}

void display_text_R(SDL_Renderer * renderer, int x, int y, int size, int h, int w, string text, int font_int, int color) {

    TTF_Init();

    TTF_Font * font;

    if (font_int == 1) {
        font = TTF_OpenFont("Arial.ttf", size);
    }
    else if (font_int == 2) {
        font = TTF_OpenFont("fancyfont.ttf", size);
    }

    x = x - w;

    SDL_Rect text_rect = {x, y, w, h};
    SDL_Surface * text_surface;
    if (color == 1) {
        text_surface = TTF_RenderText_Solid(font, text.c_str(), sdl_black);
    }
    else if (color == 2) {
        text_surface = TTF_RenderText_Solid(font, text.c_str(), sdl_red);
    }
    else if (color == 3) {
        text_surface = TTF_RenderText_Solid(font, text.c_str(), sdl_green);
    }
    else if (color == 4) {
        text_surface = TTF_RenderText_Solid(font, text.c_str(), sdl_purple);
    }
    else if (color == 5) {
        text_surface = TTF_RenderText_Solid(font, text.c_str(), sdl_white);
    }

    TTF_Quit();

    SDL_Texture * text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_RenderCopy(renderer, text_texture, NULL, &text_rect);

}

string text_box(SDL_Renderer * renderer, int font_int, int size, int x, int y, int w, int h, int color, SDL_Texture * login_texture) {

    bool quit = false, caps_lock=false;
    char ch;
    string name = "";

    TTF_Init();

    TTF_Font * font;
    if (font_int == 1) {
        font = TTF_OpenFont("Arial.ttf", size);
    }
    else if (font_int == 2) {
        font = TTF_OpenFont("fancyfont.ttf", size);
    }

    SDL_Rect textbox_rect = {x, y, w, h};
    SDL_Event * event = new SDL_Event();

    SDL_RenderCopy(renderer, login_texture, NULL, NULL);

    while (!quit)
    {
        int wp = name.length() * (size/2);
        if (wp > w) {
            wp = w;
        }
        int xp = 500 - wp/2;
        rect(renderer, x, y, w, h, 255, 0, 12, 1);
        display_text(renderer,xp, y, size, h, wp, name, font_int, color);

        if(SDL_PollEvent(event))
        {
            if(event -> type == SDL_KEYUP)
            {
                switch(event->key.keysym.sym)
                {
                    case SDLK_SPACE:
                        quit = true;
                        break;
                    case SDLK_CAPSLOCK:
                        ch=0;
                        if(!caps_lock)
                            caps_lock = true;
                        else
                            caps_lock = false;
                        break;
                    case SDLK_BACKSPACE:
                        ch = 0;
                        if(name.length()!=0)
                        {
                            name = name.substr(0,name.length()-1);
                        }

                        break;
                    default :
                        if(event->key.keysym.sym != SDLK_UP && event->key.keysym.sym != SDLK_DOWN && event->key.keysym.sym != SDLK_LEFT && event->key.keysym.sym != SDLK_RIGHT)
                            ch = event->key.keysym.sym;
                        break;
                }
                if((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') && name.length()<25 && !quit)
                {
                    if(caps_lock )
                        name+=ch + 'A' - 'a';
                    else
                        name+=ch ;
                }
            }
        }
        SDL_RenderPresent(renderer);
    }

    TTF_Quit();

    return name;

}

void rect(SDL_Renderer *Renderer, int x,int y,int w,int h,int R, int G, int B, int fill_boolian ) {
    SDL_Rect rectangle ;
    rectangle.x = x;
    rectangle.y = y;
    rectangle.w = w;
    rectangle.h = h;
    SDL_SetRenderDrawColor(Renderer, R, G, B, 10);
    if (fill_boolian==1) {
        SDL_RenderFillRect(Renderer, &rectangle); }
    SDL_RenderDrawRect(Renderer, &rectangle);
}

void ellipse(SDL_Renderer *Renderer, int x, int y, int Radius1, int Radius2, int R, int G, int B, int fill_boolian) {
    if(fill_boolian==1) {
        filledEllipseRGBA(Renderer,x,y,Radius1,Radius2,R,G,B,255); }
    if(fill_boolian==0) {
        ellipseRGBA(Renderer,x,y,Radius1,Radius2,R,G,B,255); }
}

int invisible_button(SDL_Renderer * renderer, int x, int y, int w, int h, bool &i, bool j, int r, int g, int b) {
    SDL_Event * event = new SDL_Event();
    int x_m, y_m;
    if (SDL_PollEvent(event)) {
        if (event -> type != SDL_KEYDOWN) {
            x_m = event->button.x;
            y_m = event->button.y;
            if (event -> type == SDL_MOUSEBUTTONDOWN) {
                if (x_m >= x && x_m <= x + w && y_m >= y && y_m <= y + h) {
                    if (j) {
                        rect(renderer, x, y, w, h, r, g, b, 1);
                        SDL_RenderPresent(renderer);
                        SDL_Delay(100);
                        SDL_RenderClear(renderer);
                    }
                    i = true;
                    return 0;
                }
                else {
                    return 0;
                }
            }
            else {
                return 0;
            }
        }
        else {
            return 0;
        }
    }
    else {
        return 0;
    }
}

//BASIC SDL FUNCTIONS----------------------------------------------------------------------

int menu(SDL_Renderer *renderer, SDL_Texture * menu_texture) {

    //TEXTURE LOADING----------------------------------------------------------------------

    SDL_RenderCopy(renderer, menu_texture, NULL, NULL);
    SDL_RenderPresent(renderer);

    //TEXTURE LOADING----------------------------------------------------------------------

    bool start=false, setting=false, scores=false, game_exit = false;
    int x_m, y_m;

    SDL_Event * event = new SDL_Event();

    while (!start && !scores && !setting && !game_exit) {
        SDL_GetMouseState(&x_m, &y_m);

        if (x_m >= 133 && x_m <= 133 + 300 && y_m >= 700 && y_m <= 700 + 200) {
            if (SDL_PollEvent(event)) {
                if (event -> type == SDL_MOUSEBUTTONDOWN) {
                    rect(renderer, 133, 700, 300, 200, yellow.r, yellow.g, yellow.b, 1);
                    SDL_RenderPresent(renderer);
                    SDL_Delay(100);
                    scores = true;
                    break;
                }
                else {
                    continue;
                }
            }
            else {
                continue;
            }
        }
        if (x_m >= 566 && x_m <= 566 + 300 && y_m >= 700 && y_m <= 700 + 200) {
            if (SDL_PollEvent(event)) {
                if (event -> type == SDL_MOUSEBUTTONDOWN) {
                    rect(renderer, 566, 700, 300, 200, purple.r, purple.g, purple.b, 1);
                    SDL_RenderPresent(renderer);
                    SDL_Delay(100);
                    setting = true;
                    break;
                }
                else {
                    continue;
                }
            }
            else {
                continue;
            }
        }
        if (x_m >= 932 && x_m <= 932 + 56 && y_m >= 15 && y_m <= 15 + 55) {
            if (SDL_PollEvent(event)) {
                if (event -> type == SDL_MOUSEBUTTONDOWN) {
                    //rect(renderer, 932, 15, 56, 55, white.r, white.g, white.b, 1);
                    ellipse(renderer, 932 + 28, 15 + 28, 28, 28, red.r, red.g, red.b, 1);
                    SDL_RenderPresent(renderer);
                    SDL_Delay(100);
                    game_exit = true;
                    break;
                }
                else {
                    continue;
                }
            }
            else {
                continue;
            }
        }
        invisible_button(renderer, 350, 400, 300, 200, start, true, green.r, green.g, green.b);

    }
    if (start) {
        return 1;
    }
    else if (scores) {
        return 2;
    }
    else if (setting) {
        return 3;
    }
    else if (game_exit) {
        return -1;
    }
}

int score(SDL_Renderer * renderer, SDL_Texture * scores_texture) {
    bool menu_enter = false;

    //TEXTURE LOADING----------------------------------------------------------------------

    SDL_RenderCopy(renderer, scores_texture, NULL, NULL);
    SDL_RenderPresent(renderer);

    //TEXTURE LOADING----------------------------------------------------------------------

    //DATA LOADING----------------------------------------------------------------------

    fstream scores_file;
    scores_file.open(scores_path.c_str(), ios::in);

    int user_score;
    int x = 0;

    while(scores_file.good()) {

        scores_file>>user_score;
        users_score[x] = user_score;
        x++;

    }

    scores_file.close();

    fstream users_file;
    users_file.open(users_path.c_str(), ios::in);

    string user_name;
    x = 0;

    while(users_file.good()) {

        users_file>>user_name;
        users_name[x] = user_name;
        x++;

    }

    users_file.close();

    for (int j = users_count-1; j>=0; j--) {
        for (int i=0; i<j; i++) {
            if (users_score[i] < users_score[i+1]) {
                swap(users_score[i], users_score[i+1]);
                swap(users_name[i], users_name[i+1]);
            }
        }
    }

    int n;
    if (users_count > 10) {
        n = 10;
    }
    else {
        n = users_count;
    }

    thickLineRGBA(renderer, 500, 340, 500, 850, 3, purple.r, purple.g, purple.b, 255);

    int w;
    int x_name = 30, x_score = 970;
    int y;
    string name;
    string score;

    for (int i=0; i<n; i++) {

        y = ((i+1) * 20) + (i*30) + 16 + 318;
        name = users_name[i];
        int x_name_2 = x_name + name.length() * 25 / 2;

        if (i == 0) {
            display_centered_text(renderer,x_name_2, y, 50, 50, name, 1, 6);
        }
        else if (i == 1) {
            display_centered_text(renderer,x_name_2, y, 50, 50, name, 1, 4);
        }
        else if (i == 2) {
            display_centered_text(renderer,x_name_2, y, 50, 50, name, 1, 3);
        }
        else {
            display_centered_text(renderer,x_name_2, y, 50, 50, name, 1, 1);
        }


        int score_int = users_score[i];
        score = to_string(score_int);
        int x_score_2 = x_score - score.length() * 25 / 2;

        if (i == 0) {
            display_centered_text(renderer, x_score_2, y, 50, 50, score, 1, 6);
        }
        else if (i == 1) {
            display_centered_text(renderer, x_score_2, y, 50, 50, score, 1, 4);
        }
        else if (i == 2) {
            display_centered_text(renderer, x_score_2, y, 50, 50, score, 1, 3);
        }
        else {
            display_centered_text(renderer, x_score_2, y, 50, 50, score, 1, 1);
        }

    }

    //DATA LOADING----------------------------------------------------------------------

    while (!menu_enter) {
        invisible_button(renderer, 30, 875, 191, 88, menu_enter, true, green.r, green.g, green.b);
        SDL_RenderPresent(renderer);
    }
    return 0;
}

int setting_menu(SDL_Renderer * renderer, SDL_Texture * settings_texture, Mix_Music * music1, Mix_Music * music2, int &theme, Mix_Chunk * hit_soundeffect) {

    bool music_mute = false, music_unmute = false, music_volume_up=false, music_volume_down=false, theme1 = false, theme2 = false;
    bool menu_enter = false;
    static bool effect = false;
    int x_m, y_m;

    //TEXTURE LOADING----------------------------------------------------------------------

    SDL_RenderCopy(renderer, settings_texture, NULL, NULL);
    SDL_RenderPresent(renderer);

    //TEXTURE LOADING----------------------------------------------------------------------

    SDL_Event * event = new SDL_Event();

    while (!menu_enter) {

        SDL_GetMouseState(&x_m, &y_m);

        //EFFECT / MUSIC INDICATOR----------------------------------------------------------------------

        if (effect) {
            rect(renderer, 327, 384, 27, 27, red.r, red.g, red.b, 1);
            SDL_RenderPresent(renderer);
        }

        else {
            rect(renderer, 327, 384, 27, 27, white.r, white.g, white.b, 1);
            SDL_RenderPresent(renderer);
        }

        //EFFECT / MUSIC INDICATOR----------------------------------------------------------------------

        //BUTTONS----------------------------------------------------------------------

        if (x_m >= 326 && x_m <= 326 + 30 && y_m >= 380 && y_m <= 380 + 30) {
            if (SDL_PollEvent(event)) {
                if (event -> type == SDL_MOUSEBUTTONDOWN) {
                    if (effect) {
                        effect = false;
                    }
                    else {
                        effect = true;
                    }
                }
                else {
                    continue;
                }
            }
            else {
                continue;
            }
        }
        //invisible_button(renderer, 30, 850, 191, 113, menu_enter, true);
        if (x_m >= 30 && x_m <= 30 + 191 && y_m >= 850 && y_m <= 850 + 113) {
            if (SDL_PollEvent(event)) {
                if (event -> type == SDL_MOUSEBUTTONDOWN) {
                    rect(renderer, 30, 875, 191, 88, green.r, green.g, green.b, 1);
                    SDL_RenderPresent(renderer);
                    SDL_Delay(100);
                    break;
                }
                else {
                    continue;
                }
            }
            else {
                continue;
            }
        }
        //invisible_button(renderer, 89, 696, 155, 89, music1_bool, true);
        if (x_m >= 89 && x_m <= 89 + 155 && y_m >= 696 && y_m <= 696 + 89) {
            if (SDL_PollEvent(event)) {
                if (event -> type == SDL_MOUSEBUTTONDOWN) {
                    rect(renderer, 89, 696, 155, 89, orange.r, orange.g, orange.b, 1);
                    SDL_RenderPresent(renderer);
                    SDL_Delay(100);
                    music1_int = 1;
                }
                else {
                    continue;
                }
            }
            else {
                continue;
            }
        }
        //invisible_button(renderer, 274, 697, 155, 89, music2_bool, true);
        if (x_m >= 274 && x_m <= 274 + 155 && y_m >= 697 && y_m <= 697 + 89) {
            if (SDL_PollEvent(event)) {
                if (event -> type == SDL_MOUSEBUTTONDOWN) {
                    rect(renderer, 274, 697, 155, 89, orange.r, orange.g, orange.b, 1);
                    SDL_RenderPresent(renderer);
                    SDL_Delay(100);
                    music2_int = 1;
                }
                else {
                    continue;
                }
            }
            else {
                continue;
            }
        }
        //invisible_button(renderer, 258, 462, 121, 77, music_mute, true);
        if (x_m >= 258 && x_m <= 258 + 121 && y_m >= 462 && y_m <= 462 + 77) {
            if (SDL_PollEvent(event)) {
                if (event -> type == SDL_MOUSEBUTTONDOWN) {
                    rect(renderer, 272, 455, 110, 84, red.r, red.g, red.b, 1);
                    SDL_RenderPresent(renderer);
                    SDL_Delay(100);
                    music_mute = true;
                }
                else {
                    continue;
                }
            }
            else {
                continue;
            }
        }
        //invisible_button(renderer, 137, 462, 121, 77, music_unmute, true);
        if (x_m >= 137 && x_m <= 137 + 121 && y_m >= 462 && y_m <= 462 + 77) {
            if (SDL_PollEvent(event)) {
                if (event -> type == SDL_MOUSEBUTTONDOWN) {
                    rect(renderer, 130, 455, 110, 84, green.r, green.g, green.b, 1);
                    SDL_RenderPresent(renderer);
                    SDL_Delay(100);
                    music_unmute = true;
                }
                else {
                    continue;
                }
            }
            else {
                continue;
            }
        }
        //invisible_button(renderer, 258, 552, 124, 101, music_volume_up, true);
        if (x_m >= 258 && x_m <= 258 + 124 && y_m >= 552 && y_m <= 552 + 101) {
            if (SDL_PollEvent(event)) {
                if (event -> type == SDL_MOUSEBUTTONDOWN) {
                    rect(renderer, 266, 552, 120, 101, green.r, green.g, green.b, 1);
                    SDL_RenderPresent(renderer);
                    SDL_Delay(100);
                    music_volume_up = true;
                }
                else {
                    continue;
                }
            }
            else {
                continue;
            }
        }
        //invisible_button(renderer, 134, 552, 124, 101, music_volume_down, true);
        if (x_m >= 134 && x_m <= 134 + 124 && y_m >= 552 && y_m <= 552 + 101) {
            if (SDL_PollEvent(event)) {
                if (event -> type == SDL_MOUSEBUTTONDOWN) {
                    rect(renderer, 122, 552, 110, 101, red.r, red.g, red.b, 1);
                    SDL_RenderPresent(renderer);
                    SDL_Delay(100);
                    music_volume_down = true;
                }
                else {
                    continue;
                }
            }
            else {
                continue;
            }
        }
        if (x_m >= 648 && x_m <= 648 + 179 && y_m >= 441 && y_m <= 441 + 179) {
            if (SDL_PollEvent(event)) {
                if (event -> type == SDL_MOUSEBUTTONDOWN) {
                    rect(renderer, 648, 441, 179, 179, purple.r, purple.g, purple.b, 1);
                    SDL_RenderPresent(renderer);
                    SDL_Delay(100);
                    theme1 = true;
                }
                else {
                    continue;
                }
            }
            else {
                continue;
            }
        }

        invisible_button(renderer, 648, 630, 179, 179, theme2, true, purple.r, purple.g, purple.b);

        //BUTTONS----------------------------------------------------------------------


        //SOUND ADJUSTMENT----------------------------------------------------------------------

        if (music1_int) {
            Mix_PauseMusic();
            Mix_PlayMusic(music1, 1);
            music1_int = 0;
            music1_final = 1;
            music2_final = 0;
            return 0;
        }
        else if (music2_int) {
            Mix_PauseMusic();
            Mix_PlayMusic(music2, 1);
            music2_int = 0;
            music1_final = 0;
            music2_final = 1;
            return 0;
        }
        if (!effect) {
            if (music_mute) {
                if (volume != 0) {
                    volume_saved = volume;
                }
                volume = 0;
                Mix_VolumeMusic(volume);
                return 0;
            }
            else if (music_unmute) {
                if (volume == 0) {
                    volume = volume_saved;
                    Mix_VolumeMusic(volume);
                }
                return 0;
            }
            else if (music_volume_up) {
                volume += 10;
                Mix_VolumeMusic(volume);
                return 0;
            }
            else if (music_volume_down) {
                if (volume - 10 >= 0) {
                    volume -= 10;
                    Mix_VolumeMusic(volume);
                }
                return 0;
            }
        }

        else {
            if (music_mute) {
                if (effect_volume != 0) {
                    effect_volume_saved = effect_volume;
                }
                effect_volume = 0;
                Mix_VolumeChunk(hit_soundeffect, effect_volume);
                return 0;
            }
            else if (music_unmute) {
                if (effect_volume == 0) {
                    effect_volume = effect_volume_saved;
                    Mix_VolumeChunk(hit_soundeffect, effect_volume);
                }
                return 0;
            }
            else if (music_volume_up) {
                effect_volume += 10;
                Mix_VolumeChunk(hit_soundeffect, effect_volume);
                return 0;
            }
            else if (music_volume_down) {
                if (effect_volume - 10 >= 0) {
                    effect_volume -= 10;
                    Mix_VolumeChunk(hit_soundeffect, effect_volume);
                }
                return 0;
            }
        }

        //SOUND ADJUSTMENT----------------------------------------------------------------------

        //THEME SELECTION----------------------------------------------------------------------

        if (theme1) {
            theme = 1;
            return 0;
        }
        else if (theme2) {
            theme = 2;
            return 0;
        }

        //THEME SELECTION----------------------------------------------------------------------

    }
    return 1;
}

int login(SDL_Renderer * renderer, SDL_Texture * login_texture) {

    SDL_Event * event = new SDL_Event();
    int x_m, y_m;

    //TEXTURE LOADING----------------------------------------------------------------------

    SDL_RenderCopy(renderer, login_texture, NULL, NULL);
    SDL_RenderPresent(renderer);

    //TEXTURE LOADING----------------------------------------------------------------------

    string username;

    ofstream file;
    file.open(users_path.c_str(), ios::app);

    username = text_box(renderer,1, 50, 250, 400, 500, 50, 5, login_texture);

    bool time = false;

    if (file.good()) {
        file<<username<<" ";
    }
    file.close();

    users_count++;

    while (true) {

        SDL_GetMouseState(&x_m, &y_m);

        //BUTTONS----------------------------------------------------------------------

        if (x_m >= 340 && x_m <= 340 + 321 && y_m >= 566 && y_m <= 566 + 150) {
            if (SDL_PollEvent(event)) {
                if (event -> type == SDL_MOUSEBUTTONDOWN) {
                    rect(renderer, 333, 558, 332, 169, green.r, green.g, green.b, 1);
                    SDL_RenderPresent(renderer);
                    SDL_Delay(100);
                    return 1;
                    break;
                }
                else {
                    continue;
                }
            }
            else {
                continue;
            }
        }
        if (x_m >= 119 && x_m <= 119 + 321 && y_m >= 765 && y_m <= 765 + 150) {
            if (SDL_PollEvent(event)) {
                if (event -> type == SDL_MOUSEBUTTONDOWN) {
                    rect(renderer, 112, 757, 332, 169, green.r, green.g, green.b, 1);
                    SDL_RenderPresent(renderer);
                    SDL_Delay(100);
                    return 2;
                    break;
                }
                else {
                    continue;
                }
            }
            else {
                continue;
            }
        }

        invisible_button(renderer, 553, 760, 332, 169, time, 1, green.r, green.g, green.b);

        if (time) {
            time = false;
            return 3;
        }
    }

}

int game_infinite(SDL_Renderer * renderer, SDL_Texture * theme1_texture, int theme, SDL_Texture * pause_menu_texture, Mix_Music * music1, Mix_Music * music2, Mix_Music * gameover_music, SDL_Texture * gameover_texture, Mix_Chunk * hit_soundeffect) {

    //TIME----------------------------------------------------------------------
    int times;
    int pause_time = 0;

    time_t now = time(0);

    tm* ltm = localtime(&now);

    int hour_start = ltm->tm_hour;
    int min_start = ltm->tm_min;
    int sec_start = ltm->tm_sec;

    long long int time_start = (hour_start * 3600) + (min_start * 60) + sec_start;

    int hour_end;
    int min_end;
    int sec_end;
    int hour_start_pause;
    int hour_end_pause;
    int min_start_pause;
    int min_end_pause;
    int sec_start_pause;
    int sec_end_pause;

    //TIME----------------------------------------------------------------------


    //SCORE INITIALIZATION----------------------------------------------------------------------

    final_score = 0;
    bool game_lost = false;
    int two_hit=0;

    //SCORE INITIALIZATION----------------------------------------------------------------------


    //BALLS INITIALIZATION----------------------------------------------------------------------

    int balls[11][11];

    for (int i=0; i<11; i++) {
        for (int j=0; j<11; j++) {
            balls[i][j] = 0;
        }
    }

    randomize(0, 0, balls, 1);

    //BALLS INITIALIZATION----------------------------------------------------------------------

    int x_cannon, y_cannon;

    int pause_state=0;

    long double slope;

    if (theme == 1) {
        x_cannon = 515;
        y_cannon = 913;
    }
    else if (theme == 2) {
        x_cannon = 506;
        y_cannon = 877;
    }

    int x_m, y_m;
    long double dx = 0, dy = 0;
    long double x_ball = x_cannon, y_ball = y_cannon;
    long double ratio = 1;
    bool shooted = false;

    //TEXTURE LOADING----------------------------------------------------------------------

    SDL_RenderCopy(renderer, theme1_texture, NULL, NULL);

    //TEXTURE LOADING----------------------------------------------------------------------

    //SLOPE----------------------------------------------------------------------


    if (abs(y_m - y_cannon) > abs(x_m - x_cannon)) {

        slope = (y_cannon - y_m) / (x_m - x_cannon);

    }

    else {
        slope = (x_m - x_cannon) / (y_cannon - y_m);
    }


    //SLOPE----------------------------------------------------------------------

    bool exit = false;

    int hit=0, radius = standard_radius, ball_color = random_shooting_ball_color(), ball_color_2 = random_shooting_ball_color();

    while (ball_color_2 == ball_color) {
        ball_color_2 = random_shooting_ball_color();
    }

    SDL_Event * event = new SDL_Event();

    while (!exit) {

        drop_isolated(balls);

        SDL_GetMouseState(&x_m, &y_m);
        SDL_RenderCopy(renderer, theme1_texture, NULL, NULL);
        switch(ball_color_2) {
            case 1 :
                ellipse(renderer, x_cannon+70, y_cannon, 20, 20, red.r, red.g, red.b, 1);
                break;
            case 2 :
                ellipse(renderer, x_cannon+70, y_cannon, 20, 20, blue.r, blue.g, blue.b, 1);
                break;
            case 3 :
                ellipse(renderer, x_cannon+73, y_cannon, 20, 20, green.r, green.g, green.b, 1);
                break;
            case 4 :
                ellipse(renderer, x_cannon+73, y_cannon, 20, 20, yellow.r, yellow.g, yellow.b, 1);
                break;
            case 5 :
                ellipse(renderer, x_cannon+73, y_cannon, 20, 20, cyan.r, cyan.g, cyan.b, 1);
                break;
            case 6 :
                ellipse(renderer, x_cannon+73, y_cannon, 20, 20, purple.r, purple.g, purple.b, 1);
                break;
        }

        if (!shooted) {
            trajectory(renderer, x_m, y_m, x_cannon, y_cannon);
        }

        hit = balls_to_graphics(renderer, balls, x_ball, y_ball, ball_color);

        if (hit == 1) {

            Mix_PlayChannel( -1, hit_soundeffect, 0 );

            x_ball = x_cannon;
            y_ball = y_cannon;
            dx = 0;
            dy = 0;
            hit = 0;
            shooted = false;
            ball_color = ball_color_2;
            ball_color_2 = random_shooting_ball_color();

            while (ball_color_2 == ball_color) {
                ball_color_2 = random_shooting_ball_color();
            }

        }


        switch (ball_color) {
            case 1 :
                ellipse(renderer, x_ball, y_ball, radius, radius, red.r, red.g, red.b, 1);
                break;
            case 2 :
                ellipse(renderer, x_ball, y_ball, radius, radius, blue.r, blue.g, blue.b, 1);
                break;
            case 3 :
                ellipse(renderer, x_ball, y_ball, radius, radius, green.r, green.g, green.b, 1);
                break;
            case 4 :
                ellipse(renderer, x_ball, y_ball, radius, radius, yellow.r, yellow.g, yellow.b, 1);
                break;
            case 5 :
                ellipse(renderer, x_ball, y_ball, radius, radius, cyan.r, cyan.g, cyan.b, 1);
                break;
            case 6 :
                ellipse(renderer, x_ball, y_ball, radius, radius, purple.r, purple.g, purple.b, 1);
                break;
        }

        x_ball += dx;
        y_ball += dy;

        if (x_ball <= 40) {
            Mix_PlayChannel( -1, hit_soundeffect, 0 );
            dx = -1 * dx;
            x_ball = 41;
        }
        if (x_ball >= 960) {
            Mix_PlayChannel( -1, hit_soundeffect, 0 );
            dx = -1 * dx;
            x_ball = 959;
        }

        if (y_ball >= 960) {
            Mix_PlayChannel( -1, hit_soundeffect, 0 );
            dy = -1 * dy;
            y_ball = 959;
        }

        SDL_RenderPresent(renderer);

        if (SDL_PollEvent(event)) {
            if (event -> type == SDL_MOUSEBUTTONDOWN && !shooted) {
                shoot_count++;

                int length = sqrt(pow(y_cannon - y_m, 2) + pow(x_m - x_cannon, 2));
                long double dx_d, dy_d;

                dx_d = linear_velocity * (x_m - x_cannon) / length;
                dy_d = linear_velocity * (y_cannon - y_m) / length;

                dx = int(dx_d);
                dy = -1 * int(dy_d);

                shooted = true;
                hit = 0;
                two_hit++;

                if (two_hit == 2) {

                    two_hit = 0;
                    shift_balls(balls, game_lost);

                    if (game_lost) {

                        //TIME----------------------------------------------------------------------

                        time_t now = time(0);

                        tm* ltm = localtime(&now);

                        hour_end = ltm->tm_hour;
                        min_end = ltm->tm_min;
                        sec_end = ltm->tm_sec;

                        long long int time_end = (hour_end * 3600) + (min_end * 60) + sec_end;

                        times = time_end - time_start;

                        //TIME----------------------------------------------------------------------

                        gameover(renderer, gameover_texture, gameover_music, times-pause_time);
                        game_lost = false;
                        Mix_PauseMusic();

                        if (music1_final) {
                            Mix_PlayMusic(music1, -1);
                        }
                        else if (music2_final) {
                            Mix_PlayMusic(music2, -1);
                        }

                        exit = true;
                        break;
                    }

                }
            }
            else if (event -> type == SDL_KEYDOWN) {
                if (event -> key.keysym.sym == SDLK_ESCAPE) {

                    //TIME----------------------------------------------------------------------

                    now = time(0);

                    ltm = localtime(&now);

                    hour_start_pause = ltm->tm_hour;
                    min_start_pause = ltm->tm_min;
                    sec_start_pause = ltm->tm_sec;

                    //TIME----------------------------------------------------------------------

                    while (pause_state == 0) {
                        pause_state = pause_menu(renderer, pause_menu_texture, music1, music2, hit_soundeffect);
                    }

                    //TIME----------------------------------------------------------------------

                    now = time(0);

                    ltm = localtime(&now);

                    hour_end_pause = ltm->tm_hour;
                    min_end_pause = ltm->tm_min;
                    sec_end_pause = ltm->tm_sec;

                    pause_time += ((hour_end_pause - hour_start_pause) * 3600) + ((min_end_pause - min_start_pause) * 60) + (sec_end_pause - sec_start_pause);

                    //TIME----------------------------------------------------------------------

                    if (pause_state == 1) {
                        exit = true;
                        pause_state = 0;
                        break;
                    }
                    else if (pause_state == -1) {
                        pause_state = 0;
                        continue;
                    }
                }
                else if (event -> key.keysym.sym == SDLK_SPACE && !shooted) {
                    swap(ball_color, ball_color_2);
                }

            }
        }
    }

    return 1;
}

int game_normal(SDL_Renderer * renderer, SDL_Texture * theme1_texture, int theme, SDL_Texture * pause_menu_texture, Mix_Music * music1, Mix_Music * music2, Mix_Music * gameover_music, SDL_Texture * gameover_texture, Mix_Chunk * hit_soundeffect, SDL_Texture * win_texture, Mix_Music * win_music) {

    //TIME----------------------------------------------------------------------
    int times;
    int pause_time = 0;

    time_t now = time(0);

    tm* ltm = localtime(&now);

    int hour_start = ltm->tm_hour;
    int min_start = ltm->tm_min;
    int sec_start = ltm->tm_sec;

    long long int time_start = (hour_start * 3600) + (min_start * 60) + sec_start;

    int hour_end;
    int min_end;
    int sec_end;
    int hour_start_pause;
    int hour_end_pause;
    int min_start_pause;
    int min_end_pause;
    int sec_start_pause;
    int sec_end_pause;

    //TIME----------------------------------------------------------------------

    //SCORE INITIALIZATION----------------------------------------------------------------------

    final_score = 0;
    bool game_lost = false;
    bool end_shift = false;
    int two_hit=0;
    static int shift = 0;

    //SCORE INITIALIZATION----------------------------------------------------------------------


    //BALLS INITIALIZATION----------------------------------------------------------------------

    int balls[11][11];

    for (int i=0; i<11; i++) {
        for (int j=0; j<11; j++) {
            balls[i][j] = 0;
        }
    }

    randomize(0, 0, balls, 1);

    //BALLS INITIALIZATION----------------------------------------------------------------------

    int x_cannon, y_cannon;

    int pause_state=0;

    long double slope;

    if (theme == 1) {
        x_cannon = 515;
        y_cannon = 913;
    }
    else if (theme == 2) {
        x_cannon = 506;
        y_cannon = 877;
    }

    int x_m, y_m;
    long double dx = 0, dy = 0;
    long double x_ball = x_cannon, y_ball = y_cannon;
    long double ratio = 1;
    bool shooted = false;

    //TEXTURE LOADING----------------------------------------------------------------------

    SDL_RenderCopy(renderer, theme1_texture, NULL, NULL);

    //TEXTURE LOADING----------------------------------------------------------------------

    bool exit = false;

    int hit=0, radius = standard_radius, ball_color = random_shooting_ball_color(), ball_color_2 = random_shooting_ball_color();

    while (ball_color_2 == ball_color) {
        ball_color_2 = random_shooting_ball_color();
    }

    SDL_Event * event = new SDL_Event();

    while (!exit) {

        SDL_GetMouseState(&x_m, &y_m);
        SDL_RenderCopy(renderer, theme1_texture, NULL, NULL);

        switch(ball_color_2) {
            case 1 :
                ellipse(renderer, x_cannon+70, y_cannon, 20, 20, red.r, red.g, red.b, 1);
                break;
            case 2 :
                ellipse(renderer, x_cannon+70, y_cannon, 20, 20, blue.r, blue.g, blue.b, 1);
                break;
            case 3 :
                ellipse(renderer, x_cannon+73, y_cannon, 20, 20, green.r, green.g, green.b, 1);
                break;
            case 4 :
                ellipse(renderer, x_cannon+73, y_cannon, 20, 20, yellow.r, yellow.g, yellow.b, 1);
                break;
            case 5 :
                ellipse(renderer, x_cannon+73, y_cannon, 20, 20, cyan.r, cyan.g, cyan.b, 1);
                break;
            case 6 :
                ellipse(renderer, x_cannon+73, y_cannon, 20, 20, purple.r, purple.g, purple.b, 1);
                break;
        }

        if (!shooted) {
            trajectory(renderer, x_m, y_m, x_cannon, y_cannon);
        }

        hit = balls_to_graphics(renderer, balls, x_ball, y_ball, ball_color);

        if (hit == 1) {

            Mix_PlayChannel( -1, hit_soundeffect, 0 );

            x_ball = x_cannon;
            y_ball = y_cannon;
            dx = 0;
            dy = 0;
            hit = 0;
            shooted = false;
            ball_color = ball_color_2;
            ball_color_2 = random_shooting_ball_color();

            while(!color_in_balls(ball_color_2, balls)) {
                ball_color_2 = random_shooting_ball_color();
            }

        }

        switch (ball_color) {
            case 1 :
                ellipse(renderer, x_ball, y_ball, radius, radius, red.r, red.g, red.b, 1);
                break;
            case 2 :
                ellipse(renderer, x_ball, y_ball, radius, radius, blue.r, blue.g, blue.b, 1);
                break;
            case 3 :
                ellipse(renderer, x_ball, y_ball, radius, radius, green.r, green.g, green.b, 1);
                break;
            case 4 :
                ellipse(renderer, x_ball, y_ball, radius, radius, yellow.r, yellow.g, yellow.b, 1);
                break;
            case 5 :
                ellipse(renderer, x_ball, y_ball, radius, radius, cyan.r, cyan.g, cyan.b, 1);
                break;
            case 6 :
                ellipse(renderer, x_ball, y_ball, radius, radius, purple.r, purple.g, purple.b, 1);
                break;
        }

        x_ball += dx;
        y_ball += dy;

        if (x_ball <= 40) {
            Mix_PlayChannel( -1, hit_soundeffect, 0 );
            dx = -1 * dx;
            x_ball = 41;
        }
        if (x_ball >= 960) {
            Mix_PlayChannel( -1, hit_soundeffect, 0 );
            dx = -1 * dx;
            x_ball = 959;
        }

        if (y_ball >= 960) {
            Mix_PlayChannel( -1, hit_soundeffect, 0 );
            dy = -1 * dy;
            y_ball = 959;
        }

        if (shift == 6) {
            end_shift = true;
        }

        if (allzero(balls)) {

            //TIME----------------------------------------------------------------------

            time_t now = time(0);

            tm* ltm = localtime(&now);

            hour_end = ltm->tm_hour;
            min_end = ltm->tm_min;
            sec_end = ltm->tm_sec;

            long long int time_end = (hour_end * 3600) + (min_end * 60) + sec_end;

            times = time_end - time_start;

            //TIME----------------------------------------------------------------------

            gamewin(renderer, win_texture, win_music, times-pause_time);
            shift = 0;
            Mix_PauseMusic();
            Mix_PlayMusic(music2, -1);
            exit = true;
            break;
        }

        SDL_RenderPresent(renderer);

        if (SDL_PollEvent(event)) {
            if (event -> type == SDL_MOUSEBUTTONDOWN && !shooted) {
                shoot_count++;

                int length = sqrt(pow(y_cannon - y_m, 2) + pow(x_m - x_cannon, 2));
                long double dx_d, dy_d;

                dx_d = linear_velocity * (x_m - x_cannon) / length;
                dy_d = linear_velocity * (y_cannon - y_m) / length;

                dx = int(dx_d);

                dy = -1 * int(dy_d);

                shooted = true;
                hit = 0;
                two_hit++;

                if (two_hit == 2) {
                    two_hit = 0;

                    if (!end_shift) {
                        shift_balls(balls, game_lost);
                    }
                    else {
                        game_lost = false;
                    }

                    shift++;

                    if (game_lost) {

                        //TIME----------------------------------------------------------------------

                        time_t now = time(0);

                        tm* ltm = localtime(&now);

                        hour_end = ltm->tm_hour;
                        min_end = ltm->tm_min;
                        sec_end = ltm->tm_sec;

                        long long int time_end = (hour_end * 3600) + (min_end * 60) + sec_end;

                        times = time_end - time_start;

                        //TIME----------------------------------------------------------------------

                        gameover(renderer, gameover_texture, gameover_music, times);
                        game_lost = false;
                        Mix_PauseMusic();

                        if (music1_final) {
                            Mix_PlayMusic(music1, -1);
                        }
                        else if (music2_final) {
                            Mix_PlayMusic(music2, -1);
                        }

                        exit = true;
                        break;
                    }

                }
            }
            else if (event -> type == SDL_KEYDOWN) {
                if (event -> key.keysym.sym == SDLK_ESCAPE) {

                    //TIME----------------------------------------------------------------------

                    now = time(0);

                    ltm = localtime(&now);

                    hour_start_pause = ltm->tm_hour;
                    min_start_pause = ltm->tm_min;
                    sec_start_pause = ltm->tm_sec;

                    //TIME----------------------------------------------------------------------

                    while (pause_state == 0) {
                        pause_state = pause_menu(renderer, pause_menu_texture, music1, music2, hit_soundeffect);
                    }

                    //TIME----------------------------------------------------------------------

                    now = time(0);

                    ltm = localtime(&now);

                    hour_end_pause = ltm->tm_hour;
                    min_end_pause = ltm->tm_min;
                    sec_end_pause = ltm->tm_sec;

                    pause_time += ((hour_end_pause - hour_start_pause) * 3600) + ((min_end_pause - min_start_pause) * 60) + (sec_end_pause - sec_start_pause);

                    //TIME----------------------------------------------------------------------

                    if (pause_state == 1) {
                        exit = true;
                        pause_state = 0;
                        break;
                    }
                    else if (pause_state == -1) {
                        pause_state = 0;
                        continue;
                    }
                }
                else if (event -> key.keysym.sym == SDLK_SPACE && !shooted) {
                    swap(ball_color, ball_color_2);
                }

            }
        }
    }

    return 1;

}

int game_time(SDL_Renderer * renderer, SDL_Texture * theme1_texture, int theme, SDL_Texture * pause_menu_texture, Mix_Music * music1, Mix_Music * music2, Mix_Music * gameover_music, SDL_Texture * gameover_texture, Mix_Chunk * hit_soundeffect, SDL_Texture * win_texture, Mix_Music * win_music) {

    //TIME----------------------------------------------------------------------
    int times;
    int pause_time = 0;

    time_t now = time(0);

    tm* ltm = localtime(&now);

    int hour_start = ltm->tm_hour;
    int min_start = ltm->tm_min;
    int sec_start = ltm->tm_sec;

    long long int time_start = (hour_start * 3600) + (min_start * 60) + sec_start;

    int hour_end;
    int min_end;
    int sec_end;
    int hour_start_pause;
    int hour_end_pause;
    int min_start_pause;
    int min_end_pause;
    int sec_start_pause;
    int sec_end_pause;

    //TIME----------------------------------------------------------------------

    //SCORE INITIALIZATION----------------------------------------------------------------------

    final_score = 0;
    bool game_lost = false;
    bool end_shift = false;
    int two_hit=0;
    static int shift = 0;

    //SCORE INITIALIZATION----------------------------------------------------------------------


    //BALLS INITIALIZATION----------------------------------------------------------------------

    int balls[11][11];

    for (int i=0; i<11; i++) {
        for (int j=0; j<11; j++) {
            balls[i][j] = 0;
        }
    }

    randomize(0, 0, balls, 1);

    //BALLS INITIALIZATION----------------------------------------------------------------------

    int x_cannon, y_cannon;

    int pause_state=0;

    long double slope;

    if (theme == 1) {
        x_cannon = 515;
        y_cannon = 913;
    }
    else if (theme == 2) {
        x_cannon = 506;
        y_cannon = 877;
    }

    int x_m, y_m;
    long double dx = 0, dy = 0;
    long double x_ball = x_cannon, y_ball = y_cannon;
    long double ratio = 1;
    bool shooted = false;

    //TEXTURE LOADING----------------------------------------------------------------------

    SDL_RenderCopy(renderer, theme1_texture, NULL, NULL);

    //TEXTURE LOADING----------------------------------------------------------------------

    bool exit = false;

    int hit=0, radius = standard_radius, ball_color = random_shooting_ball_color(), ball_color_2 = random_shooting_ball_color();

    while (ball_color_2 == ball_color) {
        ball_color_2 = random_shooting_ball_color();
    }

    SDL_Event * event = new SDL_Event();

    while (!exit) {

        drop_isolated(balls);

        //TIME----------------------------------------------------------------------

        time_t now = time(0);

        tm* ltm = localtime(&now);

        hour_end = ltm->tm_hour;
        min_end = ltm->tm_min;
        sec_end = ltm->tm_sec;

        long long int time_end = (hour_end * 3600) + (min_end * 60) + sec_end;

        times = time_end - time_start;

        //TIME----------------------------------------------------------------------

        if (times == time_limit) {
            gameover(renderer, gameover_texture, gameover_music, times);
            Mix_PauseMusic();

            if (music1_final) {
                Mix_PlayMusic(music1, -1);
            }
            else if (music2_final) {
                Mix_PlayMusic(music2, -1);
            }

            exit = true;
            break;
        }

        SDL_GetMouseState(&x_m, &y_m);
        SDL_RenderCopy(renderer, theme1_texture, NULL, NULL);
        display_text(renderer, 0, 930, 50, 70, 25*to_string(time_limit-times+pause_time).length()+5, to_string(time_limit-times+pause_time), 1, 5);

        switch(ball_color_2) {
            case 1 :
                ellipse(renderer, x_cannon+70, y_cannon, 20, 20, red.r, red.g, red.b, 1);
                break;
            case 2 :
                ellipse(renderer, x_cannon+70, y_cannon, 20, 20, blue.r, blue.g, blue.b, 1);
                break;
            case 3 :
                ellipse(renderer, x_cannon+73, y_cannon, 20, 20, green.r, green.g, green.b, 1);
                break;
            case 4 :
                ellipse(renderer, x_cannon+73, y_cannon, 20, 20, yellow.r, yellow.g, yellow.b, 1);
                break;
            case 5 :
                ellipse(renderer, x_cannon+73, y_cannon, 20, 20, cyan.r, cyan.g, cyan.b, 1);
                break;
            case 6 :
                ellipse(renderer, x_cannon+73, y_cannon, 20, 20, purple.r, purple.g, purple.b, 1);
                break;
        }

        if (!shooted) {
            trajectory(renderer, x_m, y_m, x_cannon, y_cannon);
        }

        hit = balls_to_graphics(renderer, balls, x_ball, y_ball, ball_color);


        if (hit == 1) {

            Mix_PlayChannel( -1, hit_soundeffect, 0 );

            x_ball = x_cannon;
            y_ball = y_cannon;
            dx = 0;
            dy = 0;
            hit = 0;
            shooted = false;
            ball_color = ball_color_2;
            ball_color_2 = random_shooting_ball_color();

            while(!color_in_balls(ball_color_2, balls)) {
                ball_color_2 = random_shooting_ball_color();
            }

        }


        switch (ball_color) {
            case 1 :
                ellipse(renderer, x_ball, y_ball, radius, radius, red.r, red.g, red.b, 1);
                break;
            case 2 :
                ellipse(renderer, x_ball, y_ball, radius, radius, blue.r, blue.g, blue.b, 1);
                break;
            case 3 :
                ellipse(renderer, x_ball, y_ball, radius, radius, green.r, green.g, green.b, 1);
                break;
            case 4 :
                ellipse(renderer, x_ball, y_ball, radius, radius, yellow.r, yellow.g, yellow.b, 1);
                break;
            case 5 :
                ellipse(renderer, x_ball, y_ball, radius, radius, cyan.r, cyan.g, cyan.b, 1);
                break;
            case 6 :
                ellipse(renderer, x_ball, y_ball, radius, radius, purple.r, purple.g, purple.b, 1);
                break;
        }

        x_ball += dx;
        y_ball += dy;

        if (x_ball <= 40) {
            Mix_PlayChannel( -1, hit_soundeffect, 0 );
            dx = -1 * dx;
            x_ball = 41;
        }
        if (x_ball >= 960) {
            Mix_PlayChannel( -1, hit_soundeffect, 0 );
            dx = -1 * dx;
            x_ball = 959;
        }

        if (y_ball >= 960) {
            Mix_PlayChannel( -1, hit_soundeffect, 0 );
            dy = -1 * dy;
            y_ball = 959;
        }

        if (shift == 6) {
            end_shift = true;
        }

        if (allzero(balls)) {

            //TIME----------------------------------------------------------------------

            time_t now = time(0);

            tm* ltm = localtime(&now);

            hour_end = ltm->tm_hour;
            min_end = ltm->tm_min;
            sec_end = ltm->tm_sec;

            long long int time_end = (hour_end * 3600) + (min_end * 60) + sec_end;

            times = time_end - time_start;

            //TIME----------------------------------------------------------------------

            gamewin(renderer, win_texture, win_music, times-pause_time);
            shift = 0;
            Mix_PauseMusic();
            Mix_PlayMusic(music2, -1);
            exit = true;
            break;
        }

        SDL_RenderPresent(renderer);

        if (SDL_PollEvent(event)) {
            if (event -> type == SDL_MOUSEBUTTONDOWN && !shooted) {

                shoot_count++;

                int length = sqrt(pow(y_cannon - y_m, 2) + pow(x_m - x_cannon, 2));
                long double dx_d, dy_d;

                dx_d = linear_velocity * (x_m - x_cannon) / length;
                dy_d = linear_velocity * (y_cannon - y_m) / length;

                dx = int(dx_d);

                dy = -1 * int(dy_d);

                shooted = true;
                hit = 0;
                two_hit++;

                if (two_hit == 2) {

                    two_hit = 0;

                    if (!end_shift) {
                        shift_balls(balls, game_lost);
                    }
                    else {
                        game_lost = false;
                    }

                    shift++;

                    if (game_lost) {

                        //TIME----------------------------------------------------------------------

                        time_t now = time(0);

                        tm* ltm = localtime(&now);

                        hour_end = ltm->tm_hour;
                        min_end = ltm->tm_min;
                        sec_end = ltm->tm_sec;

                        long long int time_end = (hour_end * 3600) + (min_end * 60) + sec_end;

                        times = time_end - time_start;

                        //TIME----------------------------------------------------------------------

                        gameover(renderer, gameover_texture, gameover_music, times);
                        game_lost = false;
                        Mix_PauseMusic();
                        Mix_PlayMusic(music2, -1);
                        exit = true;
                        break;
                    }

                }
            }
            else if (event -> type == SDL_KEYDOWN) {
                if (event -> key.keysym.sym == SDLK_ESCAPE) {
                    //TIME
                    now = time(0);

                    ltm = localtime(&now);

                    hour_start_pause = ltm->tm_hour;
                    min_start_pause = ltm->tm_min;
                    sec_start_pause = ltm->tm_sec;
                    //TIME
                    while (pause_state == 0) {
                        pause_state = pause_menu(renderer, pause_menu_texture, music1, music2, hit_soundeffect);
                    }
                    //TIME

                    now = time(0);

                    ltm = localtime(&now);

                    hour_end_pause = ltm->tm_hour;
                    min_end_pause = ltm->tm_min;
                    sec_end_pause = ltm->tm_sec;

                    pause_time += ((hour_end_pause - hour_start_pause) * 3600) + ((min_end_pause - min_start_pause) * 60) + (sec_end_pause - sec_start_pause);

                    //TIME

                    if (pause_state == 1) {
                        exit = true;
                        pause_state = 0;
                        break;
                    }
                    else if (pause_state == -1) {
                        pause_state = 0;
                        continue;
                    }
                }
                else if (event -> key.keysym.sym == SDLK_SPACE && !shooted) {
                    swap(ball_color, ball_color_2);
                }

            }
        }
    }

    return 1;

}

bool allzero(int balls[11][11]) {
    for (int i=0; i<11; i++) {
        for (int j=0; j<11; j++) {
            if (balls[i][j] != 0) {
                return false;
            }
        }
    }
    return true;
}

int trajectory(SDL_Renderer * renderer, int x_m, int y_m, int x_cannon, int y_cannon) {

    long double x, y;

    thickLineRGBA(renderer, x_cannon, y_cannon, x_m + (x_m - x_cannon)*20, y_m + (- y_cannon +y_m)*20, trajectory_width, purple.r, purple.g, purple.b, 255);

    if (x_m > x_cannon) {

        if (x_m != x_cannon && abs(x_m - x_cannon) > 10) {

            x = 1000;
            y = (1000 - x_cannon) * (y_cannon - y_m) / (x_m - x_cannon);
            y = 1000 - y;
            if (theme == 1) {
                y -= 90;
            }
            else {
                y -= 123;
            }
            thickLineRGBA(renderer, int(x), int(y), int(x) - (x_m - x_cannon)*20, int(y) - (y_cannon - y_m)*20, trajectory_width, purple.r, purple.g, purple.b, 255);

        }

    }

    else {
        x = 0;
        if (x_m != x_cannon && abs(x_m - x_cannon) > 10) {
            y = (y_cannon - y_m) * (x_cannon) / (x_cannon - x_m);
            y = 1000 - y;

            if (theme == 1) {
                y -= 90;
            }
            else {
                y -= 123;
            }
            thickLineRGBA(renderer, int(x), int(y), int(x) + (x_cannon - x_m)*10, int(y) - (y_cannon - y_m)*10, trajectory_width, purple.r, purple.g, purple.b, 255);
        }
    }
}

void ball_chain(int i, int j, int balls[11][11], int ball_color) {

    if (i+1<11 && balls[i+1][j] == ball_color) {
        final_score += score_per_ball;
        balls[i+1][j] = 0;
        ball_chain(i+1, j, balls, ball_color);
    }
    if (j+1<11 && balls[i][j+1] == ball_color) {
        final_score += score_per_ball;
        balls[i][j+1] = 0;
        ball_chain(i, j+1, balls, ball_color);
    }
    if (i-1>=0 && balls[i-1][j] == ball_color) {
        final_score += score_per_ball;
        balls[i-1][j] = 0;
        ball_chain(i-1, j, balls, ball_color);
    }
    if (j-1>=0 && balls[i][j-1] == ball_color) {
        final_score += score_per_ball;
        balls[i][j-1] = 0;
        ball_chain(i, j-1, balls, ball_color);
    }
}

bool color_in_balls(int color_ball, int balls[11][11]) {
    if (color_ball == 6) {
        return true;
    }
    for (int i=0; i<11; i++) {
        for (int j=0; j<11; j++) {
            if (balls[i][j] == color_ball) {
                return true;
            }
        }
    }
    return false;
}

bool has_around_stick(int i, int j, int ball_color, int balls[11][11]) {
    int count = 0;
    if ((i+1 < 11 && balls[i+1][j] == ball_color)) {
        count++;
        if ((i+2 < 11 && balls[i+2][j] == ball_color) || (j+1 < 11 && balls[i+1][j+1] == ball_color) || (j-1 >= 0 && balls[i+1][j-1] == ball_color)) {
            return true;
        }
    }
    if ((j+1 < 11 && balls[i][j+1] == ball_color)) {
        count++;
        if ((i+1 < 11 && balls[i+1][j+1] == ball_color) || (j+2 < 11 && balls[i][j+2] == ball_color) || (i-1 >= 0 && balls[i-1][j+1] == ball_color)) {
            return true;
        }
    }
    if ((i-1 >= 0 && balls[i-1][j] == ball_color)) {
        count++;
        if ((i-2 >= 0 && balls[i-2][j] == ball_color) || (j+1 < 11 && balls[i-1][j+1] == ball_color) || (j-1 >= 0 && balls[i-1][j-1] == ball_color)) {
            return true;
        }
    }
    if ((j-1 >= 0 && balls[i][j-1] == ball_color)) {
        count++;
        if ((i+1 < 11 && balls[i+1][j-1] == ball_color) || (j-2 >= 0 && balls[i][j-2] == ball_color) || (i-1 >= 0 && balls[i-1][j-1] == ball_color)) {
            return true;
        }
    }
    if (count == 2) {
        return true;
    }
    return false;
}

int balls_to_graphics(SDL_Renderer * renderer, int balls[11][11], int x_ball, int y_ball, int color_ball) {

    bool rainbow = false, hit = false, chain = false, stick = false, not_three, stuck_hit = false;

    int x, y;

    for (int i=10; i>=0; i--) {
        for (int j=0; j<11; j++) {

            //X & Y DEFINITION OF THE BALLS----------------------------------------------------------------------

            x = 60 + standard_radius * (2*j + 1);
            y = (2*i + 1) * standard_radius;

            //X & Y DEFINITION OF THE BALLS----------------------------------------------------------------------

            not_three = false;

            if (i == 0 && balls[i][j] == 0 && !hit && !stick) {
                if (sqrt(pow(x_ball - x, 2) + pow(y_ball, y)) <= 2*standard_radius &&!stick) {
                    balls[0][j] = color_ball;
                    stick = true;
                }
            }

            if (balls[i][j] != 0 && !hit && sqrt(pow(x_ball - x, 2) + pow(y_ball - y, 2)) <= 2 * standard_radius &&!stick) {
                if (color_ball == 6 && balls[i][j] != 7 && !hit) {
                    color_ball = balls[i][j];
                    rainbow = true;
                }
                else if (color_ball == 6 && balls[i][j] == 7 && !hit && !stick) {
                    hit = true;
                }
                if ((color_ball == balls[i][j]) && !hit) {

                    if (rainbow) {
                        balls[i][j] = 0;
                        hit = true;
                    }

                    else {
                        if ((i+1 < 11 && balls[i+1][j] == color_ball) || (j+1 < 11 && balls[i][j+1] == color_ball) || (i-1 >= 0 && balls[i-1][j] == color_ball) || (j-1 >= 0 && balls[i][j-1] == color_ball)) {
                            balls[i][j] = 0;
                            hit = true;
                        }

                        else {
                            not_three = true;
                        }
                    }
                }

                if (hit && !chain) {
                    chain = true;
                    if (color_ball == 6) {
                        ball_chain(i, j, balls, balls[i][j]);
                    }
                    else {
                        ball_chain(i, j, balls, color_ball);
                    }
                }

                if ((color_ball != balls[i][j] || not_three) && color_ball != 6 && !hit && !stick) {
                    if (x_ball > x) {
                        if ((x_ball - x) <= 1.53 * standard_radius && (x_ball - x) >= 1.33 * standard_radius && i+1 < 11 && j + 1 < 11 && balls[i+1][j+1] == 0) {
                            balls[i+1][j+1] = color_ball;
                            if (has_around_stick(i+1, j+1, color_ball, balls)) {
                                hit = true;
                                balls[i+1][j+1] = 0;
                                ball_chain(i+1, j+1, balls, color_ball);
                            }
                        }
                        else if (((y_ball - y) < (x_ball - x)) && j+1<11 && balls[i][j+1] == 0) {
                            balls[i][j+1] = color_ball;
                            if (has_around_stick(i, j+1, color_ball, balls)) {
                                hit = true;
                                balls[i][j+1] = 0;
                                ball_chain(i, j+1, balls, color_ball);
                            }
                        }
                        else {
                            balls[i+1][j] = color_ball;
                            if (has_around_stick(i+1, j, color_ball, balls)) {
                                hit = true;
                                balls[i+1][j] = 0;
                                ball_chain(i+1, j, balls, color_ball);
                            }
                        }
                    }
                    else {
                        if ((x - x_ball) <= 1.53 * standard_radius && (x - x_ball) >= 1.33 * standard_radius && i-1 >= 0 && j + 1 < 11 && balls[i-1][j+1] == 0) {
                            balls[i-1][j+1] = color_ball;
                            if (has_around_stick(i-1, j+1, color_ball, balls)) {
                                hit = true;
                                balls[i-1][j+1] = 0;
                                ball_chain(i-1, j+1, balls, color_ball);
                            }
                        }
                        if (((y_ball - y) < (x - x_ball)) && j-1>=0 && balls[i][j-1] == 0) {
                            balls[i][j-1] = color_ball;
                            if (has_around_stick(i, j-1, color_ball, balls)) {
                                hit = true;
                                balls[i][j-1] = 0;
                                ball_chain(i, j-1, balls, color_ball);
                            }
                        }
                        else {
                            balls[i+1][j] = color_ball;
                            if (has_around_stick(i+1, j, color_ball, balls)) {
                                hit = true;
                                balls[i+1][j] = 0;
                                ball_chain(i+1, j, balls, color_ball);
                            }
                        }
                    }
                    stick = true;
                    not_three = false;
                }
            }

            switch(balls[i][j]) {
                case 1 :
                    ellipse(renderer, x, y, standard_radius, standard_radius, red.r, red.g, red.b, 1);
                    break;
                case 2 :
                    ellipse(renderer, x, y, standard_radius, standard_radius, blue.r, blue.g, blue.b, 1);
                    break;
                case 3 :
                    ellipse(renderer, x, y, standard_radius, standard_radius, green.r, green.g, green.b, 1);
                    break;
                case 4 :
                    ellipse(renderer, x, y, standard_radius, standard_radius, yellow.r, yellow.g, yellow.b, 1);
                    break;
                case 5 :
                    ellipse(renderer, x, y, standard_radius, standard_radius, cyan.r, cyan.g, cyan.b, 1);
                    break;
                case 7 :
                    ellipse(renderer, x, y, standard_radius, standard_radius, black.r, black.g, black.b, 1);
                    break;
                default :
                    break;
            }
        }
    }

    if (hit) {
        drop_isolated(balls);
    }

    if (hit || stick) {
        return 1;
    }
    else {
        return 0;
    }
}

int random_number() {

    int color = (rand()%6) + 1;
    if (color == 6) {
        color = 7;
    }
    return color;
}

int coin_flip() {
    int ans = rand() % 2;
    return ans;
}

void randomize(int i, int j, int balls[11][11], int color) {

    int coin, new_color;

    if (color == 7) {

        if (i+1 < 5 && balls[i+1][j] == 0) {
            new_color = random_number();
            balls[i+1][j] = new_color;
            randomize(i+1, j, balls, new_color);
        }

        if (j+1 < 11 && balls[i][j+1] == 0) {
            new_color = random_number();
            balls[i][j+1] = new_color;
            randomize(i, j+1, balls, new_color);
        }

        if (j-1 >= 0 && balls[i][j-1] == 0) {
            new_color = random_number();
            balls[i][j-1] = new_color;
            randomize(i, j-1, balls, new_color);
        }

        if (i-1 >= 0 && balls[i-1][j] == 0) {
            new_color = random_number();
            balls[i-1][j] = new_color;
            randomize(i-1, j, balls, new_color);
        }

    }

    else {
        if (i+1 < 5 && balls[i+1][j] == 0) {
            coin = coin_flip();
            if (coin == 0) {
                balls[i+1][j] = color;
                randomize(i+1, j, balls, color);
            }
            else {
                new_color = random_number();
                balls[i+1][j] = new_color;
                randomize(i+1, j, balls, new_color);
            }
        }

        if (j+1 < 11 && balls[i][j+1] == 0) {
            coin = coin_flip();
            if (coin == 0) {
                balls[i][j+1] = color;
                randomize(i, j+1, balls, color);
            }
            else {
                new_color = random_number();
                balls[i][j+1] = new_color;
                randomize(i, j+1, balls, new_color);
            }
        }

        if (j-1 >= 0 && balls[i][j-1] == 0) {
            coin = coin_flip();
            if (coin == 0) {
                balls[i][j-1] = color;
                randomize(i, j-1, balls, color);
            }
            else {
                new_color = random_number();
                balls[i][j-1] = new_color;
                randomize(i, j-1, balls, new_color);
            }
        }

        if (i-1 >= 0 && balls[i-1][j] == 0) {
            coin = coin_flip();
            if (coin == 0) {
                balls[i-1][j] = color;
                randomize(i-1, j, balls, color);
            }
            else {
                new_color = random_number();
                balls[i-1][j] = new_color;
                randomize(i-1, j, balls, new_color);
            }
        }

    }

}

int linear_randomize(int balls[11][11], int color, int j) {

    int coin, new_color;
    if (j+1 < 11 && balls[0][j+1] == 0) {
        coin = coin_flip();
        if (coin == 0) {
            balls[0][j+1] = color;
            linear_randomize(balls, color, j+1);
        }
        else {
            new_color = random_number();
            while (new_color == 7) {
                new_color = random_number();
            }
            balls[0][j+1] = new_color;
            linear_randomize(balls, new_color, j+1);
        }
    }
}

int shift_balls(int balls[11][11], bool & game_lost) {

    int temp_balls[11][11];
    for (int i=0; i<11; i++) {
        for (int j=0; j<11; j++) {
            temp_balls[i][j] = 0;
        }
    }
    for (int i=0; i<11; i++) {
        for (int j=0; j<11; j++) {
            if (balls[i][j] != 0) {
                temp_balls[i+1][j] = balls[i][j];
            }
        }
    }
    for (int i=0; i<11; i++) {
        for (int j=0; j<11; j++) {
            balls[i][j] = temp_balls[i][j];
        }
    }
    for (int i=0; i<11; i++) {
        if (balls[10][i] != 0) {
            game_lost = true;
            return -1;
        }
    }
    balls[0][0] = 1;
    linear_randomize(balls, 1, 0);
}

int is_connected(int balls[11][11], bool isolated[11][11], int i, int j) {
    if (i+1 < 11 && isolated[i+1][j] == 0 && balls[i+1][j] != 0) {
        isolated[i+1][j] = true;
        is_connected(balls, isolated, i+1, j);
    }
    if (j+1 < 11 && isolated[i][j+1] == 0 && balls[i][j+1] != 0) {
        isolated[i][j+1] = true;
        is_connected(balls, isolated, i, j+1);
    }
    if (i-1 >= 0 && isolated[i-1][j] == 0 && balls[i-1][j] != 0) {
        isolated[i-1][j] = true;
        is_connected(balls, isolated, i-1, j);
    }
    if (j-1 >= 0 && isolated[i][j-1] == 0 && balls[i][j-1] != 0) {
        isolated[i][j-1] = true;
        is_connected(balls, isolated, i, j-1);
    }

    return 0;
}

int drop_isolated(int balls[11][11]) {
    bool isolated[11][11];
    for (int i=0; i<11; i++) {
        for (int j=0; j<11; j++) {
            isolated[i][j] = false;
        }
    }
    for (int j=0; j<11; j++) {
        if (balls[0][j] != 0) {
            is_connected(balls, isolated, 0, j);
        }
    }
    for (int i=0; i<11; i++) {
        for (int j=0; j<11; j++) {
            if (!isolated[i][j]) {
                balls[i][j] = 0;
            }
        }
    }
    return 0;
}

int gameover(SDL_Renderer *renderer, SDL_Texture * gameover_texture, Mix_Music * gameover_music, int time) {

    final_score *= 10;
    final_score -= shoot_count;
    final_score -= 8*time;

    if (final_score < 0) {
        final_score = 0;
    }

    fstream scores_file;
    scores_file.open(scores_path.c_str(), ios::app);
    if (scores_file.good()) {
        scores_file<<final_score<<" ";
    }
    scores_file.close();

    Mix_PauseMusic();
    Mix_PlayMusic(gameover_music, 0);

    SDL_RenderCopy(renderer, gameover_texture, NULL, NULL);
    string f_score = to_string(final_score);
    display_centered_text(renderer, 500, 400, 250, 250, f_score, 2, 2);
    SDL_RenderPresent(renderer);

    final_score = 0;

    SDL_Event * event = new SDL_Event();

    while(true) {
        if (SDL_PollEvent(event)) {
            if (event->type == SDL_MOUSEBUTTONDOWN) {
                return 0;
            }
        }
    }

}

int gamewin(SDL_Renderer *renderer, SDL_Texture * win_texture, Mix_Music * win_music, int time) {

    final_score *= 10;
    final_score -= shoot_count;
    final_score -= 8*time;

    if (final_score < 0) {
        final_score = 0;
    }

    fstream scores_file;
    scores_file.open(scores_path.c_str(), ios::app);
    if (scores_file.good()) {
        scores_file<<final_score<<" ";
    }
    scores_file.close();

    Mix_PauseMusic();
    Mix_PlayMusic(win_music, 0);

    SDL_RenderCopy(renderer, win_texture, NULL, NULL);

    string f_score = to_string(final_score);
    display_centered_text(renderer, 500, 400, 250, 250, f_score, 1, 3);

    final_score = 0;

    SDL_RenderPresent(renderer);

    SDL_Event * event = new SDL_Event();

    while(true) {
        if (SDL_PollEvent(event)) {
            if (event->type == SDL_MOUSEBUTTONDOWN) {
                return 0;
            }
        }
    }

}

int random_shooting_ball_color() {
    return (rand() % 6) + 1;
}

int menu_functions(SDL_Renderer * m_renderer, SDL_Texture * menu_texture, SDL_Texture * scores_texture, SDL_Texture * settings_texture, SDL_Window * m_window, Mix_Music * music1, Mix_Music * music2, SDL_Texture * login_texture, SDL_Texture * theme1_texture, SDL_Texture * theme2_texture, SDL_Texture * pause_menu_texture, Mix_Music * gameover_music, SDL_Texture * gameover_texture, Mix_Chunk * hit_soundeffect, SDL_Texture * win_texture, Mix_Music * win_music) {

    int where_to_go = 0, game_state=0;
    int where_to_go_setting = 3;

    where_to_go = menu(m_renderer, menu_texture);
    while(where_to_go != 1) {
        if (where_to_go == 2) {
            score(m_renderer, scores_texture);
            where_to_go = menu(m_renderer, menu_texture);
            continue;
        }
        else if (where_to_go == 3) {
            where_to_go_setting = setting_menu(m_renderer, settings_texture, music1, music2, theme, hit_soundeffect);
            while (where_to_go_setting != 1) {
                where_to_go_setting = setting_menu(m_renderer, settings_texture, music1, music2, theme, hit_soundeffect);
            }
            where_to_go = menu(m_renderer, menu_texture);
            continue;
        }

        //TO EXIT THE GAME
        else if (where_to_go == -1) {
            SDL_DestroyWindow(m_window);
            SDL_DestroyRenderer(m_renderer);
            IMG_Quit();
            SDL_Quit();
            game_state = -1;
            break;
        }
    }
    //GAME LOGIN & START----------------------------------------------------------------------

    int game_mode;

    if (where_to_go == 1) {

        game_mode = login(m_renderer, login_texture);

        if (game_mode == 1) {

            if (theme == 1) {
                game_state = game_normal(m_renderer, theme1_texture, theme, pause_menu_texture, music1, music2, gameover_music, gameover_texture, hit_soundeffect, win_texture, win_music);
            }

            else if (theme == 2) {
                game_state = game_normal(m_renderer, theme2_texture, theme, pause_menu_texture, music1, music2, gameover_music, gameover_texture, hit_soundeffect, win_texture, win_music);
            }

        }

        else if (game_mode == 2) {

            if (theme == 1) {
                game_state = game_infinite(m_renderer, theme1_texture, theme, pause_menu_texture, music1, music2, gameover_music, gameover_texture, hit_soundeffect);
            }

            else if (theme == 2) {
                game_state = game_infinite(m_renderer, theme2_texture, theme, pause_menu_texture, music1, music2, gameover_music, gameover_texture, hit_soundeffect);
            }

        }

        else {

            if (theme == 1) {
                game_state = game_time(m_renderer, theme1_texture, theme, pause_menu_texture, music1, music2, gameover_music, gameover_texture, hit_soundeffect, win_texture, win_music);
            }

            else if (theme == 2) {
                game_state = game_time(m_renderer, theme2_texture, theme, pause_menu_texture, music1, music2, gameover_music, gameover_texture, hit_soundeffect, win_texture, win_music);
            }

        }

    }

    //GAME LOGIN & START----------------------------------------------------------------------

    if (game_state == 1) {
        return 1;
    }
    else {
        return -1;
    }

}

int pause_menu (SDL_Renderer * renderer, SDL_Texture * pause_menu_texture, Mix_Music * music1, Mix_Music * music2, Mix_Chunk * hit_soundeffect) {

    SDL_Event * event = new SDL_Event();

    //TEXTURE LOADING----------------------------------------------------------------------

    SDL_RenderCopy(renderer, pause_menu_texture, NULL, NULL);
    SDL_RenderPresent(renderer);

    //TEXTURE LOADING----------------------------------------------------------------------

    bool menu_enter = false;
    bool mute = false, unmute = false;
    bool volume_up = false, volume_down = false;
    static bool effect = false;

    int x_m, y_m;

    while (!menu_enter) {

        Mix_VolumeMusic(volume);

        SDL_GetMouseState(&x_m, &y_m);

        if (x_m >= 578 && x_m <= 578 + 30 && y_m >= 312 && y_m <= 312 + 30) {
            if (SDL_PollEvent(event)) {
                if (event -> type == SDL_MOUSEBUTTONDOWN) {
                    if (effect) {
                        effect = false;
                    }
                    else {
                        effect = true;
                    }
                }
                else {
                    continue;
                }
            }
            else {
                continue;
            }
        }

        if (effect) {

            rect(renderer, 581, 318, 30, 24, red.r, red.g, red.b, 1);
            SDL_RenderPresent(renderer);

        }

        else {

            rect(renderer, 581, 318, 30, 24, white.r, white.g, white.b, 1);
            SDL_RenderPresent(renderer);

        }

        if (x_m >= 500 && x_m <= 500 + 139 && y_m >= 404 && y_m <= 404 + 88) {
            if (SDL_PollEvent(event)) {
                if (event -> type == SDL_MOUSEBUTTONDOWN) {
                    rect(renderer, 520, 400, 120, 94, red.r, red.g, red.b, 1);
                    SDL_RenderPresent(renderer);
                    SDL_Delay(100);
                    mute = true;
                }
                else {
                    continue;
                }
            }
            else {
                continue;
            }
        }

        if (x_m >= 361 && x_m <= 361 + 139 && y_m >= 404 && y_m <= 404 + 88) {
            if (SDL_PollEvent(event)) {
                if (event -> type == SDL_MOUSEBUTTONDOWN) {
                    rect(renderer, 361, 400, 110, 94, green.r, green.g, green.b, 1);
                    SDL_RenderPresent(renderer);
                    SDL_Delay(100);
                    unmute = true;
                }
                else {
                    continue;
                }
            }
            else {
                continue;
            }
        }

        if (x_m >= 357 && x_m <= 357 + 143 && y_m >= 507 && y_m <= 507 + 116) {
            if (SDL_PollEvent(event)) {
                if (event -> type == SDL_MOUSEBUTTONDOWN) {
                    rect(renderer, 357, 520, 110, 90, red.r, red.g, red.b, 1);
                    SDL_RenderPresent(renderer);
                    SDL_Delay(100);
                    volume_down = true;
                }
                else {
                    continue;
                }
            }
            else {
                continue;
            }
        }

        if (x_m >= 500 && x_m <= 500 + 143 && y_m >= 507 && y_m <= 507 + 116) {
            if (SDL_PollEvent(event)) {
                if (event -> type == SDL_MOUSEBUTTONDOWN) {
                    rect(renderer, 515, 505, 130, 120, green.r, green.g, green.b, 1);
                    SDL_RenderPresent(renderer);
                    SDL_Delay(100);
                    volume_up = true;
                }
                else {
                    continue;
                }
            }
            else {
                continue;
            }
        }

        if (x_m >= 306 && x_m <= 306 + 178 && y_m >= 670 && y_m <= 670 + 102) {
            if (SDL_PollEvent(event)) {
                if (event -> type == SDL_MOUSEBUTTONDOWN) {
                    rect(renderer, 306, 670, 178, 102, orange.r, orange.g, orange.b, 1);
                    SDL_RenderPresent(renderer);
                    SDL_Delay(100);
                    music1_int = 1;
                }
                else {
                    continue;
                }
            }
            else {
                continue;
            }
        }

        if (x_m >= 518 && x_m <= 518 + 178 && y_m >= 671 && y_m <= 671 + 102) {
            if (SDL_PollEvent(event)) {
                if (event -> type == SDL_MOUSEBUTTONDOWN) {
                    rect(renderer, 518, 671, 178, 102, orange.r, orange.g, orange.b, 1);
                    SDL_RenderPresent(renderer);
                    SDL_Delay(100);
                    music2_int = 1;
                }
                else {
                    continue;
                }
            }
            else {
                continue;
            }
        }

        //invisible_button(renderer, 30, 875, 191, 88, menu_enter, true, green.r, green.g, green.b);

        if (x_m >= 30 && x_m <= 30 + 191 && y_m >= 875 && y_m <= 875 + 88) {
            if (SDL_PollEvent(event)) {
                if (event -> type == SDL_MOUSEBUTTONDOWN) {
                    rect(renderer, 30, 875, 191, 88, green.r, green.g, green.b, 1);
                    SDL_RenderPresent(renderer);
                    SDL_Delay(100);
                    menu_enter = true;
                }
                else {
                    continue;
                }
            }
            else {
                continue;
            }
        }


        if (!effect) {
            if (mute) {
                if (volume != 0) {
                    volume_saved = volume;
                }
                volume = 0;
                Mix_VolumeMusic(volume);
                return 0;
            }
            else if (unmute) {
                if (volume == 0) {
                    volume = volume_saved;
                }
                Mix_VolumeMusic(volume);
                return 0;
            }
            else if (volume_up) {
                volume += 10;
                Mix_VolumeMusic(volume);
                return 0;
            }
            else if (volume_down) {
                if (volume >= 10) {
                    volume -= 10;
                }
                Mix_VolumeMusic(volume);
                return 0;
            }
        }

        else {
            if (mute) {
                if (effect_volume != 0) {
                    effect_volume_saved = effect_volume;
                }
                effect_volume = 0;
                Mix_VolumeChunk(hit_soundeffect, effect_volume);
                return 0;
            }
            else if (unmute) {
                if (effect_volume == 0) {
                    effect_volume = effect_volume_saved;
                }
                Mix_VolumeChunk(hit_soundeffect, effect_volume);
                return 0;
            }
            else if (volume_up) {
                effect_volume += 10;
                Mix_VolumeChunk(hit_soundeffect, effect_volume);
                return 0;
            }
            else if (volume_down) {
                if (effect_volume >= 10) {
                    effect_volume -= 10;
                }
                Mix_VolumeChunk(hit_soundeffect, effect_volume);
                return 0;
            }
        }

        if (music1_int) {
            Mix_PauseMusic();
            Mix_PlayMusic(music1, -1);
            music1_int = 0;
            return 0;
        }

        else if (music2_int) {
            Mix_PauseMusic();
            Mix_PlayMusic(music2, -1);
            music2_int = 0;
            return 0;
        }

        if (SDL_PollEvent(event)) {
            if (event -> type == SDL_KEYDOWN) {
                if (event -> key.keysym.sym == SDLK_ESCAPE) {

                    return -1;

                }
            }
        }
    }

    if (menu_enter) {
        fstream scores_file;
        scores_file.open(scores_path.c_str(), ios::app);
        if (scores_file.good()) {
            scores_file<<final_score<<" ";
        }
        scores_file.close();
        return 1;
    }
}
