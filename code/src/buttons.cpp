#include "../include/ui.hpp"
#include <SDL3/SDL_stdinc.h>

void Texture::destroy()
{
    SDL_DestroyTexture( texture );
    texture = nullptr;
    width = 0;
    height = 0;
}

void Texture::setColor( Uint8 r, Uint8 g, Uint8 b )
{
    SDL_SetTextureColorMod( texture, r, g, b );
}

void Texture::setAlpha( Uint8 alpha )
{
    SDL_SetTextureAlphaMod( texture, alpha );
}

void Texture::setBlending( SDL_BlendMode blendMode )
{
    SDL_SetTextureBlendMode( texture, blendMode );
}

void Texture::render( float x, float y) {
     //Set texture position
    SDL_FRect dstRect{ x, y, static_cast<float>( width ), static_cast<float>( height ) };

    SDL_RenderTexture( gRenderer, texture,  )
}

void Texture::render( float x, float y, SDL_FRect* clip, float width, float height, double degrees, SDL_FPoint* center, SDL_FlipMode flipMode )
{
    //Set texture position
    SDL_FRect dstRect{ x, y, static_cast<float>( width ), static_cast<float>( height ) };

    //Default to clip dimensions if clip is given
    if( clip != nullptr )
    {
        dstRect.w = clip->w;
        dstRect.h = clip->h;
    }

    //Resize if new dimensions are given
    if( width > 0 )
    {
        dstRect.w = width;
    }
    if( height > 0 )
    {
        dstRect.h = height;
    }

    //Render texture
    SDL_RenderTextureRotated( gRenderer, texture, clip, &dstRect, degrees, center, flipMode );
}

bool Texture::loadFromFile( std::string path )
{
    //Clean up texture if it already exists
    destroy();

    //Load surface
    if( SDL_Surface* loadedSurface = IMG_Load( path.c_str() ); loadedSurface == nullptr )
    {
        SDL_Log( "Unable to load image %s! SDL_image error: %s\n", path.c_str(), SDL_GetError() );
    }
    else
    {
        //Color key image
        if( SDL_SetSurfaceColorKey( loadedSurface, true, SDL_MapSurfaceRGB( loadedSurface, 0x00, 0xFF, 0xFF ) ) == false )
        {
            SDL_Log( "Unable to color key! SDL error: %s", SDL_GetError() );
        }
        else
        {
            //Create texture from surface
            if( SDL_Texture* texture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface ); texture == nullptr )
            {
                SDL_Log( "Unable to create texture from loaded pixels! SDL error: %s\n", SDL_GetError() );
            }
            else
            {
                //Get image dimensions
                width = loadedSurface->w;
                height = loadedSurface->h;
            }
        }

        //Clean up loaded surface
        SDL_DestroySurface( loadedSurface );
    }

    //Return success if texture loaded
    return texture != nullptr;
}

/* FONTS */
 TTF_Font* arial{ nullptr };


