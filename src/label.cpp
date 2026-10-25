#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <vector>
#include <iostream>
#include <string>
#include "label.h"
#include "camera.h"

void Label::Create()
{
    //std::cout << "[Create] Created a new label.\n";
}

void Label::SetState(SDL_State& state_)
{
    state = &state_;
}

void Label::SetFilter(LABEL_FILTER filter)
{
    if (filter == LABEL_FILTER_BILINEAR)
    {
        SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_LINEAR);
    }
    else if (filter == LABEL_FILTER_NEAREST_NEIGHBOUR)
    {
        SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
    }
}

void Label::SetOrigin(LABEL_ORIGIN origin)
{
    switch (origin)
    {
    case LABEL_ORIGIN_TOP_LEFT:
        labelOrigin = LABEL_ORIGIN_TOP_LEFT;
        break;
    case LABEL_ORIGIN_TOP_RIGHT:
        labelOrigin = LABEL_ORIGIN_TOP_RIGHT;
        break;
    case LABEL_ORIGIN_BOTTOM_LEFT:
        labelOrigin = LABEL_ORIGIN_BOTTOM_LEFT;
        break;
    case LABEL_ORIGIN_BOTTOM_RIGHT:
        labelOrigin = LABEL_ORIGIN_BOTTOM_RIGHT;
        break;
    case LABEL_ORIGIN_TOP:
        labelOrigin = LABEL_ORIGIN_TOP;
        break;
    case LABEL_ORIGIN_BOTTOM:
        labelOrigin = LABEL_ORIGIN_BOTTOM;
        break;
    case LABEL_ORIGIN_LEFT:
        labelOrigin = LABEL_ORIGIN_LEFT;
        break;
    case LABEL_ORIGIN_RIGHT:
        labelOrigin = LABEL_ORIGIN_RIGHT;
        break;
    case LABEL_ORIGIN_CENTER:
        labelOrigin = LABEL_ORIGIN_CENTER;
        break;
    }
}

void Label::UpdateTransform()
{
    int highestCharX = 0;

    for (int i = 0; i < glyphs.size(); i++)
    {
        float fullCharDimension = glyphs[i].positionX + glyphs[i].transform.w;

        if (highestCharX < fullCharDimension)
        {
            //std::cout << "[Label::SetText] new highest highestCharX is: " << highestCharX << ". Also, the last character should be: " << glyphs[i].character << "\n";
            if (glyphPositionXTotal != 0)
            {
            }

            highestCharX = fullCharDimension;

            //std::cout << "[Label::SetText] glyphs[" << i << "].positionX: " << glyphs[i].positionX << ".\n";
            //std::cout << "[Label::SetText] highestCharX: " << highestCharX << ".\n";

        }



        labelWidth = highestCharX;
    }


    for (int i = 0; i < glyphs.size(); i++)
    {
        switch (labelOrigin)
        {
        case Label::LABEL_ORIGIN_TOP_LEFT:
            if (camera != nullptr && cameraBased)
            {
                glyphs[i].transform.x = (positionX + glyphs[i].positionX) - camera->cameraPositionX;
                glyphs[i].transform.y = (positionY + glyphs[i].positionY) - camera->cameraPositionY;
            }
            else
            {
                glyphs[i].transform.x = (positionX + glyphs[i].positionX);
                glyphs[i].transform.y = (positionY + glyphs[i].positionY);
            }
            break;
        case Label::LABEL_ORIGIN_TOP_RIGHT:
            if (camera != nullptr && cameraBased)
            {
                glyphs[i].transform.x = ((positionX + glyphs[i].positionX) - labelWidth) - camera->cameraPositionX;
                glyphs[i].transform.y = (positionY + glyphs[i].positionY) - camera->cameraPositionY;
            }
            else
            {
                glyphs[i].transform.x = (positionX + glyphs[i].positionX) - labelWidth;
                glyphs[i].transform.y = (positionY + glyphs[i].positionY);
            }
            break;
        case Label::LABEL_ORIGIN_BOTTOM_LEFT:
            if (camera != nullptr && cameraBased)
            {
                glyphs[i].transform.x = (positionX + glyphs[i].positionX) - camera->cameraPositionX;
                glyphs[i].transform.y = ((positionY + glyphs[i].positionY) - labelHeight) - camera->cameraPositionY;
            }
            else
            {
                glyphs[i].transform.x = (positionX + glyphs[i].positionX);
                glyphs[i].transform.y = (positionY + glyphs[i].positionY) - labelHeight;
            }
            break;
        case Label::LABEL_ORIGIN_BOTTOM_RIGHT:
            if (camera != nullptr && cameraBased)
            {
                glyphs[i].transform.x = ((positionX + glyphs[i].positionX) - labelWidth) - camera->cameraPositionX;
                glyphs[i].transform.y = ((positionY + glyphs[i].positionY) - labelHeight) - camera->cameraPositionY;
            }
            else
            {
                glyphs[i].transform.x = (positionX + glyphs[i].positionX) - labelWidth;
                glyphs[i].transform.y = (positionY + glyphs[i].positionY) - labelHeight;
            }
            break;
        case Label::LABEL_ORIGIN_TOP:
            if (camera != nullptr && cameraBased)
            {
                glyphs[i].transform.x = ((positionX + glyphs[i].positionX) - (labelWidth / 2)) - camera->cameraPositionX;
                glyphs[i].transform.y = (positionY + glyphs[i].positionY) - camera->cameraPositionY;
            }
            else
            {
                glyphs[i].transform.x = (positionX + glyphs[i].positionX) - (labelWidth / 2);
                glyphs[i].transform.y = (positionY + glyphs[i].positionY);
            }
            break;
        case Label::LABEL_ORIGIN_BOTTOM:
            if (camera != nullptr && cameraBased)
            {
                glyphs[i].transform.x = ((positionX + glyphs[i].positionX) - (labelWidth / 2)) - camera->cameraPositionX;
                glyphs[i].transform.y = ((positionY + glyphs[i].positionY) - labelHeight) - camera->cameraPositionY;
            }
            else
            {
                glyphs[i].transform.x = (positionX + glyphs[i].positionX) - (labelWidth / 2);
                glyphs[i].transform.y = (positionY + glyphs[i].positionY) - labelHeight;
            }
            break;
        case Label::LABEL_ORIGIN_LEFT:
            if (camera != nullptr && cameraBased)
            {
                glyphs[i].transform.x = (positionX + glyphs[i].positionX) - camera->cameraPositionX;
                glyphs[i].transform.y = ((positionY + glyphs[i].positionY) - (labelHeight / 2)) - camera->cameraPositionY;
            }
            else
            {
                glyphs[i].transform.x = (positionX + glyphs[i].positionX);
                glyphs[i].transform.y = (positionY + glyphs[i].positionY) - (labelHeight / 2);
            }
            break;
        case Label::LABEL_ORIGIN_RIGHT:
            if (camera != nullptr && cameraBased)
            {
                glyphs[i].transform.x = ((positionX + glyphs[i].positionX) - labelWidth) - camera->cameraPositionX;
                glyphs[i].transform.y = ((positionY + glyphs[i].positionY) - (labelHeight / 2)) - camera->cameraPositionY;
            }
            else
            {
                glyphs[i].transform.x = (positionX + glyphs[i].positionX) - labelWidth;
                glyphs[i].transform.y = (positionY + glyphs[i].positionY) - (labelHeight / 2);
            }
            break;
        case Label::LABEL_ORIGIN_CENTER:
            if (camera != nullptr && cameraBased)
            {
                glyphs[i].transform.x = ((positionX + glyphs[i].positionX) - (labelWidth / 2)) - camera->cameraPositionX;
                glyphs[i].transform.y = ((positionY + glyphs[i].positionY) - (labelHeight / 2)) - camera->cameraPositionY;
            }
            else
            {
                glyphs[i].transform.x = (positionX + glyphs[i].positionX) - (labelWidth / 2);
                glyphs[i].transform.y = (positionY + glyphs[i].positionY) - (labelHeight / 2);
            }
            break;
        default:
            break;
        }
    }
}

void Label::SetText(std::string newText)
{
    // note this little system will not work if i later add autowrapping.
    // this relies on the hardcoded set text i want. it does nto include new lines added after. cuz its set before anything else.
    preDeterminedNewLineCount = 1;
    for (int i = 0; i < newText.size(); i++)
    {
        if (newText[i] == '\n')
        {
            preDeterminedNewLineCount++;
        }
    }

    

    labelHeight = charHeight * preDeterminedNewLineCount;

    if (labelType == LABEL_TYPE_DEBUG || labelType == LABEL_TYPE_DEBUG_BACKGROUND)
    {
        Clear();
        text = newText;
        need_new_glyphs_to_be_generated = false;
        GenerateGlyphs();
    }
    else if (labelType == LABEL_TYPE_NORMAL)
    {
        Clear();
        text = newText;
        need_new_glyphs_to_be_generated = false;
        GenerateGlyphsCFNT();
    }
    UpdateTransform();
}

