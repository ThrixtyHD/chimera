#pragma once
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "boot.h"

struct Glyph
{
    SDL_FRect textureSrc{};
    SDL_FRect transform{};
    SDL_FRect backgroundSrc{};
    SDL_FRect backgroundTransform{};
    float positionX = 0;
    float positionY = 0;
    char character = 0;
};

class Camera;

class Label
{
public:
    Label() = default;
    std::vector<Label>* labels{};

    bool finishedCreatingLabel = false;

    enum LABEL_ORIGIN
    {
        LABEL_ORIGIN_TOP_LEFT,
        LABEL_ORIGIN_TOP_RIGHT,
        LABEL_ORIGIN_BOTTOM_LEFT,
        LABEL_ORIGIN_BOTTOM_RIGHT,
        LABEL_ORIGIN_TOP,
        LABEL_ORIGIN_BOTTOM,
        LABEL_ORIGIN_LEFT,
        LABEL_ORIGIN_RIGHT,
        LABEL_ORIGIN_CENTER,
    };

    LABEL_ORIGIN labelOrigin = LABEL_ORIGIN_TOP_LEFT;

    enum LABEL_ALIGNMENT
    {
        LABEL_ALIGNMENT_STANDARD,
        LABEL_ALIGNMENT_CENTER,
    };

    enum LABEL_TYPE
    {
        LABEL_TYPE_DEBUG,
        LABEL_TYPE_DEBUG_BACKGROUND,
        LABEL_TYPE_NORMAL,
    };


    enum LABEL_COLOR
    {
        LABEL_COLOR_RED,
        LABEL_COLOR_GREEN,
        LABEL_COLOR_BLUE,
        LABEL_COLOR_YELLOW,
        LABEL_COLOR_WHITE,
        LABEL_COLOR_BLACK,
        LABEL_COLOR_MAGENTA,
        LABEL_COLOR_CYAN,
    };

    enum LABEL_FILTER
    {
        LABEL_FILTER_BILINEAR,
        LABEL_FILTER_NEAREST_NEIGHBOUR,
    };
    SDL_State* state = nullptr;
    Camera* camera = nullptr;

    bool cameraBased = false;

    SDL_Texture* texture;
    LABEL_TYPE labelType = LABEL_TYPE_NORMAL;
    LABEL_COLOR labelColor = LABEL_COLOR_WHITE;
    LABEL_FILTER labelFilter = LABEL_FILTER_BILINEAR;

    //SDL_Texture* texture;
    SDL_Texture* textureShadow;
    std::vector<Glyph> glyphs;
    std::vector<Glyph> glyphs_Shadow;
    std::vector<Glyph> glyphs_Background; // might use idk
    // proprties
    std::string text = "<unassigned>";

    bool Visible = true;

    int charPositionX = 0;
    int charPositionY = 0;
    float positionX = 0;
    float positionY = 0;
    float fontSize = 8.0f;
    int fontColorR = 255;
    int fontColorG = 255;
    int fontColorB = 255;
    int fontColorA = 255;
    int fontBackgroundColorR = 0;
    int fontBackgroundColorG = 0;
    int fontBackgroundColorB = 0;
    int fontBackgroundColorA = 72;
    int fontShadowColorR = 0;
    int fontShadowColorG = 0;
    int fontShadowColorB = 0;
    int fontShadowColorA = 255;

    // BACKGROUND rect
    int charsSinceNewLine = 0;

    int shadowOffsetPositionX = 1;
    int shadowOffsetPositionY = 2;

    int preDeterminedNewLineCount = 1;
    int newLineCount = 1;


    int labelWidth = 0;
    // charHeight * newLineCount
    int labelHeight = 0;

    bool need_new_glyphs_to_be_generated = false;

    // FNT file support.
    // My idea is we read a file from the fonts folder.
    // The file path in the .fnt is relative to where the file is so ill force it into the fonts folder or make my own file format for it.

    int glyphPositionXTotal = 0;

    // the font will use the same height for all chars.
    int charHeight = 0;

    float newScale = 0.0f;

    float textureSrc_X = 0.0f;
    float textureSrc_Y = 0.0f;
    float textureSrc_W = 0.0f;
    float textureSrc_H = 0.0f;

    float transform_X = 0.0f;
    float transform_Y = 0.0f;
    float transform_W = 0.0f;
    float transform_H = 0.0f;

    // here im defining each char size of X. Its a long list of 32 - 126
    int char32X = 0;
    int char33X = 0;
    int char34X = 0;
    int char35X = 0;
    int char36X = 0;
    int char37X = 0;
    int char38X = 0;
    int char39X = 0;

    int char40X = 0;
    int char41X = 0;
    int char42X = 0;
    int char43X = 0;
    int char44X = 0;
    int char45X = 0;
    int char46X = 0;
    int char47X = 0;
    int char48X = 0;
    int char49X = 0;

    int char50X = 0;
    int char51X = 0;
    int char52X = 0;
    int char53X = 0;
    int char54X = 0;
    int char55X = 0;
    int char56X = 0;
    int char57X = 0;
    int char58X = 0;
    int char59X = 0;

    int char60X = 0;
    int char61X = 0;
    int char62X = 0;
    int char63X = 0;
    int char64X = 0;
    int char65X = 0;
    int char66X = 0;
    int char67X = 0;
    int char68X = 0;
    int char69X = 0;

