#include "RenderTexture.h"
#include "Texture.h"
#include "Sprite.h"
#include "Window.h"
#include "Vector2d.h"

int main()
{
    Window window(Vector2d(720, 720));
    
    RenderTexture render_texture(Vector2d(100, 400));
    Texture texture(Colors::Blue);
    Sprite sprite(Vector2d(100, 400), texture);

    sprite.setPosition(Vector2d(650, 200));
    render_texture.draw(sprite);
    sprite.setTexture(render_texture.getTexture());
    render_texture.display();


    while (window.isOpen())
    {
        window.clear();

        window.draw(sprite);

        window.display();
    }
}