void Label::GenerateGlyphs()
{
    newLineCount = 1;
    if (labelType == LABEL_TYPE_DEBUG || labelType == LABEL_TYPE_DEBUG_BACKGROUND)
    {
        if (!need_new_glyphs_to_be_generated)
        {
            // create glyphs for every char.
            // here is the main check func. for loop. every char, check the char and create a glyph.
            for (int i = 0; i < text.size(); i++)
            {
                // with every character check the char
                GenerateGlyphBasedOnChar(text[i], charsSinceNewLine);
                //std::cout << "[GenerateGlyphs] Generating new glyph: '" << text[charsSinceNewLine] << "'\n";
                //std::cout << "[GenerateGlyphs] Characters since new line: '" << charsSinceNewLine << "'\n";
                if (text[i] != '\n')
                {
                    charsSinceNewLine++;
                    //std::cout << "[GenerateGlyphs] Glyph is not newline!\n";
                }
                else
                {
                    charsSinceNewLine = 0;
                    newLineCount++;
                    //std::cout << "[GenerateGlyphs] Glyph is newline!\n";
                }


            }
            // theoretically after the forloop is done, we should be done with generating glyphs.
            need_new_glyphs_to_be_generated = true;
            //std::cout << "[GenerateGlyphs] Finished generating glyphs.\n";
        }
    }
    if (labelType == LABEL_TYPE_NORMAL)
    {
        if (!need_new_glyphs_to_be_generated)
        {
            // create glyphs for every char.
            // here is the main check func. for loop. every char, check the char and create a glyph.
            for (int i = 0; i < text.size(); i++)
            {
                // with every character check the char
                GenerateGlyphBasedOnCharCFNT(text[i], charsSinceNewLine);
                //std::cout << "[GenerateGlyphs] Generating new glyph: '" << text[charsSinceNewLine] << "'\n";
                //std::cout << "[GenerateGlyphs] Characters since new line: '" << charsSinceNewLine << "'\n";
                if (text[i] != '\n')
                {
                    charsSinceNewLine++;
                    //std::cout << "[GenerateGlyphs] Glyph is not newline!\n";
                }
                else
                {
                    charsSinceNewLine = 0;
                    //std::cout << "[GenerateGlyphs] Glyph is newline!\n";
                }


            }
            // theoretically after the forloop is done, we should be done with generating glyphs.
            need_new_glyphs_to_be_generated = true;
            glyphPositionXTotal = 0;
            //std::cout << "[GenerateGlyphs] Finished generating glyphs.\n";
        }
    }
    
}

void Label::SetFont(LABEL_TYPE type, std::string filepath)
{
    labelType = type;
    if (labelType == LABEL_TYPE_DEBUG || labelType == LABEL_TYPE_DEBUG_BACKGROUND)
    {
        // we use a hardcoded set path to debug. if its a debug type, we leave the path param unused.
        std::string texturePath = "textures/fonts/debug.png";
        texture = IMG_LoadTexture(state->renderer, texturePath.c_str());
        textureShadow = IMG_LoadTexture(state->renderer, texturePath.c_str());
        if (!texture)
        {
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "texture null reference", nullptr);
        }
        if (!textureShadow)
        {
            std::string errorString = "textureShadow null reference. path: " + texturePath + "";
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", errorString.c_str(), nullptr);
        }
        SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    }
    

    // we use the line index to check whats in the line. hardcoded 32 to 126 cuz i dont plan to ever do localisation.
    else if (labelType == LABEL_TYPE_NORMAL)
    {
        int cfontFileLineIndex = 0;

        std::string fullFilePath = "fonts/" + filepath + ".cfnt";
        std::ifstream fileInput(fullFilePath);
        if (!fileInput.is_open())
        {
            //std::cout << "[Level::GenerateTiles] Error: Failed to open '" + fullFilePath + "'";
            return;
        }

        std::string test;
        // Read each line from the file and print it
        while (getline(fileInput, test))
        {
            // checks each line using na index.
            //std::cout << "[Label::LoadFNT] cfontFileLineIndex: '" << cfontFileLineIndex << "'\n";
            if (cfontFileLineIndex == 0)
            {
                charHeight = stoi(test);
                fontSize = charHeight;
                //std::cout << "[Label::LoadFNT] test (AKA charHeight): '" << test << "'\n";
            }
            if (cfontFileLineIndex == 1)
            {
                char32Width = stoi(test);
                //std::cout << "[Label::LoadFNT] char32Width: '" << char32Width << "'\n";

            }
            if (cfontFileLineIndex == 2)
            {
                char33Width = stoi(test);
                //std::cout << "[Label::LoadFNT] char33Width: '" << char33Width << "'\n";
            }
            if (cfontFileLineIndex == 3)
            {
                char34Width = stoi(test);
                //std::cout << "[Label::LoadFNT] char34Width: '" << char34Width << "'\n";
            }
            if (cfontFileLineIndex == 4)
            {
                char35Width = stoi(test);
                //std::cout << "[Label::LoadFNT] char35Width: '" << char35Width << "'\n";
            }
            if (cfontFileLineIndex == 5)
            {
                char36Width = stoi(test);
            }
            if (cfontFileLineIndex == 6)
            {
                char37Width = stoi(test);
            }

            if (cfontFileLineIndex == 7)
            {
                char38Width = stoi(test);
            }
            if (cfontFileLineIndex == 8)
            {
                char39Width = stoi(test);
            }
            if (cfontFileLineIndex == 9)
            {
                char40Width = stoi(test);
            }

            if (cfontFileLineIndex == 10)
            {
                char41Width = stoi(test);
            }

            if (cfontFileLineIndex == 11)
            {
                char42Width = stoi(test);
            }

            if (cfontFileLineIndex == 12)
            {
                char43Width = stoi(test);
            }

            if (cfontFileLineIndex == 13)
            {
                char44Width = stoi(test);
            }

            if (cfontFileLineIndex == 14)
            {
                char45Width = stoi(test);
            }

            if (cfontFileLineIndex == 15)
            {
                char46Width = stoi(test);
            }

            if (cfontFileLineIndex == 16)
            {
                char47Width = stoi(test);
            }

            if (cfontFileLineIndex == 17)
            {
                char48Width = stoi(test);
            }

            if (cfontFileLineIndex == 18)
            {
                char49Width = stoi(test);
            }

            if (cfontFileLineIndex == 19)
            {
                char50Width = stoi(test);
            }

            if (cfontFileLineIndex == 20)
            {
                char51Width = stoi(test);
            }

            if (cfontFileLineIndex == 21)
            {
                char52Width = stoi(test);
            }

            if (cfontFileLineIndex == 22)
            {
                char53Width = stoi(test);
            }

            if (cfontFileLineIndex == 23)
            {
                char54Width = stoi(test);
            }

            if (cfontFileLineIndex == 24)
            {
                char55Width = stoi(test);
            }

            if (cfontFileLineIndex == 25)
            {
                char56Width = stoi(test);
            }

            if (cfontFileLineIndex == 26)
            {
                char57Width = stoi(test);
            }

            if (cfontFileLineIndex == 27)
            {
                char58Width = stoi(test);
            }

            if (cfontFileLineIndex == 28)
            {
                char59Width = stoi(test);
            }

            if (cfontFileLineIndex == 29)
            {
                char60Width = stoi(test);
            }

            if (cfontFileLineIndex == 30)
            {
                char61Width = stoi(test);
            }

            if (cfontFileLineIndex == 31)
            {
                char62Width = stoi(test);
            }

            if (cfontFileLineIndex == 32)
            {
                char63Width = stoi(test);
            }

            if (cfontFileLineIndex == 33)
            {
                char64Width = stoi(test);
            }

            if (cfontFileLineIndex == 34)
            {
                char65Width = stoi(test);
            }

            if (cfontFileLineIndex == 35)
            {
                char66Width = stoi(test);
            }

            if (cfontFileLineIndex == 36)
            {
                char67Width = stoi(test);
            }

            if (cfontFileLineIndex == 37)
            {
                char68Width = stoi(test);
            }

            if (cfontFileLineIndex == 38)
            {
                char69Width = stoi(test);
            }

            if (cfontFileLineIndex == 39)
            {
                char70Width = stoi(test);
            }

            if (cfontFileLineIndex == 40)
            {
                char71Width = stoi(test);
            }

            if (cfontFileLineIndex == 41)
            {
                char72Width = stoi(test);
            }

            if (cfontFileLineIndex == 42)
            {
                char73Width = stoi(test);
            }

            if (cfontFileLineIndex == 43)
            {
                char74Width = stoi(test);
            }

            if (cfontFileLineIndex == 44)
            {
                char75Width = stoi(test);
            }

            if (cfontFileLineIndex == 45)
            {
                char76Width = stoi(test);
            }

            if (cfontFileLineIndex == 46)
            {
                char77Width = stoi(test);
            }

            if (cfontFileLineIndex == 47)
            {
                char78Width = stoi(test);
            }

            if (cfontFileLineIndex == 48)
            {
                char79Width = stoi(test);
            }

            if (cfontFileLineIndex == 49)
            {
                char80Width = stoi(test);
            }

            if (cfontFileLineIndex == 50)
            {
                char81Width = stoi(test);
            }

            if (cfontFileLineIndex == 51)
            {
                char82Width = stoi(test);
            }

            if (cfontFileLineIndex == 52)
            {
                char83Width = stoi(test);
            }

            if (cfontFileLineIndex == 53)
            {
                char84Width = stoi(test);
            }

            if (cfontFileLineIndex == 54)
            {
                char85Width = stoi(test);
            }

            if (cfontFileLineIndex == 55)
            {
                char86Width = stoi(test);
            }

            if (cfontFileLineIndex == 56)
            {
                char87Width = stoi(test);
            }

            if (cfontFileLineIndex == 57)
            {
                char88Width = stoi(test);
            }

            if (cfontFileLineIndex == 58)
            {
                char89Width = stoi(test);
            }

            if (cfontFileLineIndex == 59)
            {
                char90Width = stoi(test);
            }

            if (cfontFileLineIndex == 60)
            {
                char91Width = stoi(test);
            }

            if (cfontFileLineIndex == 61)
            {
                char92Width = stoi(test);
            }

            if (cfontFileLineIndex == 62)
            {
                char93Width = stoi(test);
            }

            if (cfontFileLineIndex == 63)
            {
                char94Width = stoi(test);
            }

            if (cfontFileLineIndex == 64)
            {
                char95Width = stoi(test);
            }

            if (cfontFileLineIndex == 65)
            {
                char96Width = stoi(test);
            }

            if (cfontFileLineIndex == 66)
            {
                char97Width = stoi(test);
            }

            if (cfontFileLineIndex == 67)
            {
                char98Width = stoi(test);
            }

            if (cfontFileLineIndex == 68)
            {
                char99Width = stoi(test);
            }

            if (cfontFileLineIndex == 69)
            {
                char100Width = stoi(test);
            }

            if (cfontFileLineIndex == 70)
            {
                char101Width = stoi(test);
            }

            if (cfontFileLineIndex == 71)
            {
                char102Width = stoi(test);
            }

            if (cfontFileLineIndex == 72)
            {
                char103Width = stoi(test);
            }

            if (cfontFileLineIndex == 73)
            {
                char104Width = stoi(test);
            }

            if (cfontFileLineIndex == 74)
            {
                char105Width = stoi(test);
            }

            if (cfontFileLineIndex == 75)
            {
                char106Width = stoi(test);
            }

            if (cfontFileLineIndex == 76)
            {
                char107Width = stoi(test);
            }

            if (cfontFileLineIndex == 77)
            {
                char108Width = stoi(test);
            }

            if (cfontFileLineIndex == 78)
            {
                char109Width = stoi(test);
            }

            if (cfontFileLineIndex == 79)
            {
                char110Width = stoi(test);
            }

            if (cfontFileLineIndex == 80)
            {
                char111Width = stoi(test);
            }

            if (cfontFileLineIndex == 81)
            {
                char112Width = stoi(test);
            }

            if (cfontFileLineIndex == 82)
            {
                char113Width = stoi(test);
            }

            if (cfontFileLineIndex == 83)
            {
                char114Width = stoi(test);
            }

            if (cfontFileLineIndex == 84)
            {
                char115Width = stoi(test);
            }

            if (cfontFileLineIndex == 85)
            {
                char116Width = stoi(test);
            }

            if (cfontFileLineIndex == 86)
            {
                char117Width = stoi(test);
            }

            if (cfontFileLineIndex == 87)
            {
                char118Width = stoi(test);
            }

            if (cfontFileLineIndex == 88)
            {
                char119Width = stoi(test);
            }

            if (cfontFileLineIndex == 89)
            {
                char120Width = stoi(test);
            }

            if (cfontFileLineIndex == 90)
            {
                char121Width = stoi(test);
            }

            if (cfontFileLineIndex == 91)
            {
                char122Width = stoi(test);
            }

            if (cfontFileLineIndex == 92)
            {
                char123Width = stoi(test);
            }

            if (cfontFileLineIndex == 93)
            {
                char124Width = stoi(test);
            }

            if (cfontFileLineIndex == 94)
            {
                char125Width = stoi(test);
            }

            if (cfontFileLineIndex == 95)
            {
                char126Width = stoi(test);
            }
            cfontFileLineIndex++;


            // line 0 or 1 if starting at 0, is line 32's width. so lets grab it and set the width ints.


            // Process each line as needed

            // so this checks each line. if i can do an index, that would be good. WAIT
            //if (test == "a")
            //{
            //    std::cout << "[Label::LoadFNT] '" << test << "' has the char 'a' " << std::endl;
            //}
        }

        // Always close the file when done
        fileInput.close();

        std::string texturePath = "fonts/" + filepath + ".png";
        texture = IMG_LoadTexture(state->renderer, texturePath.c_str());
        textureShadow = IMG_LoadTexture(state->renderer, texturePath.c_str());
        if (!texture)
        {
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "texture null reference", nullptr);
        }
        if (!textureShadow)
        {
            std::string errorString = "textureShadow null reference. path: " + texturePath + "";
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", errorString.c_str(), nullptr);
        }
        SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);





        // i need to calculate the fontsize before this!!!!!!!!!!!!
        // after loading the font, we set its glyph properties.
    }
}