    int char70X = 0;
    int char71X = 0;
    int char72X = 0;
    int char73X = 0;
    int char74X = 0;
    int char75X = 0;
    int char76X = 0;
    int char77X = 0;
    int char78X = 0;
    int char79X = 0;

    int char80X = 0;
    int char81X = 0;
    int char82X = 0;
    int char83X = 0;
    int char84X = 0;
    int char85X = 0;
    int char86X = 0;
    int char87X = 0;
    int char88X = 0;
    int char89X = 0;

    int char90X = 0;
    int char91X = 0;
    int char92X = 0;
    int char93X = 0;
    int char94X = 0;
    int char95X = 0;
    int char96X = 0;
    int char97X = 0;
    int char98X = 0;
    int char99X = 0;

    int char100X = 0;
    int char101X = 0;
    int char102X = 0;
    int char103X = 0;
    int char104X = 0;
    int char105X = 0;
    int char106X = 0;
    int char107X = 0;
    int char108X = 0;
    int char109X = 0;

    int char110X = 0;
    int char111X = 0;
    int char112X = 0;
    int char113X = 0;
    int char114X = 0;
    int char115X = 0;
    int char116X = 0;
    int char117X = 0;
    int char118X = 0;
    int char119X = 0;

    int char120X = 0;
    int char121X = 0;
    int char122X = 0;
    int char123X = 0;
    int char124X = 0;
    int char125X = 0;
    int char126X = 0;

    // here im defining each char size of X. Its a long list of 32 - 126
    int char32Width = 0;
    int char33Width = 0;
    int char34Width = 0;
    int char35Width = 0;
    int char36Width = 0;
    int char37Width = 0;
    int char38Width = 0;
    int char39Width = 0;

    int char40Width = 0;
    int char41Width = 0;
    int char42Width = 0;
    int char43Width = 0;
    int char44Width = 0;
    int char45Width = 0;
    int char46Width = 0;
    int char47Width = 0;
    int char48Width = 0;
    int char49Width = 0;

    int char50Width = 0;
    int char51Width = 0;
    int char52Width = 0;
    int char53Width = 0;
    int char54Width = 0;
    int char55Width = 0;
    int char56Width = 0;
    int char57Width = 0;
    int char58Width = 0;
    int char59Width = 0;

    int char60Width = 0;
    int char61Width = 0;
    int char62Width = 0;
    int char63Width = 0;
    int char64Width = 0;
    int char65Width = 0;
    int char66Width = 0;
    int char67Width = 0;
    int char68Width = 0;
    int char69Width = 0;

    int char70Width = 0;
    int char71Width = 0;
    int char72Width = 0;
    int char73Width = 0;
    int char74Width = 0;
    int char75Width = 0;
    int char76Width = 0;
    int char77Width = 0;
    int char78Width = 0;
    int char79Width = 0;

    int char80Width = 0;
    int char81Width = 0;
    int char82Width = 0;
    int char83Width = 0;
    int char84Width = 0;
    int char85Width = 0;
    int char86Width = 0;
    int char87Width = 0;
    int char88Width = 0;
    int char89Width = 0;

    int char90Width = 0;
    int char91Width = 0;
    int char92Width = 0;
    int char93Width = 0;
    int char94Width = 0;
    int char95Width = 0;
    int char96Width = 0;
    int char97Width = 0;
    int char98Width = 0;
    int char99Width = 0;

    int char100Width = 0;
    int char101Width = 0;
    int char102Width = 0;
    int char103Width = 0;
    int char104Width = 0;
    int char105Width = 0;
    int char106Width = 0;
    int char107Width = 0;
    int char108Width = 0;
    int char109Width = 0;

    int char110Width = 0;
    int char111Width = 0;
    int char112Width = 0;
    int char113Width = 0;
    int char114Width = 0;
    int char115Width = 0;
    int char116Width = 0;
    int char117Width = 0;
    int char118Width = 0;
    int char119Width = 0;

    int char120Width = 0;
    int char121Width = 0;
    int char122Width = 0;
    int char123Width = 0;
    int char124Width = 0;
    int char125Width = 0;
    int char126Width = 0;

	void Create();
    void SetState(SDL_State& state_);
	void SetText(std::string newText);
    void SetCameraBased();
	void GenerateGlyphs();
	void SetFont(LABEL_TYPE type, std::string filepath);
    void SetFilter(LABEL_FILTER filter);
	void SetColorRGB(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    void SetColorEnum(LABEL_COLOR color);
	void SetShadowColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    void Position(int x, int y);
	void Render();
	void Clear();
	void Destroy();
	void GenerateGlyphBasedOnChar(char input, int index);
    void SetSize(float size);
    void Show();
    void Hide();

    // Regarding origin, maybe i can determine the longest line in the label as the xTotal. when i ccreate a new line, thats when i store the value.
    // And i should record the amount of lines in the label. so i can figure out center and bottom orientation.
    void SetOrigin(LABEL_ORIGIN origin);

    void LoadCFNT(std::string filepath);
    void PositionCFNT(int x, int y);
    void GenerateGlyphsCFNT();
    void GenerateGlyphBasedOnCharCFNT(char input, int index);
    void SetTextCFNT(std::string newText);
    void CalculateCharXValueCFNT();
    void SetCamera(Camera& camera_);
    void UpdateTransform();
};