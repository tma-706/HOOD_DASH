#ifndef DEF_H_INCLUDED
#define DEF_H_INCLUDED
constexpr int SCREEN_WIDTH = 700;
constexpr int SCREEN_HEIGHT = 520;
constexpr int GROUND_LEVEL = 54;
const int mainchar = 31;
const int velo = 10;
const double spriteRat = 2.5; //tỉ lệ nhân vật
const int enemyRat = 2;
const int appleRat = 3;
const int mainX = 50;


constexpr const char* WINDOW_NAME="GAME BTL";
//FILE BG
constexpr const char* BACKGROUND_IMG = "assets/Background.png";
//FILE BGMUSIC
constexpr const char* BGMUSIC = "assets/so-happy-with-my-8-bit-game-301275.mp3";
//TỌA ĐỘ MAIN
constexpr const char* MAIN_RUN = "assets/MAIN_RUN.png";
constexpr int MAIN_RUN_CLIPS[][4] = {
    {  0, 0, 31, 31},
    { 31, 0, 31, 31},
    { 62, 0, 31, 31},
    { 93, 0, 31, 31},
    {124, 0, 31, 31},
    {155, 0, 31, 31},
    {186, 0, 31, 31},
    {217, 0, 31, 31}};
constexpr int MAIN_RUN_FRAMES = sizeof(MAIN_RUN_CLIPS)/sizeof(int)/4;

constexpr const char* MAIN_JUMP = "assets/MAIN_JUMP.png";
constexpr int MAIN_JUMP_CLIPS[][4] = {
    {  0, 0, 31, 31},
    { 31, 0, 31, 31},
    { 62, 0, 31, 31},
    { 93, 0, 31, 31}};
constexpr int MAIN_JUMP_FRAMES = sizeof(MAIN_JUMP_CLIPS)/sizeof(int)/4;

constexpr const char* MAIN_FALL = "assets/MAIN_FALL.png";
constexpr int MAIN_FALL_CLIPS[][4] = {
    {  0, 0, 31, 31},
    { 31, 0, 31, 31},
    { 62, 0, 31, 31},
    { 93, 0, 31, 31}};
constexpr int MAIN_FALL_FRAMES = sizeof(MAIN_FALL_CLIPS)/sizeof(int)/4;

constexpr const char* EXPLODE = "assets/EXPLODE.png";
constexpr int EXPLODE_CLIPS[][4] = {
    {   0, 0, 128, 128},
    { 128, 0, 128, 128},
    { 256, 0, 128, 128},
    { 384, 0, 128, 128},
    { 512, 0, 128, 128},
    { 640, 0, 128, 128},
    { 768, 0, 128, 128},
    { 896, 0, 128, 128},
    {1024, 0, 128, 128},
    {1152, 0, 128, 128},
    {1280, 0, 128, 128},
    {1408, 0, 128, 128}};
constexpr int EXPLODE_FRAMES = sizeof(EXPLODE_CLIPS)/sizeof(int)/4;

constexpr const char* WARN = "assets/WARN.png";
constexpr int WARN_CLIPS[][4] = {
    {  0, 0, 32, 32},
    { 32, 0, 32, 32},
    { 64, 0, 32, 32},
    { 96, 0, 32, 32},
    {128, 0, 32, 32},
    {160, 0, 32, 32},
    {192, 0, 32, 32},
    {224, 0, 32, 32},
    {256, 0, 32, 32}};
constexpr int WARN_FRAMES = sizeof(WARN_CLIPS)/sizeof(int)/4;


//*************************************************************

//TỌA ĐỘ GOLEM, TÁO
constexpr const char* ORANGE_GOLEM = "assets/ORANGE_GOLEM.png";
constexpr const char* BLUE_GOLEM = "assets/BLUE_GOLEM.png";
constexpr const char* apple = "assets/apple.png";
constexpr const char* MISSILE = "assets/MISSILE.png";

#endif // DEF_H_INCLUDED