void Label::SetColorRGB(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    for (int i = 0; i < glyphs.size(); i++)
    {
        SDL_SetTextureColorMod(texture, r, g, b);
        SDL_SetTextureAlphaMod(texture, a);
    }
}

void Label::SetColorEnum(LABEL_COLOR color)
{
    Uint8 r = 255;
    Uint8 g = 255;
    Uint8 b = 255;
    Uint8 a = 255;
    switch (color)
    {
        case LABEL_COLOR_RED:
            r = 255;
            g = 0;
            b = 0;
            a = 255;
            break;
        case LABEL_COLOR_GREEN:
            r = 0;
            g = 255;
            b = 0;
            a = 255;
            break;
        case LABEL_COLOR_BLUE:
            r = 0;
            g = 0;
            b = 255;
            a = 255;
            break;
        case LABEL_COLOR_YELLOW:
            r = 255;
            g = 255;
            b = 0;
            a = 255;
            break;
        case LABEL_COLOR_WHITE:
            r = 255;
            g = 255;
            b = 255;
            a = 255;
            break;
        case LABEL_COLOR_BLACK:
            r = 0;
            g = 0;
            b = 0;
            a = 255;
            break;
        case LABEL_COLOR_MAGENTA:
            r = 255;
            g = 0;
            b = 255;
            a = 255;
            break;
        case LABEL_COLOR_CYAN:
            r = 0;
            g = 255;
            b = 255;
            a = 255;
            break;
        default:
            break;
    }
    
    for (int i = 0; i < glyphs.size(); i++)
    {
        SDL_SetTextureColorMod(texture, r, g, b);
    }
}

void Label::SetShadowColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    /*
    if (labelType == LABEL_TYPE_SHADOW)
    {
        for (int i = 0; i < glyphs_Shadow.size(); i++)
        {
            SDL_SetTextureColorMod(textureShadow, r, g, b);
        }
    }
    */
}

void Label::SetSize(float size)
{
    newScale = size / charHeight;
    charHeight = size;
    fontSize = size;
    std::cout << "[Label::SetSize] newScale: " << newScale << "\n";

    CalculateCharXValueCFNT();

    // so the fontSize calc for height is (e.g 12) figuring out the base which is 12.
    // lets say i want it 24, thats *2. so its whatever is the different of base height multiplied to the new height.

    // new / base = newScale.
    // size / charHeight = fontSize;

}

void Label::Show()
{
    Visible = true;
}

void Label::Hide()
{
    Visible = false;
}