#if defined(SDL_TTF_MAJOR_VERSION)
bool Texture::loadFromRenderedText( std::string textureText, SDL_Color textColor )
{
    //Clean up existing texture
    destroy();

    //Load text surface
    if( SDL_Surface* textSurface = TTF_RenderText_Blended( arial, textureText.c_str(), 0, textColor ); textSurface == nullptr )
    {
        SDL_Log( "Unable to render text surface! SDL_ttf Error: %s\n", SDL_GetError() );
    }
    else
    {
        //Create texture from surface
        if( texture = SDL_CreateTextureFromSurface( gRenderer, textSurface ); texture == nullptr )
        {
            SDL_Log( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
            width = textSurface->w;
            height = textSurface->h;
        }

        //Free temp surface
        SDL_DestroySurface( textSurface );
    }

    //Return success if texture loaded
    return texture != nullptr;
}
#endif


void Button::setPosition( float x, float y )
{
    position.x = x;
    position.y = y;
}

void Button::handleEvent(SDL_Event* e) {
    if ( e -> type = SDL_EVENT_MOUSE_MOTION || e -> type = SDL_EVENT_MOUSE_BUTTON_DOWN || e -> type = SDL_EVENT_MOUSE_BUTTON_UP) {
        float x = -1.f, y = -1.f;
        SDL_GetMouseState( &x, &y );

        bool inside = true;

        if (x < position.x || x > position.x + width || y < position.y || y > position.y + width) inside == false;

        if (!inside) {
            currentSprite = buttonSprite::Unpressed;
        } else {
            switch( e->type )
            {
                case SDL_EVENT_MOUSE_MOTION:
                currentSprite = buttonSprite::Hover;
                break;

                case SDL_EVENT_MOUSE_BUTTON_DOWN:
                currentSprite = buttonSprite::Pressed;
                break;
            }
        }
    }
}


void Button::render()
{
    float fHeight = static_cast<float>(height);
    float fWidth = static_cast<float>(width);
    //Define sprites of buttons, all three states, total 21 states
    SDL_FRect spriteClips[] = {
        { 0.0f, 0 * fHeight, fWidth, fHeight },
        { fWidth, 0 * fHeight, 2 * fWidth, fHeight },
        { 2 * fWidth, 0 * fHeight, 3 * fWidth, fHeight },
        { 0.0f, 1 * fHeight, fWidth, 2 * fHeight },
        { fWidth, 1 * fHeight, 2 * fWidth, 2 * fHeight },
        { 2 * fWidth, 1 * fHeight, 3 * fWidth, 2 * fHeight },
        { 0.f, 2 * fHeight, fWidth, 3 * fHeight },
        { fWidth, 2 * fHeight, 2 * fWidth, 3 * fHeight },
        { 2 * fWidth, 2 * fHeight, 3 * fWidth, 3 * fHeight },
        { 0.0f, 3 * fHeight, fWidth, 4 * fHeight },
        { fWidth, 3 * fHeight, 2 * fWidth, 4 * fHeight },
        { 2 * fWidth, 3 * fHeight, 3 * fWidth, 4 * fHeight },
        { 0.0f, 4 * fHeight, fWidth, 5 * fHeight },
        { fWidth, 4 * fHeight, 2 * fWidth, 5 * fHeight },
        { 2 * fWidth, 4 * fHeight, 3 * fWidth, 5 * fHeight },
        { 0.0f, 5 * fHeight, fWidth, 6 * fHeight },
        { fWidth, 5 * fHeight, 2 * fWidth, 6 * fHeight },
        { 2 * fWidth, 5 * fHeight, 3 * fWidth, 6 * fHeight },
        { 0.0f, 6 * fHeight, fWidth, 7 * fHeight },
        { fWidth, 6 * fHeight, 2 * fWidth, 7 * fHeight },
        { 2 * fWidth, 6 * fHeight, 3 * fWidth, 7 * fHeight },
    };

    //Show current button sprite
    buttonsSpriteSheet.render( position.x, position.y, &spriteClips[ (buttonNumber * 3) + static_cast<Uint8>(currentSprite)  ] );
}

void TextButton::setText(std::string line) {
    text = line;
}

void TextButton::render()
{
     switch (currentSprite) {
        case buttonSprite::Unpressed:
             super::render();
             renderedText.loadFromRenderedText(text, defaultColor);

             break;
        case buttonSprite::Hover:
            super::render();
            renderedText.loadFromRenderedText(text, hoverColor);

            break;
        case buttonSprite::Pressed:
            super::render();
            renderedText.loadFromRenderedText(text, pressedColor);
            renderedText.render( ( rawScreenWidth - renderedText.getWidth() ) / 2.f, ( rawScreenHeight - renderedText.getHeight() ) / 2.f );
            break;
    }

};

void makeUIMenuButtons() {

}
