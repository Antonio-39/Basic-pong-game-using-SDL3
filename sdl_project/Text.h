#pragma once
#include <SDL3/SDL.h>
#include "SDLState.h"
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <cstdio>
#include <cstring>
#include <iostream>

class Text
{
public:
    TTF_Font* font;
    SDL_Texture* score_texture;
    char score_text[16];
    float x, y;


    Text() : font(nullptr), score_texture(nullptr), x(50), y(50)
    {
        memset(score_text, 0, sizeof(score_text));
    }

    void drawText(SDLState& state, int playerScore, int botScore)
    {
        SDL_Color color = { 255, 0, 0, 255 };

        char botString[50];
        char playerString[50];

        // Format the strings separately
        snprintf(botString, sizeof(botString), "Bot: %d", botScore);
        snprintf(playerString, sizeof(playerString), "You: %d", playerScore);

        // === Render First Line (Bot) ===
        SDL_Surface* surface1 = TTF_RenderText_Blended(font, botString, 0, color);
        SDL_Texture* texture1 = SDL_CreateTextureFromSurface(state.renderer, surface1);

        float w1, h1;
        SDL_GetTextureSize(texture1, &w1, &h1);
        w1 /= 2.0f;
        h1 /= 2.0f;
        SDL_DestroySurface(surface1);

        // === Render Second Line (Player) ===
        SDL_Surface* surface2 = TTF_RenderText_Blended(font, playerString, 0, color);
        SDL_Texture* texture2 = SDL_CreateTextureFromSurface(state.renderer, surface2);

        float w2, h2;
        SDL_GetTextureSize(texture2, &w2, &h2);
        w2 /= 2.0f;
        h2 /= 2.0f;
        SDL_DestroySurface(surface2);

        // === Calculate Positions ===
        float x1 = 0; // Left-aligned like your original code
        float y1 = (LOGICAL_HEIGHT / 2.0f) - (h1 * 2.0f);

        float x2 = 0;
        float y2 = (LOGICAL_HEIGHT / 2.0f) + (h1 * 1.0f);

        SDL_FRect dst1 = { x1, y1, w1, h1 };
        SDL_FRect dst2 = { x2, y2, w2, h2 };

        // === Draw Textures ===
        SDL_RenderTexture(state.renderer, texture1, NULL, &dst1);
        SDL_RenderTexture(state.renderer, texture2, NULL, &dst2);

        // === Clean Up ===
        SDL_DestroyTexture(texture1);
        SDL_DestroyTexture(texture2);
    }

    void startScreenText(SDLState& state)
    {
        SDL_Color color = { 255, 0, 0, 255 };

        // === Render First Line ===
        SDL_Surface* surface1 = TTF_RenderText_Blended(font, "Basic Pong game!", 0, color);
        SDL_Texture* texture1 = SDL_CreateTextureFromSurface(state.renderer, surface1);

        float w1, h1;
        SDL_GetTextureSize(texture1, &w1, &h1);
        w1 /= 2.0f; // Scaling down by half, matching your original code
        h1 /= 2.0f;
        SDL_DestroySurface(surface1);

        // === Render Second Line ===
        SDL_Surface* surface2 = TTF_RenderText_Blended(font, "Press Space to start!", 0, color);
        SDL_Texture* texture2 = SDL_CreateTextureFromSurface(state.renderer, surface2);

        float w2, h2;
        SDL_GetTextureSize(texture2, &w2, &h2);
        w2 /= 2.0f;
        h2 /= 2.0f;
        SDL_DestroySurface(surface2);

        // === Calculate Positions ===
        // Centering the text horizontally. Change X to 0 if you prefer it left-aligned.
        float x1 = (LOGICAL_WIDTH / 2.0f) - (w1 / 2.0f);
        float y1 = (LOGICAL_HEIGHT / 2.0f) - (h1 * 2.0f);

        float x2 = (LOGICAL_WIDTH / 2.0f) - (w2 / 2.0f);
        float y2 = y1 + h1 + 10.0f; // 10 pixels gap below the first line

        SDL_FRect dst1 = { x1, y1, w1, h1 };
        SDL_FRect dst2 = { x2, y2, w2, h2 };

        // === Draw Textures ===
        SDL_RenderTexture(state.renderer, texture1, NULL, &dst1);
        SDL_RenderTexture(state.renderer, texture2, NULL, &dst2);

        // === Clean Up ===
        // Textures must be destroyed every frame if created dynamically, 
        // otherwise your VRAM will quickly fill up and crash the game.
        SDL_DestroyTexture(texture1);
        SDL_DestroyTexture(texture2);
    }
};