void Label::Render()
{
    if (Visible)
    {
        /*
    // render shadow first
    if (labelType == LABEL_TYPE_SHADOW)
    {
        for (int i = 0; i < glyphs_Shadow.size(); i++)
        {
            SDL_RenderTexture(state.renderer, textureShadow, &glyphs_Shadow[i].textureSrc, &glyphs_Shadow[i].transform);
        }
    }
    */

    // render the background first.
        if (labelType == LABEL_TYPE_DEBUG_BACKGROUND)
        {
            for (int i = 0; i < glyphs.size(); i++)
            {
                SDL_SetRenderDrawBlendMode(state->renderer, SDL_BLENDMODE_BLEND);
                SDL_SetRenderDrawColor(state->renderer, fontBackgroundColorR, fontBackgroundColorG, fontBackgroundColorB, fontBackgroundColorA);
                SDL_RenderFillRect(state->renderer, &glyphs[i].transform);
                if (!SDL_RenderFillRect(state->renderer, &glyphs[i].transform))
                {
                    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Failed to create texture.", nullptr);
                }
            }
        }


        // finally readjust each glyph (basically the entire label)
        for (int i = 0; i < glyphs.size(); i++)
        {


            SDL_RenderTexture(state->renderer, texture, &glyphs[i].textureSrc, &glyphs[i].transform);
        }

        //std::cout << "[Label::Render] new line var idk what its called: " << newLineCount << ".\n";
        //std::cout << "[Label::Render] labelHeight: " << labelHeight << ".\n";
    }
}

void Label::Clear()
{
    text = "";
    charsSinceNewLine = 0;
    glyphs.clear();
    /*
    if (labelType == LABEL_TYPE_SHADOW)
    {
        glyphs_Shadow.clear();
    }
    */
    charPositionY = 0;
}

void Label::Position(int x, int y)
{
    positionX = x;
    positionY = y;
    UpdateTransform();
}

void Label::Destroy()
{
    std::cout << "[Create] Destroyed label.\n";
}

// reallt badly done but who cares.
void Label::GenerateGlyphBasedOnChar(char input, int index)
{
    Glyph newGlyph;
    Glyph newGlyphShadow;

    // monospace size 8 so height is always 8.
    // theoreticaly this should work for any character in ascii from that range.
    if (input == 0x0A)
    {
        // newline with it starts at the beginning of the line.
        index = 0;
        // newline sets it a new line down.
        charPositionY += 8;
        
    }

    if (input > 0 && input < 255)
    {
        newGlyph.textureSrc.x = (input - 32) * 8;
        newGlyph.textureSrc.y = 0;
        newGlyph.textureSrc.w = 8;
        newGlyph.textureSrc.h = 8;

        newGlyph.positionX = index * fontSize;
        newGlyph.positionY = charPositionY;
        newGlyph.transform.w = fontSize;
        newGlyph.transform.h = fontSize;
    }
    // sepcial chars
    // newline

    // idk how dest. its the position of the texture so that gets calculated later down the pipeline

    glyphs.push_back(newGlyph);

    /*
    if (labelType == LABEL_TYPE_SHADOW)
    {
        glyphs_Shadow.push_back(newGlyphShadow);
    }
    */
    //std::cout << "[GenerateGlyphBasedOnChar] Added glyph:\nX: " << newGlyph.textureSrc.x << "\nY: " << newGlyph.textureSrc.y << "\n";
}





/// FNT SUPPORT

void Label::LoadCFNT(std::string filepath)
{
    
    
}

void Label::GenerateGlyphsCFNT()
{
    newLineCount = 1;
    if (!need_new_glyphs_to_be_generated)
    {
        // create glyphs for every char.
        // here is the main check func. for loop. every char, check the char and create a glyph.
        for (int i = 0; i < text.size(); i++)
        {
            // with every character check the char
            GenerateGlyphBasedOnCharCFNT(text[i], charsSinceNewLine);
            //std::cout << "[GenerateGlyphs] Generating new glyph: '" << text[charsSinceNewLine] << "'\n";
            //std::cout << "[GenerateGlyphs] Characters since new line: '" << charsSinceNewLine << "'\n";
            if (text[i] != '\n')
            {
                charsSinceNewLine++;
                //std::cout << "[GenerateGlyphs] Glyph is not newline!\n";
            }
            else
            {
                charsSinceNewLine = 0;
                // we use newLineCount paired with the charHeight to determine the total height of the label.
                newLineCount++;
                //std::cout << "[GenerateGlyphs] Glyph is newline!\n";
            }
        }
        // theoretically after the forloop is done, we should be done with generating glyphs.
        need_new_glyphs_to_be_generated = true;
        glyphPositionXTotal = 0;
        //std::cout << "[GenerateGlyphs] Finished generating glyphs.\n";
    }
}

void Label::GenerateGlyphBasedOnCharCFNT(char input, int index)
{
    Glyph newGlyph;
    newGlyph.character = input;
    //std::cout << "[Label::GenerateGlyphBasedOnCharCFNT] index: '" << index << "' is character: '" << input << "'.\n";
    // This handles new line.
    if (input == 0x0A)
    {
        // newline with it starts at the beginning of the line.
        index = 0;
        // newline sets it a new line down
        // This might need a but more. maybe +2 of an gap?.
        charPositionY += charHeight;
        glyphPositionXTotal = 0;
    }

    if (input > 0 && input < 255)
    {
    #pragma region
        if (input == 32)
        {
            newGlyph.textureSrc.x = char32X;
        }
        if (input == 33)
        {
            newGlyph.textureSrc.x = char33X;
        }
        if (input == 34)
        {
            newGlyph.textureSrc.x = char34X;
        }
        if (input == 35)
        {
            newGlyph.textureSrc.x = char35X;
        }
        if (input == 36)
        {
            newGlyph.textureSrc.x = char36X;
        }
        if (input == 37)
        {
            newGlyph.textureSrc.x = char37X;
        }
        if (input == 38)
        {
            newGlyph.textureSrc.x = char38X;
        }
        if (input == 39)
        {
            newGlyph.textureSrc.x = char39X;
        }
        if (input == 40)
        {
            newGlyph.textureSrc.x = char40X;
        }
        if (input == 41)
        {
            newGlyph.textureSrc.x = char41X;
        }
        if (input == 42)
        {
            newGlyph.textureSrc.x = char42X;
        }
        if (input == 43)
        {
            newGlyph.textureSrc.x = char43X;
        }
        if (input == 44)
        {
            newGlyph.textureSrc.x = char44X;
        }
        if (input == 45)
        {
            newGlyph.textureSrc.x = char45X;
        }
        if (input == 46)
        {
            newGlyph.textureSrc.x = char46X;
        }
        if (input == 47)
        {
            newGlyph.textureSrc.x = char47X;
        }
        if (input == 48)
        {
            newGlyph.textureSrc.x = char48X;
        }
        if (input == 49)
        {
            newGlyph.textureSrc.x = char49X;
        }
        if (input == 50)
        {
            newGlyph.textureSrc.x = char50X;
        }
        if (input == 51)
        {
            newGlyph.textureSrc.x = char51X;
        }
        if (input == 52)
        {
            newGlyph.textureSrc.x = char52X;
        }
        if (input == 53)
        {
            newGlyph.textureSrc.x = char53X;
        }
        if (input == 54)
        {
            newGlyph.textureSrc.x = char54X;
        }
        if (input == 55)
        {
            newGlyph.textureSrc.x = char55X;
        }
        if (input == 56)
        {
            newGlyph.textureSrc.x = char56X;
        }
        if (input == 57)
        {
            newGlyph.textureSrc.x = char57X;
        }
        if (input == 58)
        {
            newGlyph.textureSrc.x = char58X;
        }
        if (input == 59)
        {
            newGlyph.textureSrc.x = char59X;
        }
        if (input == 60)
        {
            newGlyph.textureSrc.x = char60X;
        }
        if (input == 61)
        {
            newGlyph.textureSrc.x = char61X;
        }
        if (input == 62)
        {
            newGlyph.textureSrc.x = char62X;
        }
        if (input == 63)
        {
            newGlyph.textureSrc.x = char63X;
        }
        if (input == 64)
        {
            newGlyph.textureSrc.x = char64X;
        }
        if (input == 65)
        {
            newGlyph.textureSrc.x = char65X;
        }
        if (input == 66)
        {
            newGlyph.textureSrc.x = char66X;
        }
        if (input == 67)
        {
            newGlyph.textureSrc.x = char67X;
        }
        if (input == 68)
        {
            newGlyph.textureSrc.x = char68X;
        }
        if (input == 69)
        {
            newGlyph.textureSrc.x = char69X;
        }
        if (input == 70)
        {
            newGlyph.textureSrc.x = char70X;
        }
        if (input == 71)
        {
            newGlyph.textureSrc.x = char71X;
        }
        if (input == 72)
        {
            newGlyph.textureSrc.x = char72X;
        }
        if (input == 73)
        {
            newGlyph.textureSrc.x = char73X;
        }
        if (input == 74)
        {
            newGlyph.textureSrc.x = char74X;
        }
        if (input == 75)
        {
            newGlyph.textureSrc.x = char75X;
        }
        if (input == 76)
        {
            newGlyph.textureSrc.x = char76X;
        }
        if (input == 77)
        {
            newGlyph.textureSrc.x = char77X;
        }
        if (input == 78)
        {
            newGlyph.textureSrc.x = char78X;
        }
        if (input == 79)
        {
            newGlyph.textureSrc.x = char79X;
        }
        if (input == 80)
        {
            newGlyph.textureSrc.x = char80X;
        }
        if (input == 81)
        {
            newGlyph.textureSrc.x = char81X;
        }
        if (input == 82)
        {
            newGlyph.textureSrc.x = char82X;
        }
        if (input == 83)
        {
            newGlyph.textureSrc.x = char83X;
        }
        if (input == 84)
        {
            newGlyph.textureSrc.x = char84X;
        }
        if (input == 85)
        {
            newGlyph.textureSrc.x = char85X;
        }
        if (input == 86)
        {
            newGlyph.textureSrc.x = char86X;
        }
        if (input == 87)
        {
            newGlyph.textureSrc.x = char87X;
        }
        if (input == 88)
        {
            newGlyph.textureSrc.x = char88X;
        }
        if (input == 89)
        {
            newGlyph.textureSrc.x = char89X;
        }
        if (input == 90)
        {
            newGlyph.textureSrc.x = char90X;
        }
        if (input == 91)
        {
            newGlyph.textureSrc.x = char91X;
        }
        if (input == 92)
        {
            newGlyph.textureSrc.x = char92X;
        }
        if (input == 93)
        {
            newGlyph.textureSrc.x = char93X;
        }
        if (input == 94)
        {
            newGlyph.textureSrc.x = char94X;
        }
        if (input == 95)
        {
            newGlyph.textureSrc.x = char95X;
        }
        if (input == 96)
        {
            newGlyph.textureSrc.x = char96X;
        }
        if (input == 97)
        {
            newGlyph.textureSrc.x = char97X;
        }
        if (input == 98)
        {
            newGlyph.textureSrc.x = char98X;
        }
        if (input == 99)
        {
            newGlyph.textureSrc.x = char99X;
        }
        if (input == 100)
        {
            newGlyph.textureSrc.x = char100X;
        }
        if (input == 101)
        {
            newGlyph.textureSrc.x = char101X;
        }
        if (input == 102)
        {
            newGlyph.textureSrc.x = char102X;
        }
        if (input == 103)
        {
            newGlyph.textureSrc.x = char103X;
        }
        if (input == 104)
        {
            newGlyph.textureSrc.x = char104X;
        }
        if (input == 105)
        {
            newGlyph.textureSrc.x = char105X;
        }
        if (input == 106)
        {
            newGlyph.textureSrc.x = char106X;
        }
        if (input == 107)
        {
            newGlyph.textureSrc.x = char107X;
        }
        if (input == 108)
        {
            newGlyph.textureSrc.x = char108X;
        }
        if (input == 109)
        {
            newGlyph.textureSrc.x = char109X;
        }
        if (input == 110)
        {
            newGlyph.textureSrc.x = char110X;
        }
        if (input == 111)
        {
            newGlyph.textureSrc.x = char111X;
        }
        if (input == 112)
        {
            newGlyph.textureSrc.x = char112X;
        }
        if (input == 113)
        {
            newGlyph.textureSrc.x = char113X;
        }
        if (input == 114)
        {
            newGlyph.textureSrc.x = char114X;
        }
        if (input == 115)
        {
            newGlyph.textureSrc.x = char115X;
        }
        if (input == 116)
        {
            newGlyph.textureSrc.x = char116X;
        }
        if (input == 117)
        {
            newGlyph.textureSrc.x = char117X;
        }
        if (input == 118)
        {
            newGlyph.textureSrc.x = char118X;
        }
        if (input == 119)
        {
            newGlyph.textureSrc.x = char119X;
        }
        if (input == 120)
        {
            newGlyph.textureSrc.x = char120X;
        }
        if (input == 121)
        {
            newGlyph.textureSrc.x = char121X;
            //std::cout << char121X << " \n";

        }
        if (input == 122)
        {
            newGlyph.textureSrc.x = char122X;
        }
        if (input == 123)
        {
            newGlyph.textureSrc.x = char123X;
        }
        if (input == 124)
        {
            newGlyph.textureSrc.x = char124X;
        }
        if (input == 125)
        {
            newGlyph.textureSrc.x = char125X;
        }
        if (input == 126)
        {
            newGlyph.textureSrc.x = char126X;
            //std::cout << char126X << " \n";
        }

        newGlyph.textureSrc.y = 0;

        if (input == 32)
        {
            newGlyph.textureSrc.w = char32Width;
        }
        if (input == 33)
        {
            newGlyph.textureSrc.w = char33Width;
        }
        if (input == 34)
        {
            newGlyph.textureSrc.w = char34Width;
        }
        if (input == 35)
        {
            newGlyph.textureSrc.w = char35Width;
        }
        if (input == 36)
        {
            newGlyph.textureSrc.w = char36Width;
        }
        if (input == 37)
        {
            newGlyph.textureSrc.w = char37Width;
        }
        if (input == 38)
        {
            newGlyph.textureSrc.w = char38Width;
        }
        if (input == 39)
        {
            newGlyph.textureSrc.w = char39Width;
        }
        if (input == 40)
        {
            newGlyph.textureSrc.w = char40Width;
        }
        if (input == 41)
        {
            newGlyph.textureSrc.w = char41Width;
        }
        if (input == 42)
        {
            newGlyph.textureSrc.w = char42Width;
        }
        if (input == 43)
        {
            newGlyph.textureSrc.w = char43Width;
        }
        if (input == 44)
        {
            newGlyph.textureSrc.w = char44Width;
        }
        if (input == 45)
        {
            newGlyph.textureSrc.w = char45Width;
        }
        if (input == 46)
        {
            newGlyph.textureSrc.w = char46Width;
        }
        if (input == 47)
        {
            newGlyph.textureSrc.w = char47Width;
        }
        if (input == 48)
        {
            newGlyph.textureSrc.w = char48Width;
        }
        if (input == 49)
        {
            newGlyph.textureSrc.w = char49Width;
        }
        if (input == 50)
        {
            newGlyph.textureSrc.w = char50Width;
        }
        if (input == 51)
        {
            newGlyph.textureSrc.w = char51Width;
        }
        if (input == 52)
        {
            newGlyph.textureSrc.w = char52Width;
        }
        if (input == 53)
        {
            newGlyph.textureSrc.w = char53Width;
        }
        if (input == 54)
        {
            newGlyph.textureSrc.w = char54Width;
        }
        if (input == 55)
        {
            newGlyph.textureSrc.w = char55Width;
        }
        if (input == 56)
        {
            newGlyph.textureSrc.w = char56Width;
        }
        if (input == 57)
        {
            newGlyph.textureSrc.w = char57Width;
        }
        if (input == 58)
        {
            newGlyph.textureSrc.w = char58Width;
        }
        if (input == 59)
        {
            newGlyph.textureSrc.w = char59Width;
        }
        if (input == 60)
        {
            newGlyph.textureSrc.w = char60Width;
        }
        if (input == 61)
        {
            newGlyph.textureSrc.w = char61Width;
        }
        if (input == 62)
        {
            newGlyph.textureSrc.w = char62Width;
        }
        if (input == 63)
        {
            newGlyph.textureSrc.w = char63Width;
        }
        if (input == 64)
        {
            newGlyph.textureSrc.w = char64Width;
        }
        if (input == 65)
        {
            newGlyph.textureSrc.w = char65Width;
        }
        if (input == 66)
        {
            newGlyph.textureSrc.w = char66Width;
        }
        if (input == 67)
        {
            newGlyph.textureSrc.w = char67Width;
        }
        if (input == 68)
        {
            newGlyph.textureSrc.w = char68Width;
        }
        if (input == 69)
        {
            newGlyph.textureSrc.w = char69Width;
        }
        if (input == 70)
        {
            newGlyph.textureSrc.w = char70Width;
        }
        if (input == 71)
        {
            newGlyph.textureSrc.w = char71Width;
        }
        if (input == 72)
        {
            newGlyph.textureSrc.w = char72Width;
        }
        if (input == 73)
        {
            newGlyph.textureSrc.w = char73Width;
        }
        if (input == 74)
        {
            newGlyph.textureSrc.w = char74Width;
        }
        if (input == 75)
        {
            newGlyph.textureSrc.w = char75Width;
        }
        if (input == 76)
        {
            newGlyph.textureSrc.w = char76Width;
        }
        if (input == 77)
        {
            newGlyph.textureSrc.w = char77Width;
        }
        if (input == 78)
        {
            newGlyph.textureSrc.w = char78Width;
        }
        if (input == 79)
        {
            newGlyph.textureSrc.w = char79Width;
        }
        if (input == 80)
        {
            newGlyph.textureSrc.w = char80Width;
        }
        if (input == 81)
        {
            newGlyph.textureSrc.w = char81Width;
        }
        if (input == 82)
        {
            newGlyph.textureSrc.w = char82Width;
        }
        if (input == 83)
        {
            newGlyph.textureSrc.w = char83Width;
        }
        if (input == 84)
        {
            newGlyph.textureSrc.w = char84Width;
        }
        if (input == 85)
        {
            newGlyph.textureSrc.w = char85Width;
        }
        if (input == 86)
        {
            newGlyph.textureSrc.w = char86Width;
        }
        if (input == 87)
        {
            newGlyph.textureSrc.w = char87Width;
        }
        if (input == 88)
        {
            newGlyph.textureSrc.w = char88Width;
        }
        if (input == 89)
        {
            newGlyph.textureSrc.w = char89Width;
        }
        if (input == 90)
        {
            newGlyph.textureSrc.w = char90Width;
        }
        if (input == 91)
        {
            newGlyph.textureSrc.w = char91Width;
        }
        if (input == 92)
        {
            newGlyph.textureSrc.w = char92Width;
        }
        if (input == 93)
        {
            newGlyph.textureSrc.w = char93Width;
        }
        if (input == 94)
        {
            newGlyph.textureSrc.w = char94Width;
        }
        if (input == 95)
        {
            newGlyph.textureSrc.w = char95Width;
        }
        if (input == 96)
        {
            newGlyph.textureSrc.w = char96Width;
        }
        if (input == 97)
        {
            newGlyph.textureSrc.w = char97Width;
        }
        if (input == 98)
        {
            newGlyph.textureSrc.w = char98Width;
        }
        if (input == 99)
        {
            newGlyph.textureSrc.w = char99Width;
        }
        if (input == 100)
        {
            newGlyph.textureSrc.w = char100Width;
        }
        if (input == 101)
        {
            newGlyph.textureSrc.w = char101Width;
        }
        if (input == 102)
        {
            newGlyph.textureSrc.w = char102Width;
        }
        if (input == 103)
        {
            newGlyph.textureSrc.w = char103Width;
        }
        if (input == 104)
        {
            newGlyph.textureSrc.w = char104Width;
        }
        if (input == 105)
        {
            newGlyph.textureSrc.w = char105Width;
        }
        if (input == 106)
        {
            newGlyph.textureSrc.w = char106Width;
        }
        if (input == 107)
        {
            newGlyph.textureSrc.w = char107Width;
        }
        if (input == 108)
        {
            newGlyph.textureSrc.w = char108Width;
        }
        if (input == 109)
        {
            newGlyph.textureSrc.w = char109Width;
        }
        if (input == 110)
        {
            newGlyph.textureSrc.w = char110Width;
        }
        if (input == 111)
        {
            newGlyph.textureSrc.w = char111Width;
        }
        if (input == 112)
        {
            newGlyph.textureSrc.w = char112Width;
        }
        if (input == 113)
        {
            newGlyph.textureSrc.w = char113Width;
        }
        if (input == 114)
        {
            newGlyph.textureSrc.w = char114Width;
        }
        if (input == 115)
        {
            newGlyph.textureSrc.w = char115Width;
        }
        if (input == 116)
        {
            newGlyph.textureSrc.w = char116Width;
        }
        if (input == 117)
        {
            newGlyph.textureSrc.w = char117Width;
        }
        if (input == 118)
        {
            newGlyph.textureSrc.w = char118Width;
        }
        if (input == 119)
        {
            newGlyph.textureSrc.w = char119Width;
        }
        if (input == 120)
        {
            newGlyph.textureSrc.w = char120Width;
        }
        if (input == 121)
        {
            newGlyph.textureSrc.w = char121Width;
        }
        if (input == 122)
        {
            newGlyph.textureSrc.w = char122Width;
        }
        if (input == 123)
        {
            newGlyph.textureSrc.w = char123Width;
        }
        if (input == 124)
        {
            newGlyph.textureSrc.w = char124Width;
        }
        if (input == 125)
        {
            newGlyph.textureSrc.w = char125Width;
        }
        if (input == 126)
        {
            newGlyph.textureSrc.w = char126Width;
        }


        newGlyph.textureSrc.h = charHeight;

        // use an index.
        newGlyph.positionX = glyphPositionXTotal;

        newGlyph.positionY = charPositionY;
        // for fontisze X
        newGlyph.transform.x = newGlyph.positionX;
        //newGlyph.transform.y = newGlyph.positionY;


        //std::cout << "newGlyph.positionX: '" << newGlyph.positionX << "'\n";
        
        if (input == 32)
        {
            glyphPositionXTotal += (char32Width * newScale);
        }
        if (input == 33)
        {
            glyphPositionXTotal += (char33Width * newScale);
        }
        if (input == 34)
        {
            glyphPositionXTotal += (char34Width * newScale);
        }
        if (input == 35)
        {
            glyphPositionXTotal += (char35Width * newScale);
        }
        if (input == 36)
        {
            glyphPositionXTotal += (char36Width * newScale);
        }
        if (input == 37)
        {
            glyphPositionXTotal += (char37Width * newScale);
        }
        if (input == 38)
        {
            glyphPositionXTotal += (char38Width * newScale);
        }
        if (input == 39)
        {
            glyphPositionXTotal += (char39Width * newScale);
        }
        if (input == 40)
        {
            glyphPositionXTotal += (char40Width * newScale);
        }
        if (input == 41)
        {
            glyphPositionXTotal += (char41Width * newScale);
        }
        if (input == 42)
        {
            glyphPositionXTotal += (char42Width * newScale);
        }
        if (input == 43)
        {
            glyphPositionXTotal += (char43Width * newScale);
        }
        if (input == 44)
        {
            glyphPositionXTotal += (char44Width * newScale);
        }
        if (input == 45)
        {
            glyphPositionXTotal += (char45Width * newScale);
        }
        if (input == 46)
        {
            glyphPositionXTotal += (char46Width * newScale);
        }
        if (input == 47)
        {
            glyphPositionXTotal += (char47Width * newScale);
        }
        if (input == 48)
        {
            glyphPositionXTotal += (char48Width * newScale);
        }
        if (input == 49)
        {
            glyphPositionXTotal += (char49Width * newScale);
        }
        if (input == 50)
        {
            glyphPositionXTotal += (char50Width * newScale);
        }
        if (input == 51)
        {
            glyphPositionXTotal += (char51Width * newScale);
        }
        if (input == 52)
        {
            glyphPositionXTotal += (char52Width * newScale);
        }
        if (input == 53)
        {
            glyphPositionXTotal += (char53Width * newScale);
        }
        if (input == 54)
        {
            glyphPositionXTotal += (char54Width * newScale);
        }
        if (input == 55)
        {
            glyphPositionXTotal += (char55Width * newScale);
        }
        if (input == 56)
        {
            glyphPositionXTotal += (char56Width * newScale);
        }
        if (input == 57)
        {
            glyphPositionXTotal += (char57Width * newScale);
        }
        if (input == 58)
        {
            glyphPositionXTotal += (char58Width * newScale);
        }
        if (input == 59)
        {
            glyphPositionXTotal += (char59Width * newScale);
        }
        if (input == 60)
        {
            glyphPositionXTotal += (char60Width * newScale);
        }
        if (input == 61)
        {
            glyphPositionXTotal += (char61Width * newScale);
        }
        if (input == 62)
        {
            glyphPositionXTotal += (char62Width * newScale);
        }
        if (input == 63)
        {
            glyphPositionXTotal += (char63Width * newScale);
        }
        if (input == 64)
        {
            glyphPositionXTotal += (char64Width * newScale);
        }
        if (input == 65)
        {
            glyphPositionXTotal += (char65Width * newScale);
        }
        if (input == 66)
        {
            glyphPositionXTotal += (char66Width * newScale);
        }
        if (input == 67)
        {
            glyphPositionXTotal += (char67Width * newScale);
        }
        if (input == 68)
        {
            glyphPositionXTotal += (char68Width * newScale);
        }
        if (input == 69)
        {
            glyphPositionXTotal += (char69Width * newScale);
        }
        if (input == 70)
        {
            glyphPositionXTotal += (char70Width * newScale);
        }
        if (input == 71)
        {
            glyphPositionXTotal += (char71Width * newScale);
        }
        if (input == 72)
        {
            glyphPositionXTotal += (char72Width * newScale);
        }
        if (input == 73)
        {
            glyphPositionXTotal += (char73Width * newScale);
        }
        if (input == 74)
        {
            glyphPositionXTotal += (char74Width * newScale);
        }
        if (input == 75)
        {
            glyphPositionXTotal += (char75Width * newScale);
        }
        if (input == 76)
        {
            glyphPositionXTotal += (char76Width * newScale);
        }
        if (input == 77)
        {
            glyphPositionXTotal += (char77Width * newScale);
        }
        if (input == 78)
        {
            glyphPositionXTotal += (char78Width * newScale);
        }
        if (input == 79)
        {
            glyphPositionXTotal += (char79Width * newScale);
        }
        if (input == 80)
        {
            glyphPositionXTotal += (char80Width * newScale);
        }
        if (input == 81)
        {
            glyphPositionXTotal += (char81Width * newScale);
        }
        if (input == 82)
        {
            glyphPositionXTotal += (char82Width * newScale);
        }
        if (input == 83)
        {
            glyphPositionXTotal += (char83Width * newScale);
        }
        if (input == 84)
        {
            glyphPositionXTotal += (char84Width * newScale);
        }
        if (input == 85)
        {
            glyphPositionXTotal += (char85Width * newScale);
        }
        if (input == 86)
        {
            glyphPositionXTotal += (char86Width * newScale);
        }
        if (input == 87)
        {
            glyphPositionXTotal += (char87Width * newScale);
        }
        if (input == 88)
        {
            glyphPositionXTotal += (char88Width * newScale);
        }
        if (input == 89)
        {
            glyphPositionXTotal += (char89Width * newScale);
        }
        if (input == 90)
        {
            glyphPositionXTotal += (char90Width * newScale);
        }
        if (input == 91)
        {
            glyphPositionXTotal += (char91Width * newScale);
        }
        if (input == 92)
        {
            glyphPositionXTotal += (char92Width * newScale);
        }
        if (input == 93)
        {
            glyphPositionXTotal += (char93Width * newScale);
        }
        if (input == 94)
        {
            glyphPositionXTotal += (char94Width * newScale);
        }
        if (input == 95)
        {
            glyphPositionXTotal += (char95Width * newScale);
        }
        if (input == 96)
        {
            glyphPositionXTotal += (char96Width * newScale);
        }
        if (input == 97)
        {
            glyphPositionXTotal += (char97Width * newScale);
        }
        if (input == 98)
        {
            glyphPositionXTotal += (char98Width * newScale);
        }
        if (input == 99)
        {
            glyphPositionXTotal += (char99Width * newScale);
        }
        if (input == 100)
        {
            glyphPositionXTotal += (char100Width * newScale);
        }
        if (input == 101)
        {
            glyphPositionXTotal += (char101Width * newScale);
        }
        if (input == 102)
        {
            glyphPositionXTotal += (char102Width * newScale);
        }
        if (input == 103)
        {
            glyphPositionXTotal += (char103Width * newScale);
        }
        if (input == 104)
        {
            glyphPositionXTotal += (char104Width * newScale);
        }
        if (input == 105)
        {
            glyphPositionXTotal += (char105Width * newScale);
        }
        if (input == 106)
        {
            glyphPositionXTotal += (char106Width * newScale);
        }
        if (input == 107)
        {
            glyphPositionXTotal += (char107Width * newScale);
        }
        if (input == 108)
        {
            glyphPositionXTotal += (char108Width * newScale);
        }
        if (input == 109)
        {
            glyphPositionXTotal += (char109Width * newScale);
        }
        if (input == 110)
        {
            glyphPositionXTotal += (char110Width * newScale);
        }
        if (input == 111)
        {
            glyphPositionXTotal += (char111Width * newScale);
        }
        if (input == 112)
        {
            glyphPositionXTotal += (char112Width * newScale);
        }
        if (input == 113)
        {
            glyphPositionXTotal += (char113Width * newScale);
        }
        if (input == 114)
        {
            glyphPositionXTotal += (char114Width * newScale);
        }
        if (input == 115)
        {
            glyphPositionXTotal += (char115Width * newScale);
        }
        if (input == 116)
        {
            glyphPositionXTotal += (char116Width * newScale);
        }
        if (input == 117)
        {
            glyphPositionXTotal += (char117Width * newScale);
        }
        if (input == 118)
        {
            glyphPositionXTotal += (char118Width * newScale);
        }
        if (input == 119)
        {
            glyphPositionXTotal += (char119Width * newScale);
        }
        if (input == 120)
        {
            glyphPositionXTotal += (char120Width * newScale);
        }
        if (input == 121)
        {
            glyphPositionXTotal += (char121Width * newScale);
        }
        if (input == 122)
        {
            glyphPositionXTotal += (char122Width * newScale);
        }
        if (input == 123)
        {
            glyphPositionXTotal += (char123Width * newScale);
        }
        if (input == 124)
        {
            glyphPositionXTotal += (char124Width * newScale);
        }
        if (input == 125)
        {
            glyphPositionXTotal += (char125Width * newScale);
        }
        if (input == 126)
        {
            glyphPositionXTotal += (char126Width * newScale);
        }

        newGlyph.transform.y = positionY + charPositionY;

        if (input == 32)
        {
            newGlyph.transform.w = char32Width * newScale;
        }
        if (input == 33)
        {
            newGlyph.transform.w = char33Width * newScale;
        }
        if (input == 34)
        {
            newGlyph.transform.w = char34Width * newScale;
        }
        if (input == 35)
        {
            newGlyph.transform.w = char35Width * newScale;
        }
        if (input == 36)
        {
            newGlyph.transform.w = char36Width * newScale;
        }
        if (input == 37)
        {
            newGlyph.transform.w = char37Width * newScale;
        }
        if (input == 38)
        {
            newGlyph.transform.w = char38Width * newScale;
        }
        if (input == 39)
        {
            newGlyph.transform.w = char39Width * newScale;
        }
        if (input == 40)
        {
            newGlyph.transform.w = char40Width * newScale;
        }
        if (input == 41)
        {
            newGlyph.transform.w = char41Width * newScale;
        }
        if (input == 42)
        {
            newGlyph.transform.w = char42Width * newScale;
        }
        if (input == 43)
        {
            newGlyph.transform.w = char43Width * newScale;
        }
        if (input == 44)
        {
            newGlyph.transform.w = char44Width * newScale;
        }
        if (input == 45)
        {
            newGlyph.transform.w = char45Width * newScale;
        }
        if (input == 46)
        {
            newGlyph.transform.w = char46Width * newScale;
        }
        if (input == 47)
        {
            newGlyph.transform.w = char47Width * newScale;
        }
        if (input == 48)
        {
            newGlyph.transform.w = char48Width * newScale;
        }
        if (input == 49)
        {
            newGlyph.transform.w = char49Width * newScale;
        }
        if (input == 50)
        {
            newGlyph.transform.w = char50Width * newScale;
        }
        if (input == 51)
        {
            newGlyph.transform.w = char51Width * newScale;
        }
        if (input == 52)
        {
            newGlyph.transform.w = char52Width * newScale;
        }
        if (input == 53)
        {
            newGlyph.transform.w = char53Width * newScale;
        }
        if (input == 54)
        {
            newGlyph.transform.w = char54Width * newScale;
        }
        if (input == 55)
        {
            newGlyph.transform.w = char55Width * newScale;
        }
        if (input == 56)
        {
            newGlyph.transform.w = char56Width * newScale;
        }
        if (input == 57)
        {
            newGlyph.transform.w = char57Width * newScale;
        }
        if (input == 58)
        {
            newGlyph.transform.w = char58Width * newScale;
        }
        if (input == 59)
        {
            newGlyph.transform.w = char59Width * newScale;
        }
        if (input == 60)
        {
            newGlyph.transform.w = char60Width * newScale;
        }
        if (input == 61)
        {
            newGlyph.transform.w = char61Width * newScale;
        }
        if (input == 62)
        {
            newGlyph.transform.w = char62Width * newScale;
        }
        if (input == 63)
        {
            newGlyph.transform.w = char63Width * newScale;
        }
        if (input == 64)
        {
            newGlyph.transform.w = char64Width * newScale;
        }
        if (input == 65)
        {
            newGlyph.transform.w = char65Width * newScale;
        }
        if (input == 66)
        {
            newGlyph.transform.w = char66Width * newScale;
        }
        if (input == 67)
        {
            newGlyph.transform.w = char67Width * newScale;
        }
        if (input == 68)
        {
            newGlyph.transform.w = char68Width * newScale;
        }
        if (input == 69)
        {
            newGlyph.transform.w = char69Width * newScale;
        }
        if (input == 70)
        {
            newGlyph.transform.w = char70Width * newScale;
        }
        if (input == 71)
        {
            newGlyph.transform.w = char71Width * newScale;
        }
        if (input == 72)
        {
            newGlyph.transform.w = char72Width * newScale;
        }
        if (input == 73)
        {
            newGlyph.transform.w = char73Width * newScale;
        }
        if (input == 74)
        {
            newGlyph.transform.w = char74Width * newScale;
        }
        if (input == 75)
        {
            newGlyph.transform.w = char75Width * newScale;
        }
        if (input == 76)
        {
            newGlyph.transform.w = char76Width * newScale;
        }
        if (input == 77)
        {
            newGlyph.transform.w = char77Width * newScale;
        }
        if (input == 78)
        {
            newGlyph.transform.w = char78Width * newScale;
        }
        if (input == 79)
        {
            newGlyph.transform.w = char79Width * newScale;
        }
        if (input == 80)
        {
            newGlyph.transform.w = char80Width * newScale;
        }
        if (input == 81)
        {
            newGlyph.transform.w = char81Width * newScale;
        }
        if (input == 82)
        {
            newGlyph.transform.w = char82Width * newScale;
        }
        if (input == 83)
        {
            newGlyph.transform.w = char83Width * newScale;
        }
        if (input == 84)
        {
            newGlyph.transform.w = char84Width * newScale;
        }
        if (input == 85)
        {
            newGlyph.transform.w = char85Width * newScale;
        }
        if (input == 86)
        {
            newGlyph.transform.w = char86Width * newScale;
        }
        if (input == 87)
        {
            newGlyph.transform.w = char87Width * newScale;
        }
        if (input == 88)
        {
            newGlyph.transform.w = char88Width * newScale;
        }
        if (input == 89)
        {
            newGlyph.transform.w = char89Width * newScale;
        }
        if (input == 90)
        {
            newGlyph.transform.w = char90Width * newScale;
        }
        if (input == 91)
        {
            newGlyph.transform.w = char91Width * newScale;
        }
        if (input == 92)
        {
            newGlyph.transform.w = char92Width * newScale;
        }
        if (input == 93)
        {
            newGlyph.transform.w = char93Width * newScale;
        }
        if (input == 94)
        {
            newGlyph.transform.w = char94Width * newScale;
        }
        if (input == 95)
        {
            newGlyph.transform.w = char95Width * newScale;
        }
        if (input == 96)
        {
            newGlyph.transform.w = char96Width * newScale;
        }
        if (input == 97)
        {
            newGlyph.transform.w = char97Width * newScale;
        }
        if (input == 98)
        {
            newGlyph.transform.w = char98Width * newScale;
        }
        if (input == 99)
        {
            newGlyph.transform.w = char99Width * newScale;
        }
        if (input == 100)
        {
            newGlyph.transform.w = char100Width * newScale;
        }
        if (input == 101)
        {
            newGlyph.transform.w = char101Width * newScale;
        }
        if (input == 102)
        {
            newGlyph.transform.w = char102Width * newScale;
        }
        if (input == 103)
        {
            newGlyph.transform.w = char103Width * newScale;
        }
        if (input == 104)
        {
            newGlyph.transform.w = char104Width * newScale;
        }
        if (input == 105)
        {
            newGlyph.transform.w = char105Width * newScale;
        }
        if (input == 106)
        {
            newGlyph.transform.w = char106Width * newScale;
        }
        if (input == 107)
        {
            newGlyph.transform.w = char107Width * newScale;
        }
        if (input == 108)
        {
            newGlyph.transform.w = char108Width * newScale;
        }
        if (input == 109)
        {
            newGlyph.transform.w = char109Width * newScale;
        }
        if (input == 110)
        {
            newGlyph.transform.w = char110Width * newScale;
        }
        if (input == 111)
        {
            newGlyph.transform.w = char111Width * newScale;
        }
        if (input == 112)
        {
            newGlyph.transform.w = char112Width * newScale;
        }
        if (input == 113)
        {
            newGlyph.transform.w = char113Width * newScale;
        }
        if (input == 114)
        {
            newGlyph.transform.w = char114Width * newScale;
        }
        if (input == 115)
        {
            newGlyph.transform.w = char115Width * newScale;
        }
        if (input == 116)
        {
            newGlyph.transform.w = char116Width * newScale;
        }
        if (input == 117)
        {
            newGlyph.transform.w = char117Width * newScale;
        }
        if (input == 118)
        {
            newGlyph.transform.w = char118Width * newScale;
        }
        if (input == 119)
        {
            newGlyph.transform.w = char119Width * newScale;
        }
        if (input == 120)
        {
            newGlyph.transform.w = char120Width * newScale;
        }
        if (input == 121)
        {
            newGlyph.transform.w = char121Width * newScale;
        }
        if (input == 122)
        {
            newGlyph.transform.w = char122Width * newScale;
        }
        if (input == 123)
        {
            newGlyph.transform.w = char123Width * newScale;
        }
        if (input == 124)
        {
            newGlyph.transform.w = char124Width * newScale;
        }
        if (input == 125)
        {
            newGlyph.transform.w = char125Width * newScale;
        }
        if (input == 126)
        {
            newGlyph.transform.w = char126Width * newScale;
        }
        newGlyph.transform.h = fontSize;
    }
    // sepcial chars
    // newline

    // idk how dest. its the position of the texture so that gets calculated later down the pipeline

    glyphs.push_back(newGlyph);
    //std::cout << "[GenerateGlyphBasedOnCharCFNT] charPositionX: '" << charPositionX << "'\n";
}

void Label::SetTextCFNT(std::string newText)
{
}

void Label::PositionCFNT(int x, int y)
{
    positionX = x;
    positionY = y;
}

void Label::CalculateCharXValueCFNT()
{
    char32X = 0;
    char33X = char32X + char32Width;
    char34X = char33X + char33Width;
    char35X = char34X + char34Width;
    char36X = char35X + char35Width;
    char37X = char36X + char36Width;
    char38X = char37X + char37Width;
    char39X = char38X + char38Width;
    char40X = char39X + char39Width;
    char41X = char40X + char40Width;
    char42X = char41X + char41Width;
    char43X = char42X + char42Width;
    char44X = char43X + char43Width;
    char45X = char44X + char44Width;
    char46X = char45X + char45Width;
    char47X = char46X + char46Width;
    char48X = char47X + char47Width;
    char49X = char48X + char48Width;
    char50X = char49X + char49Width;
    char51X = char50X + char50Width;
    char52X = char51X + char51Width;
    char53X = char52X + char52Width;
    char54X = char53X + char53Width;
    char55X = char54X + char54Width;
    char56X = char55X + char55Width;
    char57X = char56X + char56Width;
    char58X = char57X + char57Width;
    char59X = char58X + char58Width;
    char60X = char59X + char59Width;
    char61X = char60X + char60Width;
    char62X = char61X + char61Width;
    char63X = char62X + char62Width;
    char64X = char63X + char63Width;
    char65X = char64X + char64Width;
    char66X = char65X + char65Width;
    char67X = char66X + char66Width;
    char68X = char67X + char67Width;
    char69X = char68X + char68Width;
    char70X = char69X + char69Width;
    char71X = char70X + char70Width;
    char72X = char71X + char71Width;
    char73X = char72X + char72Width;
    char74X = char73X + char73Width;
    char75X = char74X + char74Width;
    char76X = char75X + char75Width;
    char77X = char76X + char76Width;
    char78X = char77X + char77Width;
    char79X = char78X + char78Width;
    char80X = char79X + char79Width;
    char81X = char80X + char80Width;
    char82X = char81X + char81Width;
    char83X = char82X + char82Width;
    char84X = char83X + char83Width;
    char85X = char84X + char84Width;
    char86X = char85X + char85Width;
    char87X = char86X + char86Width;
    char88X = char87X + char87Width;
    char89X = char88X + char88Width;
    char90X = char89X + char89Width;
    char91X = char90X + char90Width;
    char92X = char91X + char91Width;
    char93X = char92X + char92Width;
    char94X = char93X + char93Width;
    char95X = char94X + char94Width;
    char96X = char95X + char95Width;
    char97X = char96X + char96Width;
    char98X = char97X + char97Width;
    char99X = char98X + char98Width;
    char100X = char99X + char99Width;
    char101X = char100X + char100Width;
    char102X = char101X + char101Width;
    char103X = char102X + char102Width;
    char104X = char103X + char103Width;
    char105X = char104X + char104Width;
    char106X = char105X + char105Width;
    char107X = char106X + char106Width;
    char108X = char107X + char107Width;
    char109X = char108X + char108Width;
    char110X = char109X + char109Width;
    char111X = char110X + char110Width;
    char112X = char111X + char111Width;
    char113X = char112X + char112Width;
    char114X = char113X + char113Width;
    char115X = char114X + char114Width;
    char116X = char115X + char115Width;
    char117X = char116X + char116Width;
    char118X = char117X + char117Width;
    char119X = char118X + char118Width;
    char120X = char119X + char119Width;
    char121X = char120X + char120Width;
    char122X = char121X + char121Width;
    char123X = char122X + char122Width;
    char124X = char123X + char123Width;
    char125X = char124X + char124Width;
    char126X = char125X + char125Width;
}

void Label::SetCameraBased()
{
    cameraBased = true;
}

void Label::SetCamera(Camera& camera_)
{
    camera = &camera_;
    if (camera != nullptr)
    {
        //std::cout << "[Label::SetCamera] camera not null.\n";
    }
    //texture.SetCamera(*camera);
}
